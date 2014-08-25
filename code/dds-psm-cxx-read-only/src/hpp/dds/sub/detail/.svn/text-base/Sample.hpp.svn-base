#ifndef OMG_DDS_PUB_DETAIL_SAMPLE_HPP_
#define OMG_DDS_PUB_DETAIL_SAMPLE_HPP_

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

#include <dds/core/corefwd.hpp>
#include <dds/core/Exception.hpp>
#include <dds/core/Time.hpp>
#include <dds/sub/detail/subfwd.hpp>
#include <dds/sub/status/ReaderState.hpp>


namespace dds { namespace sub { namespace detail {

class GenerationCount {
public:
    inline int32_t disposed() const {
        return 0;
    }

    inline int32_t no_writers() const {
        return 0;
    }
};


class Rank {
public:
    inline int32_t absolute_generation() const {
        return 0;
    }

    inline int32_t generation() const {
        return 0;
    }

    inline int32_t sample() const {
        return 0;
    }
};


class SampleInfo {
public:
    inline const dds::core::Time timestamp() const {
        return dds::core::Time();
    }

    inline const dds::sub::status::ReaderState state() const {
        return dds::sub::status::ReaderState::any();
    }

    inline const GenerationCount generation_count() const {
        return GenerationCount();
    }

    inline const Rank rank() const {
        return Rank();
    }

    inline bool valid() const {
        return false;
    }
};


template <typename T>
class Sample {
public:
    const T& data() const {
        throw dds::core::InvalidDataError("sample has no valid data");
    }

    const SampleInfo& info() const {
        return info_;
    }
    
private:
    SampleInfo info_;
};


template <typename T>
class LoanedSamples { };
} } }


#endif /* OMG_DDS_PUB_DETAIL_SAMPLE_HPP_ */
