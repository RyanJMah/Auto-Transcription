#ifndef AUDIO_DECODER
#define AUDIO_DECODER

#include "audio_data.hpp"
#include <string>
#include <vector>

class AudioDecoder {
	private:
		//////////////////////////////////////////////////////////////
		// MEMBER VARIABLES
		std::string filepath;

		std::vector<uint8_t> raw_hex;

		double sample_rate;
		long bit_depth;
		std::vector<uint32_t> samples;
		//////////////////////////////////////////////////////////////

		std::vector<uint8_t> read_file();

		AudioData decode_wav();

	public:
		AudioDecoder(std::string path_to_file);

		AudioData decode();

};


#endif
