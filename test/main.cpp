#include <iostream>
#include <libwave.hpp>

int main(int argc, char** argv){
    
    std::cout << "Hello World " << std::endl;
    
    const auto wav = libwave::FromFile(argv[1]);

    if(wav != nullptr){
        std::cout << "Wav Decoded" << std::endl;
        std::cout << wav->GetDataSize() << std::endl;
        std::cout << wav->GetChannels() << std::endl;
        std::cout << wav->riff.chunkSize << std::endl;
        std::cout << wav->dataSize << std::endl;
        std::cout << (wav->riff.chunkSize - wav->dataSize) / 8 << std::endl;
        delete wav;
    }
    else
    {
        std::cout << "Failed To Decode Wav" << std::endl;
    }

    return 0;
}