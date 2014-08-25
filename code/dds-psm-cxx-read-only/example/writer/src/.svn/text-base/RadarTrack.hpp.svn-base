#ifndef OMG_DDS_DEMO_RADARTRACK_HPP_
#define OMG_DDS_DEMO_RADARTRACK_HPP_

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

#include <string>
#include <iosfwd>
#include <dds/topic/TopicTraits.hpp>


/*
 * struct RadarTrack {
 *     string id;
 *     long x;
 *     long yl
 * };
 *
 */
class RadarTrack {
public:
    RadarTrack(){ }
    RadarTrack(const std::string& the_id, int32_t the_x, int32_t the_y)
    : id_(the_id),
      x_(the_x),
      y_(the_y) { }
public:

    const std::string& id() const { return id_; }
    void id(const std::string& s) { id_ = s; }

    int32_t x() const { return x_; }
    void x(int32_t& i) { x_ = i; }

    int32_t y() const { return y_; }
    void y(int32_t& i) { y_ = i;}

protected:
    std::string id_;
    int32_t x_;
    int32_t y_;
};

REGISTER_TOPIC_TYPE(RadarTrack)


class MyRadarTrack : public RadarTrack {
public:
    // ...
};

std::ostream&
operator << (std::ostream& os, const RadarTrack& t);


#endif /* OMG_DDS_DEMO_RADARTRACK_HPP_ */
