#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "audio_decoder.hpp"

int main();

int main() {
	std::string filepath = "/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/c_major_115_bpm.wav";
	// std::string filepath = "C:\\shared\\Personal\\Projects\\Auto-Transcription\\resources\\c_major_115_bpm.wav";

	AudioDecoder decoder = AudioDecoder(filepath);
	auto data = decoder.decode();

	std::cout << data.sample_rate << std::endl;
	std::cout << data.bit_depth << std::endl;

	double Ts = 1/data.sample_rate;

	std::ofstream out_file;
	out_file.open("/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/c_major_115_bpm.csv");
	// out_file.open("C:\\shared\\Personal\\Projects\\Auto-Transcription\\resources\\c_major_115_bpm.csv");
	for (std::size_t i = 0; i < data.samples.size(); i++) {
		out_file << std::fixed << std::setprecision(15);
		out_file << i*Ts << "," << data.samples[i] << "\n";
	}
	out_file.close();

	return 0;
}