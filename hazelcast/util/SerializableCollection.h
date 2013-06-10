//
// Created by sancar koyunlu on 5/29/13.
// Copyright (c) 2013 hazelcast. All rights reserved.



#ifndef HAZELCAST_SERIALIZABLE_CONNECTION
#define HAZELCAST_SERIALIZABLE_CONNECTION

#include "../client/serialization/Data.h"

namespace hazelcast {
    namespace util {
        class SerializableCollection {
            template<typename HzWriter>
            friend void hazelcast::client::serialization::writePortable(HzWriter& writer, const hazelcast::util::SerializableCollection& ar);

            template<typename HzReader>
            friend void hazelcast::client::serialization::readPortable(HzReader& reader, hazelcast::util::SerializableCollection& ar);

        public:
            SerializableCollection();

            ~SerializableCollection();

            std::vector<hazelcast::client::serialization::Data *> getCollection() const;

        private:
            std::vector<hazelcast::client::serialization::Data *> datas;
        };
    }
}

namespace hazelcast {
    namespace client {
        namespace serialization {
            inline int getTypeSerializerId(const hazelcast::util::SerializableCollection& x) {
                return SerializationConstants::CONSTANT_TYPE_DATA;
            };

            inline int getFactoryId(const hazelcast::util::SerializableCollection& ar) {
                return hazelcast::client::protocol::SpiConstants::SPI_PORTABLE_FACTORY;
            }

            inline int getClassId(const hazelcast::util::SerializableCollection& ar) {
                return hazelcast::client::protocol::SpiConstants::COLLECTION;
            }


            template<typename HzWriter>
            inline void writePortable(HzWriter& writer, const hazelcast::util::SerializableCollection& ar) {
                writer << ar.datas.size();
                for (std::vector< Data * >::const_iterator it = ar.datas.begin(); it != ar.datas.end(); ++it) {
//                    writer << *(*it);
                    (*it)->writeData(writer);
                }
            };

            template<typename HzReader>
            inline void readPortable(HzReader& reader, hazelcast::util::SerializableCollection& ar) {
                int size;
                reader >> size;
                if (size == -1)
                    return;
                for (int i = 0; i < size; i++) {
                    Data *data = new Data();
                    data->readData(reader);
                    ar.datas.push_back(data);
                }
            };

        }
    }
}

#endif //HAZELCAST_SERIALIZABLE_CONNECTION