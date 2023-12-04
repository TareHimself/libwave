#include <libwave.hh>
#include <iostream>
#include <fstream>
#include <cstring>

namespace libwave
{
    WaveFile::~WaveFile()
    {
    }

    WaveFile *fromFile(std::string fileName)
    {
        std::ifstream ifs{fileName, std::ios_base::binary};
        auto result = new WaveFile();

        if (!ifs.is_open())
        {
            std::cerr << "Failed to open file" << std::endl;
            delete result;
            return nullptr;
        }

        ifs.read((char *)(&result->riff), sizeof(result->riff));
        if (memcmp(result->riff.chunkId, RIFF_ID, 4) || memcmp(result->riff.format, FORMAT, 4))
        {
            std::cerr << "Invalid Riff Header" << std::endl;
            delete result;
            return nullptr;
        }

        ChunkHeader h;

        bool bHasReadData = false;

        while (ifs.read((char *)(&h), sizeof(h)))
        {

            if (memcmp(h.chunkId, FMT_ID, 4) == 0)
            {
                ifs.read((char *)(&result->fmt), h.chunkSize);
            }
            else if (memcmp(h.chunkId, DATA_ID, 4) == 0)
            {
                result->dataSize = h.chunkSize;
                result->data = malloc(h.chunkSize);
                ifs.read((char *)result->data, h.chunkSize);
                bHasReadData = true;
            }
            else
            {
                ifs.seekg(h.chunkSize, std::ios_base::cur);
            }
        }

        if (!bHasReadData)
        {
            std::cerr << "Failed To Read Data" << std::endl;
            delete result;
            return nullptr;
        }

        return result;
    }

    template <>
    float *WaveFile::getData<float>() { return (float*)data; }

    template <>
    uint8_t *WaveFile::getData<uint8_t>() { return (uint8_t*)data; }

    template <>
    int8_t *WaveFile::getData<int8_t>() { return (int8_t*)data; }

    template <>
    int16_t *WaveFile::getData<int16_t>() { return (int16_t*)data; }

    template <>
    int32_t *WaveFile::getData<int32_t>() { return (int32_t*)data; }

    int WaveFile::getBytesPerSample()
    {
        return fmt.bitsPerSample / 8;
    }

    uint32_t WaveFile::getDataSize()
    {
        return dataSize / getBytesPerSample();
    }

    int WaveFile::getSampleRate()
    {
        return fmt.sampleRate;
    }

    int WaveFile::getChannels()
    {
        return fmt.numChannels;
    }
}