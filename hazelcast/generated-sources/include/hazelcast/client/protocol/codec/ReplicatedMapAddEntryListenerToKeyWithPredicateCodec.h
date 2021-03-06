/*
 * Copyright (c) 2008-2015, Hazelcast, Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef HAZELCAST_CLIENT_PROTOCOL_CODEC_REPLICATEDMAPADDENTRYLISTENERTOKEYWITHPREDICATECODEC_H_
#define HAZELCAST_CLIENT_PROTOCOL_CODEC_REPLICATEDMAPADDENTRYLISTENERTOKEYWITHPREDICATECODEC_H_

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(push)
#pragma warning(disable: 4251) //for dll export
#endif

#include <memory>
#include <string>


#include "hazelcast/client/protocol/codec/ReplicatedMapMessageType.h"
#include "hazelcast/util/HazelcastDll.h"
#include "hazelcast/client/impl/BaseEventHandler.h"
#include "hazelcast/client/protocol/ClientMessage.h"
#include "hazelcast/client/protocol/codec/IAddListenerCodec.h"

#include "hazelcast/client/serialization/pimpl/Data.h"

namespace hazelcast {
    namespace client {

        namespace protocol {
            namespace codec {
                class HAZELCAST_API ReplicatedMapAddEntryListenerToKeyWithPredicateCodec : public IAddListenerCodec{
                public:
                    virtual ~ReplicatedMapAddEntryListenerToKeyWithPredicateCodec();
                    //************************ REQUEST STARTS ******************************************************************//
                    class HAZELCAST_API RequestParameters {
                        public:
                            static const enum ReplicatedMapMessageType TYPE;
                            static const bool RETRYABLE;

                        static std::auto_ptr<ClientMessage> encode(
                                const std::string &name, 
                                const serialization::pimpl::Data &key, 
                                const serialization::pimpl::Data &predicate, 
                                bool localOnly);

                        static int32_t calculateDataSize(
                                const std::string &name, 
                                const serialization::pimpl::Data &key, 
                                const serialization::pimpl::Data &predicate, 
                                bool localOnly);

                        private:
                            // Preventing public access to constructors
                            RequestParameters();
                    };
                    //************************ REQUEST ENDS ********************************************************************//

                    //************************ RESPONSE STARTS *****************************************************************//
                    class HAZELCAST_API ResponseParameters {
                        public:
                            static const int TYPE;

                            std::string response;
                            
                            static ResponseParameters decode(ClientMessage &clientMessage);

                            // define copy constructor (needed for auto_ptr variables)
                            ResponseParameters(const ResponseParameters &rhs);
                        private:
                            ResponseParameters(ClientMessage &clientMessage);
                    };
                    //************************ RESPONSE ENDS *******************************************************************//

                    //************************ EVENTS START*********************************************************************//
                    class HAZELCAST_API AbstractEventHandler : public impl::BaseEventHandler {
                        public:
                            virtual ~AbstractEventHandler();

                            void handle(std::auto_ptr<protocol::ClientMessage> message);

                            virtual void handleEntry(std::auto_ptr<serialization::pimpl::Data > key, std::auto_ptr<serialization::pimpl::Data > value, std::auto_ptr<serialization::pimpl::Data > oldValue, std::auto_ptr<serialization::pimpl::Data > mergingValue, const int32_t &eventType, const std::string &uuid, const int32_t &numberOfAffectedEntries) = 0;

                    };

                    //************************ EVENTS END **********************************************************************//

                    ReplicatedMapAddEntryListenerToKeyWithPredicateCodec (const std::string &name, const serialization::pimpl::Data &key, const serialization::pimpl::Data &predicate, const bool &localOnly);

                    //************************ IAddListenerCodec interface starts *******************************************//
                    std::auto_ptr<ClientMessage> encodeRequest() const;

                    std::string decodeResponse(ClientMessage &responseMessage) const;

                    //************************ IAddListenerCodec interface ends *********************************************//
                    private:
                        // Preventing public access to constructors
                        ReplicatedMapAddEntryListenerToKeyWithPredicateCodec ();

                        std::string name_;
                        serialization::pimpl::Data key_;
                        serialization::pimpl::Data predicate_;
                        bool localOnly_;
                };
            }
        }
    }
}

#if  defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#pragma warning(pop)
#endif

#endif /* HAZELCAST_CLIENT_PROTOCOL_CODEC_REPLICATEDMAPADDENTRYLISTENERTOKEYWITHPREDICATECODEC_H_ */

