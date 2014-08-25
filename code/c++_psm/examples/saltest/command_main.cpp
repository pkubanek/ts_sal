#include <boost/program_options.hpp>
#include <vector>
#include <iterator>
#include <algorithm>
#include "command_util.hpp"
#include "command_reader.hpp"
#include "command_writer.hpp"

namespace po = boost::program_options;
typedef sal::salcommand::Config Config_t;
typedef sal::salcommand::Params Params_t;

Config_t init(int argc, char* argv[]) {
  // The configuration is already initialized with
  // default parameters.
  Config_t config;
  config.runner.reset(new sal::salcommand::Reader<SALTopic_commandType>());

  po::options_description desc("Available options for <ping-sub> are");
  desc.add_options()
      ("help", "produce help message")
      ("topic", po::value<std::string>(), "topic name")
      ("subssytem", po::value<std::string>(), "Subsystem")
      ("device", po::value<std::string>(), "Device")
      ("property", po::value<std::string>(), "Property")
      ("action", po::value<std::string>(), "Action")
      ("value", po::value<std::string>(), "Value")
      ("modifiers", po::value<std::string>(), "Modifiers")
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

    if (vm.count("modifiers")) {
      config.params.name = vm["modifiers"].as<std::string>();
    }

    if (vm.count("subsystem")) {
      config.params.name = vm["subsystem"].as<std::string>();
    }

    if (vm.count("device")) {
      config.params.name = vm["device"].as<std::string>();
    }

    if (vm.count("property")) {
      config.params.name = vm["property"].as<std::string>();
    }

    if (vm.count("action")) {
      config.params.name = vm["action"].as<std::string>();
    }

    if (vm.count("value")) {
      config.params.name = vm["value"].as<std::string>();
    }

    if (vm.count("writer")) {
      config.runner.reset(new sal::salcommand::Writer<SALTopic_commandType>());
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
    dds::topic::Topic<SALTopic_commandType> salcommand(dp, config.params.name);
    config.runner->run(dp, salcommand, config.params);
  }
  catch (const dds::core::Exception& ex) {
    // std::cout << e.what() << std::endl;
    std::cout << "Exception Caught!" << std::endl;
  }
  return 0;
}
