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

		std::vector<std::uint8_t> raw_hex;

		double sample_rate;
		unsigned int bit_depth;
		std::vector<std::uint32_t> samples;
		//////////////////////////////////////////////////////////////

		// std::vector<uint8_t> read_file();
		void read_file();

		void decode_wav();

	public:
		AudioDecoder(std::string path_to_file);

		AudioData decode();

};


#endif
