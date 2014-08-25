#include "telemetry_utilT.hpp"

template<typename T>
std::ostream&
operator << (std::ostream& os, const dds::topic::Topic<T>& s) {
  os << "("  << s.data << ")";
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
	 void printSALTopic(const dds::topic::Topic<T>& s) {
	   std::cout << s.data << std::endl;
	 }

    	 void printSALTopicSample(const dds::sub::SampleInfo& s) {
   	   std::cout << s << std::endl;
  	 }

   }
}

