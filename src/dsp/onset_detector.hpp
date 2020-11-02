#ifndef ONSET_DETECTOR
#define ONSET_DETECTOR

#include <vector>
#include <functional>
#include "signal.hpp"

struct DetectionParams {
	double fs;
	double num_bins;
	double t_hop;
	double t_overlap;
	std::function<double(double)> weighting_function;
};

class OnsetDetector {
	private:
		std::vector<Signal> short_time_fft(Signal x_t);

		double weighted_avg(std::vector<double> x);
		Signal generate_detection_curve(Signal x_t);
		
		Signal peak_picking(Signal x_t);

	public:
		OnsetDetector(double fs_in, double num_bins_in);
		DetectionParams params;

		Signal detect_onsets(Signal x_t);

};





#endif
