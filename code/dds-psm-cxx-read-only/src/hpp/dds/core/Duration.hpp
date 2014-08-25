#ifndef OMG_DDS_CORE_DURATION_HPP_
#define OMG_DDS_CORE_DURATION_HPP_

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


namespace dds { namespace core {

/**
 * This class represents a time interval.
 */
class Duration {
public:
    static const Duration zero();       // {0, 0}
    static const Duration infinite();   // {0x7fffffff, 0x7fffffff}
public:
    /**
     * Create a duration elapsing zero seconds.
     */
    Duration();

    /**
     * Create a duration elapsing a specific amount of time.
     */
    explicit Duration(int32_t sec, uint32_t nanosec = 0);

    ~Duration();

public:
    static const Duration from_microseconds(int64_t microseconds);
    static const Duration from_milliseconds(int64_t milliseconds);
    static const Duration from_seconds(double seconds);
    
public:
    int32_t sec() const;
    void    sec(int32_t s);

    uint32_t nanosec() const;
    void     nanosec(uint32_t ns);

    /**
     * Reset the interval for this Duration.
     *
     * @param s second
     * @param ns nanosecont
     */
    void reset(int32_t s, uint32_t ns);

public:
    int compare(const Duration& that) const;

    bool operator >(const Duration& that) const;
    bool operator >=(const Duration& that) const;

    bool operator ==(const Duration& that) const;

    bool operator <=(const Duration& that) const;
    bool operator <(const Duration& that) const;

public:
    Duration& operator+=(const Duration &a_ti);
    Duration& operator-=(const Duration &a_ti);

public:
    void set_in_milliseconds(int64_t millisec);
    int64_t get_in_milliseconds() const;
    
    void set_in_microseconds(int64_t microsec);
    int64_t get_in_microseconds() const;
    
    void set_in_seconds(double seconds);
    double get_in_seconds() const;
    
private:
    uint32_t sec_;
    uint32_t nsec_;
};

// Duration arithmetic operators.
const Duration operator +(const Duration& lhs,
                          const Duration& rhs);
const Duration operator -(const Duration& lhs,
                          const Duration& rhs);
const Duration operator *(uint32_t lhs,
                          const Duration& rhs);
const Duration operator *(const Duration& lhs,
                          uint32_t rhs);
const Duration operator /(uint32_t lhs,
                          const Duration& rhs);
const Duration operator /(const Duration& lhs,
                          uint32_t rhs);
        
} } /* namespace dds / namespace core  */
#endif /* OMG_DDS_CORE_DURATION_HPP_ */

