#ifndef AUDIO_DATA
#define AUDIO_DATA

#include <vector>

struct AudioData {
	double sample_rate;
	unsigned long bit_depth;

	std::vector<uint32_t> samples;
};

#endif
