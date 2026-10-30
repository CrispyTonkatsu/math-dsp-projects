import numpy as np

B_hz = 20
psi_hz = 5000

B = 2 * np.pi * (B_hz / 44100)
psi = 2 * np.pi * (psi_hz / 44100)

phi = B / 2

R = 1 - (B / 2)
theta = np.acos((2 * R) / (1 + R**2) * np.cos(psi))
A = (1 - R**2) * np.sin(theta)

print(
    f"y_t & = {A}x_t \\\\\n + & {2 * R * np.cos(theta)}y_{{t-1}} \\\\\n - & {R**2}y_{{t-2}}"
)

h = [1, 0, 0]
y = [0, 0, 0]

for t in range(3):
    y[t] = (
        A * h[t]
        + 2 * R * np.cos(theta) * (y[t - 1] if t - 1 >= 0 else 0)
        - R**2 * (y[t - 2] if t - 2 >= 0 else 0)
    )

for t in range(3):
    print(f"y_{t} & = {y[t]} \\\\")
