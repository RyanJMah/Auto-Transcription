import os
import click
import csv
import numpy as np
import matplotlib.pyplot as plt

def Hann(x):
	for i in range(len(x)):
		multiplier = (0.5*(1 - np.cos(2*np.pi*i/(len(x) - 1))))
		x[i] = multiplier*x[i]


@click.command()
@click.option("--frequency-domain", "frequency", type = bool)
@click.argument('file')
def plot_csv(file, frequency):
	filepath = os.path.join(os.getcwd(), file)
	with open(filepath, "r") as f:
		data = tuple(csv.reader(f))
		x, y = (list(zip(*data)))

	x = [float(x_i) for x_i in x]
	y = [float(y_i) for y_i in y]

	term = np.mean(y)
	y = [yi - term for yi in y]

	if frequency:

		Hann(y)
		y = abs(np.fft.fft(x))
		
		fs = 1/(x[1] - x[0])
		print(fs)
		x = [i*(fs/len(x)) for i in range(len(x))]


	plt.plot(x, y)
	plt.show()


