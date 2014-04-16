//
// Created by sancar koyunlu on 6/25/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_GetAllRequest
#define HAZELCAST_GetAllRequest

#include "hazelcast/client/multimap/KeyBasedRequest.h"

namespace hazelcast {
    namespace client {
        namespace multimap {
            class HAZELCAST_API GetAllRequest : public KeyBasedRequest{
            public:
                GetAllRequest(const std::string& name, const serialization::pimpl::Data& key);

                int getClassId() const;

                bool isRetryable() const;
            };
        }
    }
}

#endif //HAZELCAST_GetAllRequest

