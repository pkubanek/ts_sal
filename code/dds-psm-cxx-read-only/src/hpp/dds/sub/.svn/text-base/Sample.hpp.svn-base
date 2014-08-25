#ifndef OMG_DDS_SUB_SAMPLE_HPP_
#define OMG_DDS_SUB_SAMPLE_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <dds/core/Exception.hpp>
#include <dds/core/Value.hpp>
#include <dds/core/Time.hpp>
#include <dds/sub/subfwd.hpp>
#include <dds/sub/detail/Sample.hpp>
#include <dds/sub/status/ReaderState.hpp>
#include <dds/sub/detail/Sample.hpp>


namespace tdds {namespace sub {
template <typename DELEGATE>
class SampleInfo : dds::core::Value<DELEGATE> {
public:
    SampleInfo();
    SampleInfo(const SampleInfo& src);
    ~SampleInfo();

public:
    // implementation-defined:
    SampleInfo(const dds::sub::detail::SampleInfo& src);

public:
	const dds::core::Time timestamp() const {
		return this->delegate().timestamp();
	}

	const dds::sub::status::ReaderState state() const {
		return this->delegate().state();
	}
	const dds::sub::GenerationCount generation_count() const {
		return this->delegate().generation_count();
	}
	const dds::sub::Rank rank() const {
		return this->delegate().rank();
	}
	bool valid() const {
		return this->delegate().valid();
	}
};

} }
namespace dds { namespace sub {

template <typename T, typename DELEGATE>
class Sample : public dds::core::Value<DELEGATE>
{
public:
	typedef T DataType;
public:
	const DataType& data() const {
		return this->delegate().data();
	}
	const SampleInfo& info() const {
		info_ = this->delegate().info();
		return info_;
	}

private:
    mutable SampleInfo info_;
};

template <typename T, typename DELEGATE>
class LoanedSamples : public dds::core::Value<DELEGATE>
{
public:
    typedef T DataType;
    typedef Sample<DataType> SampleType;

public:
    LoanedSamples() { /* implementation-defined */ }
    LoanedSamples(const LoanedSamples& src);

    /**
     * Implicitly return the loan.
     */
    ~LoanedSamples() { /* implementation-defined */ }

public:
    class Iterator : public std::iterator<std::forward_iterator_tag, const SampleType>
    {
    public:
        Iterator() { /* implementation-defined */ }
        Iterator(const Iterator& src) { /* implementation-defined */ }
        ~Iterator() { /* implementation-defined */ }

    public:
        Iterator& operator=(const Iterator& src);

        bool operator==(const Iterator& other) const {
            // implementation-defined
            return false;
        }
        bool operator!=(const Iterator& other) const {
            // implementation-defined
            return false;
        }

        Iterator& operator++() {    // prefix
            // implementation-defined
            throw dds::core::UnsupportedError("LoanedSamples::Iterator::++");
        }
        Iterator  operator++(int) { // postfix
            // implementation-defined
            throw dds::core::UnsupportedError("LoanedSamples::Iterator::++");
        }

        const SampleType& operator*() {
            // implementation-defined
            throw dds::core::UnsupportedError("LoanedSamples::begin");
        }
        const SampleType* operator->() {
            // implementation-defined
            throw dds::core::UnsupportedError("LoanedSamples::end");
        }
    };

public:
    const Iterator begin() const {
        // implementation-defined
        throw dds::core::UnsupportedError("LoanedSamples::begin");
    }

    const Iterator end() const {
        // implementation-defined
        throw dds::core::UnsupportedError("LoanedSamples::end");
    }

public:
    void return_loan();     // explicitly return loan

};


} }

#endif /* OMG_DDS_SUB_SAMPLE_HPP_ */
