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

#include "hazelcast/util/Util.h"
#include "hazelcast/util/ILogger.h"

#include "hazelcast/client/protocol/codec/ClientRemovePartitionLostListenerCodec.h"
#include "hazelcast/client/exception/UnexpectedMessageTypeException.h"

namespace hazelcast {
    namespace client {
        namespace protocol {
            namespace codec {
                const ClientMessageType ClientRemovePartitionLostListenerCodec::RequestParameters::TYPE = HZ_CLIENT_REMOVEPARTITIONLOSTLISTENER;
                const bool ClientRemovePartitionLostListenerCodec::RequestParameters::RETRYABLE = true;
                const int32_t ClientRemovePartitionLostListenerCodec::ResponseParameters::TYPE = 101;

                ClientRemovePartitionLostListenerCodec::~ClientRemovePartitionLostListenerCodec() {
                }

                std::auto_ptr<ClientMessage> ClientRemovePartitionLostListenerCodec::RequestParameters::encode(
                        const std::string &registrationId) {
                    int32_t requiredDataSize = calculateDataSize(registrationId);
                    std::auto_ptr<ClientMessage> clientMessage = ClientMessage::createForEncode(requiredDataSize);
                    clientMessage->setMessageType((uint16_t)ClientRemovePartitionLostListenerCodec::RequestParameters::TYPE);
                    clientMessage->setRetryable(RETRYABLE);
                    clientMessage->set(registrationId);
                    clientMessage->updateFrameLength();
                    return clientMessage;
                }

                int32_t ClientRemovePartitionLostListenerCodec::RequestParameters::calculateDataSize(
                        const std::string &registrationId) {
                    int32_t dataSize = ClientMessage::HEADER_SIZE;
                    dataSize += ClientMessage::calculateDataSize(registrationId);
                    return dataSize;
                }

                ClientRemovePartitionLostListenerCodec::ResponseParameters::ResponseParameters(ClientMessage &clientMessage) {
                    if (TYPE != clientMessage.getMessageType()) {
                        throw exception::UnexpectedMessageTypeException("ClientRemovePartitionLostListenerCodec::ResponseParameters::decode", clientMessage.getMessageType(), TYPE);
                    }

                    response = clientMessage.get<bool >();
                }

                ClientRemovePartitionLostListenerCodec::ResponseParameters ClientRemovePartitionLostListenerCodec::ResponseParameters::decode(ClientMessage &clientMessage) {
                    return ClientRemovePartitionLostListenerCodec::ResponseParameters(clientMessage);
                }

                ClientRemovePartitionLostListenerCodec::ResponseParameters::ResponseParameters(const ClientRemovePartitionLostListenerCodec::ResponseParameters &rhs) {
                        response = rhs.response;
                }
                //************************ EVENTS END **************************************************************************//

                ClientRemovePartitionLostListenerCodec::ClientRemovePartitionLostListenerCodec (const std::string &registrationId)
                        : registrationId_(registrationId) {
                }

                //************************ IRemoveListenerCodec interface start ************************************************//
                std::auto_ptr<ClientMessage> ClientRemovePartitionLostListenerCodec::encodeRequest() const {
                    return RequestParameters::encode(registrationId_);
                }

                const std::string &ClientRemovePartitionLostListenerCodec::getRegistrationId() const {
                    return registrationId_;
                }

                void ClientRemovePartitionLostListenerCodec::setRegistrationId(const std::string &id) {
                    registrationId_ = id;
                }

                bool ClientRemovePartitionLostListenerCodec::decodeResponse(ClientMessage &responseMessage) const {
                    return ResponseParameters::decode(responseMessage).response;
                }
                //************************ IRemoveListenerCodec interface ends *************************************************//

            }
        }
    }
}

