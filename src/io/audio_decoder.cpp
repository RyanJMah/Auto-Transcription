#include "audio_decoder.hpp"
#include "audio_data.hpp"
#include <iostream>
#include <cstdint>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>

AudioDecoder::AudioDecoder(std::string path_to_file) {
	this->filepath = path_to_file;
}


void AudioDecoder::read_file() {
	std::streampos fileSize;
	std::ifstream file(this->filepath, std::ios::binary);

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> fileData(fileSize);
	file.read((char*) &fileData[0], fileSize);

	this->raw_hex = fileData;
}

void AudioDecoder::decode_wav() {
	std::size_t i = 0;		// parsing index

	std::string header = "";
	for (i; i < 4; i++) {
		header += (unsigned char)(this->raw_hex[i]);
	}
	i += 4;
	assert(header == "RIFF");
	

	std::string fmt = "";
	for (i; i < 16; i++) {
		fmt += (unsigned char)(this->raw_hex[i]);
	}
	assert(fmt == "WAVEfmt ");


	



}



AudioData AudioDecoder::decode() {
	this->read_file();

	std::string ext = this->filepath.substr(this->filepath.length() - 4, this->filepath.length());
	
	if (ext == ".wav") {
		this->decode_wav();
	}

	return {this->sample_rate, this->bit_depth, this->samples};
}
