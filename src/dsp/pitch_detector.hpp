#ifndef PITCH_DETECTOR
#define PITCH_DETECTOR

class PitchDetector {
	private:
		std::vector<double> harmonic_product_spectrum(std::vector<double> X);

	public:
		PitchDetector();

		double detect_pitch(std::vector<double> X);

};


#endif
