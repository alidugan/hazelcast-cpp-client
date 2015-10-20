//
// Created by sancar koyunlu on 8/10/13.
// Copyright (c) 2013 hazelcast. All rights reserved.


#include "hazelcast/client/serialization/PortableReader.h"


namespace hazelcast {
    namespace client {
        namespace serialization {

            PortableReader::PortableReader(pimpl::PortableContext& context, pimpl::DataInput& input, boost::shared_ptr<ClassDefinition> cd, bool isDefaultReader)
            : isDefaultReader(isDefaultReader) {
                if (isDefaultReader) {
                    defaultPortableReader.reset(new pimpl::DefaultPortableReader(context, input, cd));
                } else {
                    morphingPortableReader.reset(new pimpl::MorphingPortableReader(context, input, cd));
                }

            }


            PortableReader::PortableReader(const PortableReader& reader)
            : isDefaultReader(reader.isDefaultReader)
            , defaultPortableReader(reader.defaultPortableReader.release())
            , morphingPortableReader(reader.morphingPortableReader.release()) {

            }

            PortableReader& PortableReader::operator=(const PortableReader& reader) {
                this->isDefaultReader = reader.isDefaultReader;
                this->defaultPortableReader.reset(reader.defaultPortableReader.release());
                this->morphingPortableReader.reset(reader.morphingPortableReader.release());
                return *this;
            }

            int PortableReader::readInt(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readInt(fieldName);
                return morphingPortableReader->readInt(fieldName);
            }

            long PortableReader::readLong(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readLong(fieldName);
                return morphingPortableReader->readLong(fieldName);
            }

            bool PortableReader::readBoolean(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readBoolean(fieldName);
                return morphingPortableReader->readBoolean(fieldName);
            }

            byte PortableReader::readByte(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readByte(fieldName);
                return morphingPortableReader->readByte(fieldName);
            }

            char PortableReader::readChar(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readChar(fieldName);
                return morphingPortableReader->readChar(fieldName);
            }

            double PortableReader::readDouble(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readDouble(fieldName);
                return morphingPortableReader->readDouble(fieldName);
            }

            float PortableReader::readFloat(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readFloat(fieldName);
                return morphingPortableReader->readFloat(fieldName);
            }

            short PortableReader::readShort(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readShort(fieldName);
                return morphingPortableReader->readShort(fieldName);
            }

            std::auto_ptr<std::string> PortableReader::readUTF(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readUTF(fieldName);
                return morphingPortableReader->readUTF(fieldName);
            }

            std::auto_ptr<std::vector<byte> > PortableReader::readByteArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readByteArray(fieldName);
                return morphingPortableReader->readByteArray(fieldName);
            }

            std::auto_ptr<std::vector<char> > PortableReader::readCharArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readCharArray(fieldName);
                return morphingPortableReader->readCharArray(fieldName);
            }

            std::auto_ptr<std::vector<int> > PortableReader::readIntArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readIntArray(fieldName);
                return morphingPortableReader->readIntArray(fieldName);
            }

            std::auto_ptr<std::vector<long> > PortableReader::readLongArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readLongArray(fieldName);
                return morphingPortableReader->readLongArray(fieldName);
            }

            std::auto_ptr<std::vector<double> > PortableReader::readDoubleArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readDoubleArray(fieldName);
                return morphingPortableReader->readDoubleArray(fieldName);
            }

            std::auto_ptr<std::vector<float> > PortableReader::readFloatArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readFloatArray(fieldName);
                return morphingPortableReader->readFloatArray(fieldName);
            }

            std::auto_ptr<std::vector<short> > PortableReader::readShortArray(const char *fieldName) {
                if (isDefaultReader)
                    return defaultPortableReader->readShortArray(fieldName);
                return morphingPortableReader->readShortArray(fieldName);
            }

            ObjectDataInput& PortableReader::getRawDataInput() {
                if (isDefaultReader)
                    return defaultPortableReader->getRawDataInput();
                return morphingPortableReader->getRawDataInput();
            }

            void PortableReader::end() {
                if (isDefaultReader)
                    return defaultPortableReader->end();
                return morphingPortableReader->end();

            }
        }
    }
}
