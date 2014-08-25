/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Inc.
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

#include <iostream>
#include <vector>

#include "RadarTrack.hpp"

#include <dds/dds.hpp>

using namespace dds::core;
using namespace dds;
using namespace dds::domain;

int main(int, char**) {

	DomainId id = 0;
    DomainParticipant dp = TheParticipantFactory().create_participant(id);

    pub::qos::PublisherQos pqos;
    pqos << policy::Partition("Tracks");

    pub::Publisher pub = dp.create_publisher(pqos);

    topic::qos::TopicQos tqos;
    tqos << policy::Reliability::Reliable()
         << policy::Durability::Transient()
         << policy::History::KeepLast(10)
         << policy::TransportPriority(14);


    dds::topic::Topic<RadarTrack> topic =
    dp.create_topic<RadarTrack>("TrackTopic", "RadarTrack", tqos);

    pub::qos::DataWriterQos dwqos(tqos);

    pub::DataWriter<RadarTrack> dw;


    pub::DataWriter<RadarTrack> dwr = pub.create_datawriter(topic, dwqos);
    dw = dwr;

    RadarTrack track("alpha", 100, 200);

    dw << track;

    // Look-up data writers for a specific topic name
    std::vector< pub::DataWriter<RadarTrack> > results;
    dds::pub::find< pub::DataWriter<RadarTrack> >(
            pub,
            "TrackTopic",
            std::back_inserter(results));

    pub::AnyDataWriter adw (dw);

    dwr = adw.get<RadarTrack>();

    dds::topic::ContentFilteredTopic<RadarTrack> cftopic;

    dds::topic::MultiTopic<RadarTrack> mtopic;

}
