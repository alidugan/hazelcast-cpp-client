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



#include "hazelcast/client/protocol/codec/AtomicLongCompareAndSetCodec.h"
#include "hazelcast/client/exception/UnexpectedMessageTypeException.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const AtomicLongMessageType AtomicLongCompareAndSetCodec::RequestParameters::TYPE = HZ_ATOMICLONG_COMPAREANDSET;
                const bool AtomicLongCompareAndSetCodec::RequestParameters::RETRYABLE = false;
                const int32_t AtomicLongCompareAndSetCodec::ResponseParameters::TYPE = 101;
                std::auto_ptr<ClientMessage> AtomicLongCompareAndSetCodec::RequestParameters::encode(
                        const std::string &name, 
                        int64_t expected, 
                        int64_t updated) {
                    int32_t requiredDataSize = calculateDataSize(name, expected, updated);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t)AtomicLongCompareAndSetCodec::RequestParameters::TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(name);
                    clientMessage->set(expected);
                    clientMessage->set(updated);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t AtomicLongCompareAndSetCodec::RequestParameters::calculateDataSize(
                        const std::string &name, 
                        int64_t expected, 
                        int64_t updated) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(name);
                    dataSize += ClientMessage::calculateDataSize(expected);
                    dataSize += ClientMessage::calculateDataSize(updated);
                    return dataSize;
                }

                AtomicLongCompareAndSetCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    if (TYPE != clientMessage.getMessageType()) {
                        throw exception::UnexpectedMessageTypeException("AtomicLongCompareAndSetCodec::ResponseParameters::decode", clientMessage.getMessageType(), TYPE);
                    }

                    response = clientMessage.get<bool >();
                }

                AtomicLongCompareAndSetCodec::ResponseParameters AtomicLongCompareAndSetCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return AtomicLongCompareAndSetCodec::ResponseParameters(clientMessage);
                }

                AtomicLongCompareAndSetCodec::ResponseParameters::ResponseParameters(const AtomicLongCompareAndSetCodec::ResponseParameters &rhs) {
                        response = rhs.response;
                }
                //************************ EVENTS END **************************************************************************//

            }
        }
    }
}

