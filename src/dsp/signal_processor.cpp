#include <cmath>
#include <complex>
#include <vector>
#include "signal_processor.hpp"

#define pi 3.141592653589793

SignalProcessor::SignalProcessor() {}

template <class T>
std::vector<std::complex<double>> SignalProcessor::hann(T x) {
	std::vector<std::complex<double>> hann_x;
	hann_x.resize(x.size());
	
	for (std::size_t i = 0; i < x.size(); i++) {
		std::complex<double> factor = 0.5*(1 - cos(2*pi*i/(x.size() - 1)));
		hann_x[i] = factor*x[i];
	}
	return hann_x;
}

template <class T>
std::vector<double> SignalProcessor::magnitude(T x) {
	std::vector<double> magnitude_x;
	magnitude_x.resize(x.size());

	for (std::size_t i = 0; i < x.size(); i++) {
		magnitude_x[i] = abs(x[i]);
	}
	return magnitude_x;
}


std::vector<std::complex<double>> SignalProcessor::fft_complex(std::vector<std::complex<double>> x) {
	std::size_t N = x.size();

	if (N == 1) {
		std::vector<std::complex<double>> ret = {x[0]};
		return ret;
	}

	else {
		std::vector<std::complex<double>> even;
		std::vector<std::complex<double>> odd;
		even.resize(N/2);
		odd.resize(N/2);

		for (std::size_t i = 0; i < N/2; i += 2) {
			even[i/2] = x[i + 1];
			odd[i/2] = x[i];
		}

		std::vector<std::complex<double>> x_even = this->fft_complex(even);
		std::vector<std::complex<double>> x_odd = this->fft_complex(odd);

		std::vector<std::complex<double>> x_ret;
		x_ret.resize(N);

		for (std::size_t k = 0; k < N/2; k++) {
			std::complex<double> W = cos((-2*pi*k)/N) + sin((-2*pi*k)/N)*1j;

			x_ret[k] = (x_even[k] + x_odd[k]*W);
			x_ret[k + N/2] = (x_even[k] - x_odd[k]*W);
		}

		return x_ret;
	}
}

std::vector<double> SignalProcessor::fft(std::vector<double> x) {
	auto windowed_x = this->hann(x);
	return this->magnitude(this->fft_complex(windowed_x));	
}
std::vector<double> SignalProcessor::generate_freq_bins(double fs, std::size_t N) {
	std::vector<double> freq_bins;
	freq_bins.resize(N);

	for (std::size_t i = 0; i < N; i++) {
		freq_bins[i] = i*(fs/N);
	}
	return freq_bins;
}
