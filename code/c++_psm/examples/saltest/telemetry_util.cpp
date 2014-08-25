#include "telemetry_util.hpp"

std::ostream&
operator << (std::ostream& os, const org::lsst::sal::SALTopicType& s) {
  os << "(" << s << ")";
  return os;
}

std::ostream&
operator << (std::ostream& os, const dds::sub::SampleInfo& si) {
  os << "SampleInfo {"
     // << "\n\tDataState = " << si.state()
     << "\n\tvalid_data = " << si.valid()
     << "\n\tsource_timestamp = " << " timestamp... "//si.timestamp()
     << "\n\tinstance_handle = " << si.instance_handle()
     << "\n\tpublication_handle = " << si.publication_handle()
     // << "\n\trank = " << si.rank()
     << "}";

  return os;
}

namespace sal { 
   namespace saltest {

         template<typename T>
	 void printSALTopic(const dds::topic::Topic<SALTopicType>& s) {
	   std::cout << s << std::endl;
	 }

    	 void printSALTopicSample(const dds::sub::SampleInfo& s) {
   	   std::cout << s << std::endl;
  	 }

   }
}


