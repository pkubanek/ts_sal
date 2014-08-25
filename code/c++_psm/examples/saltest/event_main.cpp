#include <boost/program_options.hpp>
#include <vector>
#include <iterator>
#include <algorithm>
#include "event_util.hpp"
#include "event_reader.hpp"
#include "event_writer.hpp"

namespace po = boost::program_options;
typedef sal::salevent::Config Config_t;
typedef sal::salevent::Params Params_t;

Config_t init(int argc, char* argv[]) {
  // The configuration is already initialized with
  // default parameters.
  Config_t config;
  config.runner.reset(new sal::salevent::Reader<SALTopic_eventType>());

  po::options_description desc("Available options for <ping-sub> are");
  desc.add_options()
      ("help", "produce help message")
      ("topic", po::value<std::string>(), "topic name")
      ("message", po::value<std::string>(), "Message")
      ("samples", po::value<int>(), "number of samples to read/write")
      ("period", po::value<int>(), "period at which samples are read/written")
      ("writer", "Writer application (by default is reader)")
      ("historyDepth", po::value<int>(), "Reader history depth")
      ("dataState",  po::value<int>(), "Read mode [0=Any,1=AllData,2=NewData]")
      ;

  try {
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
      std::cout << desc << "\n";
      exit(1);
    }

    if (vm.count("topic")) {
      config.params.name = vm["topic"].as<std::string>();
    }

    if (vm.count("message")) {
      config.params.message = vm["message"].as<std::string>();
    }

    if (vm.count("samples")) {
      config.params.samples = vm["samples"].as<int>();
    }

    if (vm.count("period")) {
      config.params.period = vm["period"].as<int>();
    }

    if (vm.count("writer")) {
      config.runner.reset(new sal::salevent::Writer<SALTopic_eventType>());
    }

    if (vm.count("historyDepth")) {
      config.params.history_depth = vm["historyDepth"].as<int>();
      std::cout << ">> Depth = " << config.params.history_depth << std::endl;
    }

    if (vm.count("dataState")) {
       uint32_t s = vm["dataState"].as<int>();
       std::cout << ">> dataState = " << s << std::endl;
      switch(s) {
      case 0:
        config.params.data_state = dds::sub::status::DataState::any();
        std::cout << ">> Any" << std::endl;
        break;
      case 1:
        config.params.data_state = dds::sub::status::DataState::any_data();
        std::cout << ">> Any Data" << std::endl;
        break;
      case 2:
        config.params.data_state = dds::sub::status::DataState::new_data();
        std::cout << ">> New Data" << std::endl;
        break;
      }
    }

  }
  catch (...) {
    std::cout << desc << "\n";
  }

  return config;
}

#include <bitset>

int main(int argc, char* argv[]) {

  Config_t config = init(argc, argv);

  std::bitset<(size_t) 10> bset;
  DataWriterQos dw_qos = DataWriterQos() << Reliability::Reliable() << Durability::Transient();


  try {
    dds::domain::DomainParticipant dp(0);
    dds::topic::Topic<SALTopic_eventType> salevent(dp, config.params.name);
    config.runner->run(dp, salevent, config.params);
  }
  catch (const dds::core::Exception& ex) {
    // std::cout << e.what() << std::endl;
    std::cout << "Exception Caught!" << std::endl;
  }
  return 0;
}
