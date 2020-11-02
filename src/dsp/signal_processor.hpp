#ifndef SIGNAL_PROCESSOR
#define SIGNAL_PROCESSOR

#include <complex>
#include <vector>

class SignalProcessor {
	private:
		std::vector<std::complex<double>> fft_complex(std::vector<std::complex<double>> x);

	public:
		SignalProcessor();

		std::vector<double> fft(std::vector<double> x);
		std::vector<double> generate_freq_bins(double fs, std::size_t N);

		template <class T>
		std::vector<std::complex<double>> hann(T x);
		
		template <class T>
		std::vector<double> magnitude(T x);

};

#endif
