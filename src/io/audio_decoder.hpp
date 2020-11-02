#ifndef AUDIO_DECODER
#define AUDIO_DECODER

#include "audio_data.hpp"
#include <cstdint>
#include <string>
#include <vector>

class AudioDecoder {
	private:
		//////////////////////////////////////////////////////////////
		// MEMBER VARIABLES
		std::string filepath;

		std::vector<uint8_t> raw_hex;

		double sample_rate;
		unsigned int bit_depth;
		std::vector<int> samples;
		//////////////////////////////////////////////////////////////

		void read_file();

		std::size_t decode_big_endian(std::size_t start, std::size_t end);
		std::size_t decode_little_endian(std::size_t start, std::size_t end);
		std::string uint_to_ascii(std::size_t num);

		void decode_wav();

	public:
		AudioDecoder(std::string path_to_file);

		AudioData decode();

};


#endif
