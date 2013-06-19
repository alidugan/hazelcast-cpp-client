//
// Created by sancar koyunlu on 5/23/13.
// Copyright (c) 2013 hazelcast. All rights reserved.
#ifndef HAZELCAST_QUEUE_CONTAINS_REQUEST
#define HAZELCAST_QUEUE_CONTAINS_REQUEST

#include "../serialization/Data.h"
#include "PortableHook.h"

namespace hazelcast {
    namespace client {
        namespace queue {
            class ContainsRequest {
            public:

                ContainsRequest(const std::string& name, std::vector<serialization::Data>& dataList)
                :name(name)
                , dataList(dataList) {

                };

                int getTypeSerializerId() const {
                    return serialization::SerializationConstants::CONSTANT_TYPE_PORTABLE;
                };

                int getFactoryId() const {
                    return queue::PortableHook::F_ID;
                }

                int getClassId() const {
                    return queue::PortableHook::CONTAINS;
                }

                template<typename HzWriter>
                void writePortable(HzWriter& writer) const {
                    writer["n"] << name;
                    writer["s"] << dataList.size();
                    std::vector<serialization::Data>::iterator it;
                    for (it = dataList.begin(); it != dataList.end(); ++it) {
                        writer << (*it);
                    }
                };

                template<typename HzReader>
                void readPortable(HzReader& reader) {
                    reader["n"] >> name;
                    int size;
                    reader["s"] >> size;
                    dataList.resize(size);
                    for (int i = 0; i < size; i++) {
                        reader >> dataList[i];
                    }
                };
            private:
                std::vector<serialization::Data>& dataList;
                std::string name;
            };
        }
    }
}

#endif //HAZELCAST_QUEUE_CONTAINS_REQUEST
