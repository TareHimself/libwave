#pragma once
#include <string>
// http://soundfile.sapp.org/doc/WaveFormat/
// https://stackoverflow.com/a/32128050
namespace libwave
{

    constexpr char RIFF_ID[4] = {'R', 'I', 'F', 'F'};
    constexpr char FORMAT[4] = {'W', 'A', 'V', 'E'};
    constexpr char FMT_ID[4] = {'f', 'm', 't', ' '};
    constexpr char DATA_ID[4] = {'d', 'a', 't', 'a'};

    struct ChunkHeader
    {
        char chunkId[4];    // Header Id
        uint32_t chunkSize; // Size if next chunk in bits
    };

    struct RIFFHeader
    {
        char chunkId[4];
        uint32_t chunkSize;
        char format[4];
    };

    struct FMTChunk
    {
        uint16_t audioFormat;   // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
        uint16_t numChannels;   // Number of channels 1=Mono 2=Stereo
        uint32_t sampleRate;    // Sampling Frequency in Hz
        uint32_t byteRate;      // bytes per second
        uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
        uint16_t bitsPerSample; // Number of bits per sample
    };

    // struct DataChunk {
    //     char chunkId[4];
    //     uint32_t chunkSize;
    //     void * data;
    // };

    struct WaveFile
    {
        // private:
        RIFFHeader riff;
        FMTChunk fmt;
        uint32_t dataSize;
        void *data;

    public:
        template <typename T>
        T *getData();

        int getBytesPerSample();

        uint32_t getDataSize();

        int getSampleRate();

        int getChannels();

        ~WaveFile();
    };

    WaveFile *fromFile(std::string fileName);
}