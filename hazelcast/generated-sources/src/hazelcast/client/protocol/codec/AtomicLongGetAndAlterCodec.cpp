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



#include "hazelcast/client/protocol/codec/AtomicLongGetAndAlterCodec.h"
#include "hazelcast/client/exception/UnexpectedMessageTypeException.h"
#include "hazelcast/client/serialization/pimpl/Data.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const AtomicLongMessageType AtomicLongGetAndAlterCodec::RequestParameters::TYPE = HZ_ATOMICLONG_GETANDALTER;
                const bool AtomicLongGetAndAlterCodec::RequestParameters::RETRYABLE = false;
                const int32_t AtomicLongGetAndAlterCodec::ResponseParameters::TYPE = 103;
                std::auto_ptr<ClientMessage> AtomicLongGetAndAlterCodec::RequestParameters::encode(
                        const std::string &name, 
                        const serialization::pimpl::Data &function) {
                    int32_t requiredDataSize = calculateDataSize(name, function);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t)AtomicLongGetAndAlterCodec::RequestParameters::TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(name);
                    clientMessage->set(function);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t AtomicLongGetAndAlterCodec::RequestParameters::calculateDataSize(
                        const std::string &name, 
                        const serialization::pimpl::Data &function) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(name);
                    dataSize += ClientMessage::calculateDataSize(function);
                    return dataSize;
                }

                AtomicLongGetAndAlterCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    if (TYPE != clientMessage.getMessageType()) {
                        throw exception::UnexpectedMessageTypeException("AtomicLongGetAndAlterCodec::ResponseParameters::decode", clientMessage.getMessageType(), TYPE);
                    }

                    response = clientMessage.get<int64_t >();
                }

                AtomicLongGetAndAlterCodec::ResponseParameters AtomicLongGetAndAlterCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return AtomicLongGetAndAlterCodec::ResponseParameters(clientMessage);
                }

                AtomicLongGetAndAlterCodec::ResponseParameters::ResponseParameters(const AtomicLongGetAndAlterCodec::ResponseParameters &rhs) {
                        response = rhs.response;
                }
                //************************ EVENTS END **************************************************************************//

            }
        }
    }
}

