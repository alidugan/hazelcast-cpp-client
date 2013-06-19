//
// Created by sancar koyunlu on 5/23/13.
// Copyright (c) 2013 hazelcast. All rights reserved.
#ifndef HAZELCAST_QUEUE_DESTROY_REQUEST
#define HAZELCAST_QUEUE_DESTROY_REQUEST

#include "../serialization/SerializationConstants.h"
#include "PortableHook.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace queue {
            class DestroyRequest {
            public:
                DestroyRequest(const std::string& name)
                :name(name) {

                };

                int getTypeSerializerId() const {
                    return serialization::SerializationConstants::CONSTANT_TYPE_PORTABLE;
                };

                int getFactoryId() const {
                    return queue::PortableHook::F_ID;
                }

                int getClassId() const {
                    return queue::PortableHook::DESTROY;
                };

                template<typename HzWriter>
                void writePortable(HzWriter& writer) const {
                    writer["n"] << name;
                };

                template<typename HzReader>
                void readPortable(HzReader& reader) {
                    reader["n"] >> name;
                };
            private:
                std::string name;
            };
        }
    }
}

#endif //HAZELCAST_QUEUE_DESTROY_REQUEST
