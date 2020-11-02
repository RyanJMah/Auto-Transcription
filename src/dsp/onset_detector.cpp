#include <vector>
#include <cmath>
#include <cassert>
#include "signal.hpp"
#include "signal_processor.hpp"
#include "onset_detector.hpp"

std::vector<double> slice_vector(std::vector<double> in, std::size_t start, std::size_t stop) {
	std::vector<double> out;
	out.resize(stop - start + 1);

	for (std::size_t i = 0, j = start; j <= stop; i++, j++) {
		out[i] = in[j];
	}
	return out;
}

OnsetDetector::OnsetDetector(double fs_in, double num_bins_in) {
	assert(log2(num_bins_in) > 0.00001);
	
	this->params.fs = fs_in;
	this->params.num_bins = num_bins_in;
	
	this->params.t_hop = (1/this->params.fs)*this->params.num_bins;
	this->params.t_overlap = 0;
	this->params.weighting_function = [](double k){ return k*k; };
}


std::vector<Signal> OnsetDetector::short_time_fft(Signal x_t) {
	SignalProcessor sp = SignalProcessor();		// initialize signal processing library

	auto t = x_t.independant;
	auto x = x_t.dependant;

	std::vector<Signal> X_m;		// return signal

	std::size_t bins_hop = this->params.t_hop * this->params.fs;			// convert t_hop and t_overlap to a number of bins
	std::size_t bins_overlap = this->params.t_overlap * this->params.fs;

	std::size_t bins_step = bins_hop - bins_overlap;
	for (std::size_t i = 0; i < t.size(); i += bins_step) {
		if ( (i + bins_step) > (t.size() - 1) ) {
			i += (t.size() - 1) - i;	// make sure the iteration encapsulates the entire input signal
		}

		auto temp_independant = slice_vector(t, i, i + bins_hop);
		auto temp_dependant = sp.fft( slice_vector(x, i, i + bins_hop), this->params.fs ).dependant;
		X_m.push_back({temp_independant, temp_dependant});
	}
	return X_m;
}


double OnsetDetector::weighted_avg(std::vector<double> x) {
	double sum = 0;
	for (std::size_t i = 0; i < x.size(); i++) {
		sum += this->params.weighting_function(i) * (x[i]*x[i]);
	}
	return sum/x.size();
}
Signal OnsetDetector::generate_detection_curve(Signal x_t) {
	auto stft = this->short_time_fft(x_t);

	Signal detection_curve;
	for (std::size_t i = 0; i < stft.size(); i++) {
		auto t = stft[i].independant;
		auto X = stft[i].dependant;
	
		detection_curve.independant.push_back(t[0]);
		detection_curve.dependant.push_back(this->weighted_avg(X));
	}
	return detection_curve;
}


Signal OnsetDetector::detect_onsets(Signal x_t) {
	Signal detection_curve = this->generate_detection_curve(x_t);
	

	return detection_curve;
}

