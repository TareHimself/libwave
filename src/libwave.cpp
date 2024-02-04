#include <libwave.hpp>
#include <iostream>
#include <fstream>
#include <cstring>

namespace libwave
{
    WaveFile::~WaveFile()
    {
    }

    WaveFile * FromFile(const std::filesystem::path &fileName)
    {
        std::ifstream ifs{fileName, std::ios_base::binary};
        

        if (!ifs.is_open())
        {
            std::cerr << "Failed to open file" << std::endl;
            return nullptr;
        }

        auto result = new WaveFile();

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
            delete result;
            return nullptr;
        }

        return result;
    }

    template <>
    float *WaveFile::GetData<float>() { return (float*)data; }

    template <>
    uint8_t *WaveFile::GetData<uint8_t>() { return (uint8_t*)data; }

    template <>
    int8_t *WaveFile::GetData<int8_t>() { return (int8_t*)data; }

    template <>
    int16_t *WaveFile::GetData<int16_t>() { return (int16_t*)data; }

    template <>
    int32_t *WaveFile::GetData<int32_t>() { return (int32_t*)data; }

    int WaveFile::GetBytesPerSample()
    {
        return fmt.bitsPerSample / 8;
    }

    uint32_t WaveFile::GetDataSize()
    {
        return dataSize / GetBytesPerSample();
    }

    int WaveFile::GetSampleRate()
    {
        return fmt.sampleRate;
    }

    int WaveFile::GetChannels()
    {
        return fmt.numChannels;
    }
}