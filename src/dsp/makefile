all: main

main: main.cpp signal_processor.cpp onset_detector.cpp ../io/audio_decoder.cpp
	g++ -o main main.cpp signal_processor.cpp onset_detector.cpp ../io/audio_decoder.cpp

clean:
	rm main
