#include <iostream>
#include <fstream>
#include <iomanip>
#include <functional>
#include <cmath>
#include <vector>
#include "signal_processor.hpp"

#define pi 3.141592653589793

std::vector<double> generate_time_series(double t_step, std::size_t N);
std::vector<double> generate_signal(std::vector<double> t, std::function<double(double)> f);
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

int main() {
	SignalProcessor sp = SignalProcessor();

	double fs = 44.1E3;
	auto t = generate_time_series(1/fs, 1 << 15);
	
	std::function<double(double)> f;
	f = [](double t) { return sin(2*pi*440*t) + sin(2*pi*800*t); };
	
	auto x = generate_signal(t, f);

	std::cout << x.size() << std::endl;

	auto X = sp.fft(x);
	auto freqs = sp.generate_freq_bins(fs, X.size());

	std::ofstream out_file;
	out_file.open("/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/test.csv");
	for (std::size_t i = 0; i < X.size(); i++) {
		out_file << std::fixed << std::setprecision(15);
		out_file << freqs[i] << "," << X[i] << std::endl;
	}
	out_file.close();


	return 0;
}