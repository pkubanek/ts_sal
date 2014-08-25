// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>

// -- SIMD Include
#include <dds/dds.hpp>

// -- Hello Include
#include <gen/ccpp_TopicId.h>
#include <sys/shm.h>
#include "TopicId_cache.h"
#include "svcSAL_TopicSubSystem_topics.h"
TopicId_cache *TopicId_ref;

REGISTER_TOPIC_TRAITS(TopicId);

namespace po = boost::program_options;

int history_depth = 10;
int history = 1;
bool set_deadline = false;
DDS::Duration_t deadline = {1, 0};

std::string name("OpenSplice|DDS");
std::string topic("TopicIdTopic");
std::string type("TopicId");

bool parse_args(int argc, char* argv[])
{
  po::options_description desc("Available options for <TopicId-sub> are");
  desc.add_options()
    ("help", "produce help message")
    ("topic", po::value<std::string>(), "topic name for this TopicId application")
    ("reader-history", po::value<int>(), "reader history QoS")
    ("deadline", po::value<int>(), "deadline QoS (in sec)")
    ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }

    if (vm.count("topic"))
      topic = vm["topic"].as<std::string>();

    if (vm.count("reader-history"))
      history = vm["reader-history"].as<int>();

    if (vm.count("deadline")) {
      deadline.sec = vm["deadline"].as<int>();
      set_deadline = true;
    }
  }
  catch (...) {
    std::cout << desc << "\n";
    return false;
  }
  return true;
}  

class TopicIdDataHandler {
public:
  void operator() (dds::DataReader<TopicId>& reader) {
    TopicIdSeq samples;
    DDS::SampleInfoSeq infos;
    reader.read(samples, infos);
    for (unsigned int i = 0; i < samples.length(); ++i) {
// INSERT COPY_TO_SHM from samples[i]
    }
    reader.return_loan(samples, infos);
  }
};

int main(int argc, char* argv[]) {

   int TopicId_shmsize;
   int lshmid;

   int TopicId_shmid = SAL_SHMEM_KEY_TopicId;
   TopicId_shmsize = sizeof(struct TopicId_cache);
   lshmid = shmget(TopicId_shmid, TopicId_shmsize , IPC_CREAT|0666);
   TopicId_ref  = (TopicId_cache *) shmat(lshmid, NULL, 0);

  if (!parse_args(argc, argv))
    return 1;
  // -- start the dds runtime
  dds::Runtime runtime("LSST");

  dds::Topic<TopicId> TopicIdTopic(topic);
  dds::DataReader<TopicId> reader(TopicIdTopic);

  TopicIdDataHandler handler;
  dds::ReadCondition arc = reader.create_readcondition(handler, 
						       dds::NOT_READ_SAMPLE_STATE, 
						       dds::ANY_VIEW_STATE,
						       dds::ALIVE_INSTANCE_STATE);
  
  ::dds::WaitSet ws;
  DDS::ReturnCode_t retc = ws.attach(arc);
  
  std::cout << ">> Attach Condition: " 
	    << dds::retcode2string(retc) << std::endl;

  DDS::Duration_t timeout = {1, 0};
  bool done = false;
  while (!done) {
    try {
      ws.dispatch(timeout);
    } catch (const dds::InterruptedException& e) {
      exit(0);
    }
  }

  return 0;
}
