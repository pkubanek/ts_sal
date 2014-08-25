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

int sub_main(int, char**);

using namespace dds::core;
using namespace dds::core::cond;
using namespace dds::core::policy;
using namespace dds::core::status;
using namespace dds::topic;
using namespace dds::domain;
using namespace dds::sub;
using namespace dds::sub::cond;
using dds::sub::qos::DataReaderQos;


int sub_main(int, char**) {
    try {
        // --- Configuration --- //
        DomainParticipant dp = TheParticipantFactory().create_participant();
        Topic<RadarTrack> tp = dp.create_topic<RadarTrack>("Radar Tracks");
        Subscriber sub = dp.create_subscriber();
        DataReaderQos drq = sub.default_datareader_qos();
        // Set QoS policies like this:
        drq.policy<Reliability>().kind(ReliabilityKind::RELIABLE);
        drq.policy<Ownership>().kind(OwnershipKind::EXCLUSIVE);
        // ...or like this:
        drq << Reliability::Reliable()
            << Ownership::Exclusive();
        DataReader<RadarTrack> dr = sub.create_datareader<RadarTrack>(tp, drq);
        
        // --- Read --- //
        WaitSet ws = WaitSet::newWaitSet();
        // 3 equivalent ways to be notified of new data:
        // #1: Trigger based on read state:
        ReadCondition<RadarTrack> cond1 = dr.create_readcondition();
        DataReader<RadarTrack> dr2 = parent< DataReader<RadarTrack> >(cond1); // dr == dr2

        // #2: Trigger based on DATA_AVAILABLE status change:
        StatusCondition< DataReader<RadarTrack> > cond2 = dr.status_condition();
        cond2.enabled_statuses(StatusMask::data_available());
        dr2 = parent< DataReader<RadarTrack> >(cond2); // dr == dr2

        // #3: Trigger based on DATA_ON_READERS status change:
        StatusCondition<Subscriber> cond3 = sub.status_condition();
        cond3.enabled_statuses(StatusMask::data_on_readers());
        Subscriber sub2 = parent<Subscriber>(cond3);    // sub == sub2

        // ...Or use a GuardCondition and trigger manually:
        GuardCondition gc = GuardCondition::newGuardCondition();

        // Attach any or all of the conditions:
        ws.attach_condition(cond1);
        ws.attach_condition(cond2);
        ws.attach_condition(cond3);
        ws.attach_condition(gc);
        while (true) {
            ws.wait();
            // Take a loan out on multiple samples like this:
            LoanedSamples<RadarTrack> dt = dr.take();
            for (LoanedSamples<RadarTrack>::Iterator it  = dt.begin();
                 it != dt.end();
                 ++it) {
                const Sample<RadarTrack>& sample = *it;
                if (sample.info().valid()) {
                    const RadarTrack& data = sample.data();
                    std::cout << data.x() << ", " << data.y() << std::endl;
                    // ...
                }
            }
            // ...or get a copy like this:
            std::vector< Sample<RadarTrack> > my_copy(dt.begin(), dt.end());
        }
        
        // --- Shutdown --- //
        dp.close();
    } catch (const Exception& ex) {
        // log exception
        return -1;
    }
    return 0;
}
