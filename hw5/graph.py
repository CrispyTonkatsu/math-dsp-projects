import matplotlib.pyplot as plt
import numpy as np


def mag_res(omega):
    return np.sqrt((1 + 0.999**12) - 2 * (0.999**6) * np.cos(6 * omega))


freq_space = np.linspace(0, 0.5, 1000)

omega = 2 * np.pi * freq_space

dB = 20 * np.log10(mag_res(omega))

plt.figure(figsize=(12, 6))
plt.title(r"Graph of dB over range $(0, \frac{f_s}{2})$")

plt.xlabel(r"$x f_s$ where $f_s = 1$")
plt.ylabel(r"dB")
plt.plot(freq_space, dB)

plt.grid(True)
plt.savefig("graph.png")
