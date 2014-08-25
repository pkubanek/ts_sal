#ifndef OMG_DDS_CORE_TIME_HPP_
#define OMG_DDS_CORE_TIME_HPP_

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

class Time {
public:
    static const Time invalid();       // {-1, 0xffffffff}

public:
    static const Time from_microseconds(int64_t microseconds);
    static const Time from_milliseconds(int64_t milliseconds);
    static const Time from_seconds(double seconds);

public:
	Time();
    explicit Time(int64_t sec, uint32_t nanosec = 0);

public:
    int64_t sec() const;
    void    sec(int64_t s);

    uint32_t nanosec() const;
    void     nanosec(uint32_t ns);

public:
    int compare(const Time& that);
	bool operator >(const Time& that);
	bool operator >=(const Time& that);

	bool operator ==(const Time& that);

	bool operator <=(const Time& that);
	bool operator <(const Time& that);

public:
    Time& operator+=(const Duration& a_ti);
    Time& operator-=(const Duration& a_ti);
    
public:
    void set_in_milliseconds(int64_t millisec);
    int64_t get_in_milliseconds() const;
    
    void set_in_microseconds(int64_t microsec);
    int64_t get_in_microseconds() const;
    
    void set_in_seconds(double seconds);
    double get_in_seconds() const;
    
private:
    int64_t sec_;
    uint32_t nsec_;
};

// Time arithmetic operators.
const Time operator +(const Time& lhs,      const Duration &rhs);
const Time operator +(const Duration& lhs,  const Time& rhs);
const Time operator -(const Time& lhs,      const Duration &rhs);

} } /* namespace dds / namespace core  */
#endif /* OMG_DDS_CORE_TIME_HPP_ */

