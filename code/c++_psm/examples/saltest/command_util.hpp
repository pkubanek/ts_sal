#ifndef ORG_LSST_SAL_SALCOMMAND_UTIL_HPP_
#define ORG_LSST_SAL_SALCOMMAND_UTIL_HPP_

#include <iostream>
// DDS Include
#include <dds/dds.hpp>

// Generated Files
#include <org/opensplice/core/config.hpp>
#include "gen/ccpp_SALTopic_command.h"

REGISTER_TOPIC_TRAITS(org::lsst::sal::SALTopic_commandType)

using namespace org::lsst::sal;

using namespace dds::core;
using namespace dds::core::policy;
using namespace dds::core::cond;
using namespace dds::core::status;

using namespace dds::domain;

using namespace dds::topic;

using namespace dds::pub;
using namespace dds::pub::qos;

using namespace dds::sub;
using namespace dds::sub::status;

std::ostream&
operator <<(std::ostream& os, const org::lsst::sal::SALTopic_commandType& s);

std::ostream&
operator <<(std::ostream& os, const dds::sub::SampleInfo& si);

namespace sal {
   namespace salcommand {
      struct Params;

      void printSALTopic_command(const org::lsst::sal::SALTopic_commandType& s);
      void printSALTopic_commandSample(const dds::sub::Sample<org::lsst::sal::SALTopic_commandType>& s);

      template<typename T>
      class Runner {
      public:
         virtual ~Runner() {
         }
         virtual void run(const dds::domain::DomainParticipant& dp,
               const dds::topic::Topic<T>& topic,
               const Params& params) = 0;
      };

      template<typename T>
      class IdleRunner: public Runner<T> {
      public:
         virtual ~IdleRunner() {
         }
      public:
         virtual void run(const dds::domain::DomainParticipant& dp,
               const dds::topic::Topic<T>& topic,
               const Params& params) {

         }
      };

      typedef boost::shared_ptr<sal::salcommand::Runner<SALTopic_commandType> > Runner_t;

      struct Params {
        Params() :
          name("test"),
          subsystem(""),
          device(""),
          property(""),
          action(""),
          value(""),
          modifiers(""),
          period(1000),
          samples(10),
          history_depth(1),
          data_state(dds::sub::status::DataState::new_data())
        { }
          std::string name;
          std::string subsystem;
          std::string device;
          std::string property;
          std::string action;
          std::string value;
          std::string modifiers;
          uint32_t period;
          uint32_t samples;
          uint32_t history_depth;
          dds::sub::status::DataState data_state;
       };

       struct Config {
          Params params;
          Runner_t runner;
       };

   }
} /** sal :: salcommand */


#endif /* ORG_LSST_SAL_SALCOMMAND_UTIL_HPP_ */
