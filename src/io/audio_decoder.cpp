#include "audio_decoder.hpp"
#include "audio_data.hpp"
#include <string>
#include <vector>
#include <fstream>

AudioDecoder::AudioDecoder(std::string path_to_file) {
	this->filepath = path_to_file;
}


std::vector<uint8_t> AudioDecoder::readFile(const char* filename) {
	std::streampos fileSize;
	std::ifstream file(filename, std::ios::binary);

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> fileData(fileSize);
	file.read((char*) &fileData[0], fileSize);
	return fileData;
}

AudioData AudioDecoder::decode_wav() {
	
}



AudioData AudioDecoder::decode() {
	std::string ext = this->filepath.substr(this->filepath.length() - 4, this->filepath.length());
	if (ext == ".wav") {
		return this->decode_wav();
	}
}
