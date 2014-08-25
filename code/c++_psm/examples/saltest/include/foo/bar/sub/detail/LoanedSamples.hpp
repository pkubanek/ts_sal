/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2012 PrismTech
 *   Limited and its licensees. All rights reserved. See file:
 *
 *                     $OSPL_HOME/LICENSE
 *
 *   for full copyright notice and license terms.
 *
 */
#ifndef OSPL_DDS_SUB_DETAIL_LOANEDSAMPLES_HPP_
#define OSPL_DDS_SUB_DETAIL_LOANEDSAMPLES_HPP_

/**
 * @file dds/sub/detail/LoanedSamples.hpp
 */

// Implementation

#include <org/opensplice/core/config.hpp>
#include <org/opensplice/sub/LoanedSequence.hpp>
#include <org/opensplice/topic/TopicTraits.hpp>
#include <vector>
#include <dds/sub/Sample.hpp>


namespace dds
{
namespace sub
{
namespace detail
{

template <typename T>
class LoanedSamples
{
public:

   typedef std::vector< dds::sub::Sample<T> >                             LoanedDataContainer;
   typedef typename std::vector< dds::sub::Sample<T> >::iterator iterator;
   typedef typename std::vector< dds::sub::Sample<T> >::const_iterator  const_iterator;

   typedef typename org::opensplice::topic::topic_data_reader<T>::type DR;

public:
   LoanedSamples() { }

   ~LoanedSamples() {  }

public:

   iterator mbegin() {
      return samples_.begin();
   }

   const_iterator begin() const {
      return samples_.begin();
   }

   const_iterator end() const {
      return samples_.end();
   }

   dds::core::size_type length() const {
      /** @todo Possible RTF size issue ? */
      return static_cast<dds::core::size_type> (samples_.size());
   }

   void resize(dds::core::size_type s) {
      samples_.resize(s);
   }

private:

   LoanedDataContainer samples_;
};

}
}
}

// End of implementation

#endif /* OSPL_DDS_SUB_DETAIL_LOANEDSAMPLES_HPP_ */
