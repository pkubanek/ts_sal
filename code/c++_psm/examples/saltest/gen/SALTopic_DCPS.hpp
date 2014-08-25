#ifndef CCPP_SALTOPIC_H
#define CCPP_SALTOPIC_H

#include "ccpp.h"
#include "SALTopic.h"
#include "SALTopicDcps.h"
#include <orb_abstraction.h>
#include "SALTopicDcps_impl.h"

#endif /* CCPP_SALTOPIC_H */

#ifdef SALTOPIC_DCPS_TYPESUPPORT_DEFINED
#ifndef SALTOPIC_DCPS_HPP_
#define SALTOPIC_DCPS_HPP_
#include "dds/dds.hpp"

REGISTER_TOPIC_TRAITS(::org::lsst::sal::SALTopicType)

#endif
#endif
