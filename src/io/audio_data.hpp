#ifndef AUDIO_DATA
#define AUDIO_DATA

#include <vector>
#include <cstdint>

struct AudioData {
	double sample_rate;
	unsigned int bit_depth;

	std::vector<std::uint32_t> samples;
};

#endif
