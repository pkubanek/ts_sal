#ifndef ORG_OPENSPLICE_CORE_CONFIG_HPP_
#define ORG_OPENSPLICE_CORE_CONFIG_HPP_


// Includes necessary for pulling in legacy C++ API
#include <dds_dcps.h>
#include <ccpp_dds_dcps.h>
#include <dds/core/macros.hpp>

/** Using a separate macro for org::opensplice in case we want to separate libs
later */
#define OSPL_ISOCPP_IMPL_API OMG_DDS_API

#endif /* ORG_OPENSPLICE_CORE_CONFIG_HPP_ */
