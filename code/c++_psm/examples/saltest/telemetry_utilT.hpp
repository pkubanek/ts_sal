#ifndef ORG_LSST_SAL_SALTEST_UTIL_HPP_
#define ORG_LSST_SAL_SALTEST_UTIL_HPP_

#include <iostream>

// DDS Include
#include <dds/dds.hpp>

// Generated Files
#include <org/opensplice/core/config.hpp>


#include "gen/ccpp_SALTopic.h"
REGISTER_TOPIC_TRAITS(org::lsst::sal::SALTopicType)
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

template<typename T>
std::ostream&
operator <<(std::ostream& os, const dds::topic::Topic<T>& s);

std::ostream&
operator <<(std::ostream& os, const dds::sub::SampleInfo& si);

namespace sal {
   namespace saltest {
      struct Params;

      template<typename T>
      void printSALTopic(const dds::topic::Topic<T>& s);
      void printSALTopicSample(const dds::sub::SampleInfo& s);

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


      struct Params {
        Params() :
          name("test"),
          period(1000),
          samples(10),
          history_depth(1),
          data_state(dds::sub::status::DataState::new_data())
        { }
          std::string name;
          uint32_t period;
          uint32_t samples;
          uint32_t history_depth;
          dds::sub::status::DataState data_state;
       };

       template<typename T>
       struct Config {
          Params params;
          Runner<T> runner;
       };

   }
} /** sal :: saltest */


#endif /* ORG_LSST_SAL_SALTEST_UTIL_HPP_ */
