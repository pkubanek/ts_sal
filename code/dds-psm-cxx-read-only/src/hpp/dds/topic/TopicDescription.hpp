#ifndef OMG_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_
#define OMG_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_

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

#include <tdds/core/Entity.hpp>
#include <dds/topic/topicfwd.hpp>
#include <idds/topic/TopicDescription.hpp>


namespace dds { namespace topic {

/**
 * TopicDescription represents the fact that both publications and
 * subscriptions are tied to a single data-type. Its attribute
 * type_name defines a unique resulting type for the publication
 * or the subscription and therefore creates an implicit
 * association with a TypeSupport. TopicDescription has also a
 * name that allows it to be retrieved locally.
 */
template <typename T, template <typename Q> class DELEGATE>
class TopicDescription : public tdds::core::Entity< DELEGATE<T> > {
public:
    typedef T DataType;

public:
    OMG_DDS_REF_TYPE(TopicDescription, tdds::core::Entity, DELEGATE<T>)

public:
    ~TopicDescription() { }

public:
    /**
     * Get the name used to create the TopicDescription.
     */
    const std::string& name() const {
        return this->delegate()->name();
    }

    /**
     * The type_name used to create the TopicDescription.
     */
    const std::string& type_name() const {
        return this->delegate()->type_name();
    }
};

} }

#endif /* OMG_DDS_TOPIC_TOPIC_DESCRIPTION_HPP_ */