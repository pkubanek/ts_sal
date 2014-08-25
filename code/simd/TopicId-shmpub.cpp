// -- STD C++ Include
#include <iostream>
#include <sstream>
#include <iterator>

// -- BOOST Include
#include <boost/program_options.hpp>

// -- SIMD Include
#include <dds/runtime.hpp>
#include <dds/topic.hpp>
#include <dds/writer.hpp>
#include <dds/traits.hpp>

// -- Hello Include
#include <gen/ccpp_TopicId.h>
#include <sys/shm.h>
#include "TopicId_cache.h"
#include "svcSAL_TopicId_topics.h"

#ifdef WIN32
#include "Windows.h"
#define msecSleep(msec) Sleep(msec)
#else
#define msecSleep(msec) usleep(1000*(msec))
#endif

namespace po = boost::program_options;

int period = 1;
int history_depth = 10;
int N = 50;
std::string name("OpenSplice|DDS");
std::string topic("TopicIdTopic");
std::string URI;

bool parse_args(int argc, char* argv[])
{
  po::options_description desc("Available options for <TopicId> are");
  desc.add_options()
    ("help", "produce help message")
    ("name", po::value<std::string>(), "name for this TopicId application")
    ("samples", po::value<int>(), "number of samples published")
    ("period", po::value<int>(), "period with which samples will be written")
    ("topic", po::value<std::string>(), "topic name for this TopicId application")
    ("URI", po::value<std::string>(), "OpenSplice DDS configuration URI")
    ;
 
  try {
    po::variables_map vm;        
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);    
   
    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      return false;
    }
    
    
    if (vm.count("name")) 
      name = vm["name"].as<std::string>();

    if (vm.count("topic")) 
      topic = vm["topic"].as<std::string>();

    if (vm.count("URI")) 
      URI = vm["URI"].as<std::string>();
    
    if (vm.count("samples")) 
      N = vm["samples"].as<int>();
    
    if (vm.count("period")) 
      period = vm["period"].as<int>();
  } 
  catch (...) {
    std::cout << desc << "\n" << std::endl;
    return false;
  }
  return true;
}  
REGISTER_TOPIC_TRAITS(TopicId);

int main(int argc, char* argv[]) {

   int TopicId_shmsize;
   int lshmid;
   int icount=0;
   int TopicId_shmid = SAL_SHMEM_KEY_TopicId;
   TopicId_cache *TopicId_ref;
   TopicId_shmsize = sizeof(struct TopicId_cache);
   lshmid = shmget(TopicId_shmid, TopicId_shmsize , IPC_CREAT|0666);
   TopicId_ref  = (TopicId_cache *) shmat(lshmid, NULL, 0);
  
  if (!parse_args(argc, argv))
    return 1;

  // -- start the dds runtime to use the default DDS partition, which
  // -- as per the DDS standard is ""
  dds::Runtime runtime("LSST");
  
  dds::Topic<TopicId> TopicIdTopic(topic);
  dds::DataWriter<TopicId> writer(TopicIdTopic);

  TopicId d;
  while (1) {
    if (TopicId_ref->syncO) {
// INSERT COPY_FROM_SHM to d
      writer.write(d);
    }
    msecSleep(period);
  }
  std::cout << std::endl;
  return 0;
}
