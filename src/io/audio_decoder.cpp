#include <iostream>
#include <cstdint>
#include <cassert>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

#include "audio_decoder.hpp"
#include "audio_data.hpp"
#include "formats/wav_format.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
AudioDecoder::AudioDecoder(std::string path_to_file) {
	this->filepath = path_to_file;

	this->sample_rate = 0;
	this->bit_depth = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// HELPERS
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

std::size_t AudioDecoder::decode_big_endian(std::size_t start, std::size_t end) {
	std::size_t decoded_data = 0;
	for (std::size_t i = end, j = 0; i >= start; i--, j += 8) {
		decoded_data += (unsigned int)(this->raw_hex[i] << j);
	}
	return decoded_data;
}
std::size_t AudioDecoder::decode_little_endian(std::size_t start, std::size_t end) {
	std::size_t decoded_data = 0;
	for (std::size_t i = start, j = 0; i <= end; i++, j += 8) {
		decoded_data += (unsigned int)(this->raw_hex[i] << j);
	}
	return decoded_data;
}
std::string AudioDecoder::uint_to_ascii(std::size_t num) {
	std::string str = "";
	while (num > 0) {
		str += (unsigned char)(num & 0xFF);
		num = num >> 8;
	}
	std::reverse(str.begin(), str.end());
	return str;
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// MAIN STUFF
void AudioDecoder::decode_wav() {
	this->sample_rate = this->decode_little_endian(SAMPLE_RATE_START, SAMPLE_RATE_END);
	this->bit_depth = this->decode_little_endian(BIT_DEPTH_START, BIT_DEPTH_END);

	unsigned int channels = this->decode_little_endian(NUM_CHANNELS_START, NUM_CHANNELS_END);

	std::size_t i = BIT_DEPTH_END;		// end of the "format" (fmt) section
	while ( this->uint_to_ascii(this->decode_big_endian(i, i + 3)) != "data" ) { i++; }
	i += 8;		// skip over the "data" and "chunk size" fields


	// prepare to extract the samples
	assert( (bit_depth % 8) == 0 );
	unsigned int byte_step = bit_depth/8;
	
	// this entire section below this comment is super sketchy... TOO BAD!
	if (channels == 1) {
		this->samples.resize( (this->raw_hex.size() - i)/byte_step + 5);		// + 5 to be safe
		for (std::size_t j = 0; i < this->raw_hex.size(); j++) {
			this->samples[j] = (int16_t)this->decode_little_endian(i, (i + byte_step - 1));
			i += byte_step;
		}
	}
	else {
		this->samples.resize( ((this->raw_hex.size() - i)/byte_step)/2 + 5 );	// + 5 to be safe
		for (std::size_t j = 0; i < this->raw_hex.size(); j++) {
			int16_t left = this->decode_little_endian(i, (i + byte_step - 1));
			int16_t right = this->decode_little_endian(i + byte_step, (i + byte_step*2) - 1);

			this->samples[j] = (left + right)/2;
			i += byte_step*2;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
// WRAPPER
AudioData AudioDecoder::decode() {
	this->read_file();
	std::string ext = this->filepath.substr(this->filepath.find("."), this->filepath.length());
	
	if (ext == ".wav") {
		this->decode_wav();
	}

	return {this->sample_rate, this->bit_depth, this->samples};
}
//////////////////////////////////////////////////////////////////////////////////////////////