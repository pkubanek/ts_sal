#ifndef CCPP_SALDATA_H
#define CCPP_SALDATA_H

#include "ccpp.h"
#include "SALData.h"
#include "SALDataDcps.h"
#include <orb_abstraction.h>
#include "SALDataDcps_impl.h"

#endif /* CCPP_SALDATA_H */

#ifdef SALDATA_DCPS_TYPESUPPORT_DEFINED
#ifndef SALDATA_DCPS_HPP_
#define SALDATA_DCPS_HPP_
#include "dds/dds.hpp"

REGISTER_TOPIC_TRAITS(::SALData::SALTopic)

#endif
#endif
