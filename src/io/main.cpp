#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "audio_decoder.hpp"

int main();

int main() {
	std::string filepath = "/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/c_major_115_bpm.wav";

	AudioDecoder decoder = AudioDecoder(filepath);
	auto data = decoder.decode();

	return 0;
}