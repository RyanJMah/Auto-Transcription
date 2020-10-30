import os
import numpy as np
from pydub import AudioSegment

THIS_DIR = os.path.dirname(os.path.abspath(__file__))

def read_mp3(path):
    sound = AudioSegment.from_wav(path)

    samples = list(np.frombuffer(sound.raw_data, dtype = np.int32))

    T = 1/sound.frame_rate
    times = [T*i for i in range(len(samples))]

    return {"time": times, "amplitude": samples}


def test():
    import matplotlib.pyplot as plt
    import csv
    data = read_mp3("/mnt/c/shared/Personal/Projects/Auto-Transcription/resources/c_major_115_bpm.wav")

    with open("samples.csv", "w") as f:
        writer = csv.writer(f)
        for t, f in zip(data["time"], data["amplitude"]):
            writer.writerow([t, f])



if __name__ == "__main__":
    test()