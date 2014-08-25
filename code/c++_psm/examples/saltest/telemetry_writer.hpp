#ifndef ORG_LSST_SAL_SALTEST_WRITER_HPP_
#define ORG_LSST_SAL_SALTEST_WRITER_HPP_

#include "telemetry_util.hpp"
#include <unistd.h>
#include <vector>
#include <algorithm>

namespace sal {
   namespace saltest {
      template <typename T>
      class Writer;
   }
}
/**
 * This class shows a sample use of the (forward) iterator-based read API.
 * Beware that a back-inserting iterator API also exist.
 *
 */
template <typename T>
class sal::saltest::Writer : public sal::saltest::Runner<T> {
public:
   virtual ~Writer() { }

public:
   virtual void run(const dds::domain::DomainParticipant& dp,
         const dds::topic::Topic<T>& topic,
         const Params& params)
   {
      dds::pub::qos::PublisherQos pqos =
            dp.default_publisher_qos() << Partition("saltest");

      dds::pub::Publisher pub(dp, pqos);

      dds::pub::qos::DataWriterQos dwqos =
            pub.default_writer_qos() << Durability::Transient() << Reliability::Reliable();

      dds::pub::DataWriter<T> dw(pub, topic, dwqos);

      const uint32_t period = params.period;
      const uint32_t samples = params.samples;
      uint32_t sleep_time = period * 1000;
      DDS::String_mgr private_revCode;

      srand(clock());

      // AnyDataWriter work just fine...
      AnyDataWriter adw = dw;
      DataWriter<SALTopicType> xdw = adw.get<SALTopicType>();
      std::cout << "Topic Name = " << xdw.topic().name()
                      << "\tType Name = " << xdw.topic().type_name() << std::endl;

      // SALTopicType s = {params.private_revCode};
      SALTopicType s = {private_revCode};

      std::cout << ">> Writing Data...";
               std::flush(std::cout);
      for (uint32_t i = 0; i < samples; ++i) {
         // Regular write
         dw.write(s);

         // Stream write
         dw << s;

         usleep(sleep_time); // period is in ms
      }
   }
};


#endif /* ORG_LSSST_SAL_SALTEST_WRITER_HPP_ */

