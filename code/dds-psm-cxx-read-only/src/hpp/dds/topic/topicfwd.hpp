#ifndef OMG_DDS_TOPIC_TOPIC_FWD_HPP_
#define OMG_DDS_TOPIC_TOPIC_FWD_HPP_

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

#include <dds/core/detail/conformance.hpp>
#include <dds/topic/detail/topicfwd.hpp>
#include <tdds/topic/topicfwd.hpp>
#include <idds/topic/topicfwd.hpp>


namespace dds { namespace topic {

class AnyTopic;

class AnyTopicDescription;

class AnyTopicListener;

typedef tdds::topic::BuiltinTopicKey<dds::topic::detail::BuiltinTopicKeyImpl>
BuiltinTopicKey;

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
template <typename T,
          template <typename Q> class DELEGATE = dds::topic::detail::ContentFilteredTopic>
class ContentFilteredTopic;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

template <typename T>
struct is_topic_type;

#ifdef OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT
template <typename T,
          template <typename Q> class DELEGATE = dds::topic::detail::MultiTopic>
class MultiTopic;
#endif  // OMG_DDS_CONTENT_SUBSCRIPTION_SUPPORT

class NoOpAnyTopicListener;

typedef tdds::topic::ParticipantBuiltinTopicData<dds::topic::detail::ParticipantBuiltinTopicDataImpl>
ParticipantBuiltinTopicData;

typedef tdds::topic::PublicationBuiltinTopicData<dds::topic::detail::PublicationBuiltinTopicDataImpl>
PublicationBuiltinTopicData;

typedef tdds::topic::SubscriptionBuiltinTopicData<dds::topic::detail::SubscriptionBuiltinTopicDataImpl>
SubscriptionBuiltinTopicData;

template <typename T,
          template <typename Q> class DELEGATE = dds::topic::detail::Topic>
class Topic;

typedef tdds::topic::TopicBuiltinTopicData<dds::topic::detail::TopicBuiltinTopicDataImpl>
TopicBuiltinTopicData;

template <typename T,
          template <typename Q> class DELEGATE = idds::topic::TopicDescriptionImpl>
class TopicDescription;

template <typename T>
class TopicInstance;

template <typename T>
class TopicListener;

template <typename T>
struct topic_type_support;


namespace qos {
    typedef ::dds::topic::qos::detail::TopicQos TopicQos;
}

} }

#endif /* OMG_DDS_TOPIC_TOPIC_FWD_HPP_ */
