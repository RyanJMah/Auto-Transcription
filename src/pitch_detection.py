import os
import numpy as np
import audio_io as io
import matplotlib.pyplot as plt

def to_freq_series(t, A, t_step, sample_rate = 44.1E3, epsilon = 1E-3):
    """A basic frequency detection thing"""
    assert(len(t) == len(A))

    t_elapsed = 0
    while len(A) != 0:

        index = 0
        for i in range(len(t)):
            if abs(t[i] - (t_elapsed + t_step)) < epsilon:
                index = i
                break

        print(f"index = {index}")
        input("Press enter to continue: ")

        freqs = [i*(sample_rate/index) for i in range(index)]
        A_omega = abs(np.fft.fft(A[:i]))

        plt.plot(freqs, A_omega)
        plt.show()

        t = t[i:]
        A = A[i:]


        t_elapsed += t_step


def main():
    import csv
    with open(r"C:\shared\Personal\Projects\Auto-Transcription\src\dump\samples.csv", "r") as f:
        data = tuple(csv.reader(f))
        t, A = (list(zip(*data)))

    t = [float(t_i) for t_i in t]
    A = [float(A_i) for A_i in A]

    to_freq_series(t, A, t_step = 0.1)


if __name__ == "__main__":
    main()

