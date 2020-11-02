#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <cmath>
#include <vector>

#include "../io/audio_data.hpp"
#include "../io/audio_decoder.hpp"

#include "signal.hpp"
#include "signal_processor.hpp"
#include "onset_detector.hpp"

#define pi 3.141592653589793

std::vector<double> generate_time_series(double t_step, std::size_t N);
std::vector<double> generate_signal(std::vector<double> t, std::function<double(double)> f);
void test_fft();
void test_onset_detection();
int main();


std::vector<double> generate_time_series(double t_step, std::size_t N) {
	std::vector<double> t_series;
	t_series.resize(N);

	for (std::size_t i = 0; i < N; i++) {
		t_series[i] = t_step*i;
	}
	return t_series;
}
std::vector<double> generate_signal(std::vector<double> t, std::function<double(double)> f) {
	std::vector<double> x;
	x.resize(t.size());

	for (std::size_t i = 0; i < x.size(); i++) {
		x[i] = f(t[i]);
	}
	return x;
}
void write_file(std::string path, std::vector<double> x, std::vector<double> y) {
	std::ofstream out_file;
	out_file.open(path);
	for (std::size_t i = 0; i < x.size(); i++) {
		out_file << std::fixed << std::setprecision(15);
		out_file << x[i] << "," << y[i] << std::endl;
	}
	out_file.close();
}


void test_fft() {
	SignalProcessor sp = SignalProcessor();

	double fs = 44.1E3;
	auto t = generate_time_series(1/fs, 1 << 15);
	
	std::function<double(double)> f;
	f = [](double t) { return sin(2*pi*440*t) + sin(2*pi*800*t); };
	
	auto x = generate_signal(t, f);

	auto X_omega = sp.fft(x, fs);
	auto omega = X_omega.independant;
	auto X = X_omega.dependant;

	write_file("/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/test.csv", omega, X);
}

void test_onset_detection() {
	std::string in_path = "/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/c_major_115_bpm.wav";
	std::string out_path = "/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/results.csv";

	AudioDecoder decoder = AudioDecoder(in_path);
	auto data = decoder.decode();

	double fs = data.sample_rate;
	std::vector<double> samples(data.samples.begin(), data.samples.end());

	OnsetDetector onset_detector = OnsetDetector(fs, 1 << 10);	// 2^12
	// onset_detector.params.weighting_function = [](double k) { return abs(k); };


	Signal input = {generate_time_series(1/fs, samples.size()), samples};
	Signal results = onset_detector.detect_onsets(input);

	write_file(out_path, results.independant, results.dependant);
}


int main() {
	test_onset_detection();

	return 0;
}

