#include "response_util.hpp"

std::ostream&
operator << (std::ostream& os, const org::lsst::sal::SALTopic_responseType& s) {
  os << "("  << s.private_seqnum ")";
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

void sal::saltest::printSALTopic_responseSample(const dds::sub::Sample<org::lsst::sal::SALTopic_responseType>& s) {
   std::cout << s.data() << std::endl;
}

void sal::saltest::printSALTopic_response(const org::lsst::sal::SALTopic_responseType& s) {
  std::cout << s << std::endl;
}
