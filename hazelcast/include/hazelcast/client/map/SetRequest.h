//
// Created by sancar koyunlu on 5/23/13.
// Copyright (c) 2013 hazelcast. All rights reserved.
#ifndef HAZELCAST_MAP_SET_REQUEST
#define HAZELCAST_MAP_SET_REQUEST

#include "hazelcast/client/impl/PortableRequest.h"
#include "hazelcast/client/serialization/pimpl/Data.h"
#include <string>

namespace hazelcast {
    namespace client {
        namespace map {
            class HAZELCAST_API SetRequest : public impl::PortableRequest {
            public:
                SetRequest(const std::string &name, serialization::pimpl::Data &key, serialization::pimpl::Data &value, long threadId, long ttl);

                int getFactoryId() const;

                int getClassId() const;

                void write(serialization::PortableWriter &writer) const;


            private:
                std::string name;
                serialization::pimpl::Data key;
                serialization::pimpl::Data value;
                long threadId;
                long ttl;
            };
        }
    }
}

#endif //HAZELCAST_MAP_PUT_REQUEST

