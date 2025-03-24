import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

file_path = "puck3-clipped.csv"
df = pd.read_csv(file_path)

time = df["time (ms)"].values / 1000 #Convert ms to s
dt = np.gradient(time) #accounts for non-uniform time steps

x_pos = df["pos_pixel_x-green"].values * 0.4179410296 / 1000
y_pos = df["pos_pixel_y-green"].values * 0.4179410296 / 1000

v_x_fwd = np.zeros_like(x_pos)
v_y_fwd = np.zeros_like(y_pos)
v_x_bwd = np.zeros_like(x_pos)
v_y_bwd = np.zeros_like(y_pos)
v_x_ctr = np.zeros_like(x_pos)
v_y_ctr = np.zeros_like(y_pos)

a_x_fwd = np.zeros_like(x_pos)
a_y_fwd = np.zeros_like(y_pos)
a_x_bwd = np.zeros_like(x_pos)
a_y_bwd = np.zeros_like(y_pos)
a_x_ctr = np.zeros_like(x_pos)
a_y_ctr = np.zeros_like(y_pos)

# Forward finite difference for velocity (except last point)
v_x_fwd[:-1] = (x_pos[1:] - x_pos[:-1]) / dt[:-1]
v_y_fwd[:-1] = (y_pos[1:] - y_pos[:-1]) / dt[:-1]

# Backward difference for velocity (except first point)
v_x_bwd[1:] = (x_pos[1:] - x_pos[:-1]) / dt[1:]
v_y_bwd[1:] = (y_pos[1:] - y_pos[:-1]) / dt[1:]

# Centered difference for velocity (except first and last points)
v_x_ctr[1:-1] = (x_pos[2:] - x_pos[:-2]) / (2 * dt[1:-1])
v_y_ctr[1:-1] = (y_pos[2:] - y_pos[:-2]) / (2 * dt[1:-1])

# Forward difference for acceleration (except last point)
a_x_fwd[:-1] = (v_x_fwd[1:] - v_x_fwd[:-1]) / dt[:-1]
a_y_fwd[:-1] = (v_y_fwd[1:] - v_y_fwd[:-1]) / dt[:-1]

# Backward difference for acceleration (except first point)
a_x_bwd[1:] = (v_x_bwd[1:] - v_x_bwd[:-1]) / dt[1:]
a_y_bwd[1:] = (v_y_bwd[1:] - v_y_bwd[:-1]) / dt[1:]

# Centered difference for acceleration (except first and last points)
a_x_ctr[1:-1] = (v_x_ctr[2:] - v_x_ctr[:-2]) / (2 * dt[1:-1])
a_y_ctr[1:-1] = (v_y_ctr[2:] - v_y_ctr[:-2]) / (2 * dt[1:-1])

# Store computed values in the dataframe
df["v_x_fwd"], df["v_y_fwd"] = v_x_fwd, v_y_fwd
df["v_x_bwd"], df["v_y_bwd"] = v_x_bwd, v_y_bwd
df["v_x_ctr"], df["v_y_ctr"] = v_x_ctr, v_y_ctr

df["a_x_fwd"], df["a_y_fwd"] = a_x_fwd, a_y_fwd
df["a_x_bwd"], df["a_y_bwd"] = a_x_bwd, a_y_bwd
df["a_x_ctr"], df["a_y_ctr"] = a_x_ctr, a_y_ctr

# Set up the figure with subplots
fig, axes = plt.subplots(3, 2, figsize=(12, 12))

titles = [
    "Position(x)", "Position (y)",
    "Velocity (x)", "Velocity (y)",
    "Acceleration (x)", "Acceleration (y)",
]

data = [
    (x_pos,),
    (y_pos,),
    (v_x_fwd, v_x_bwd, v_x_ctr),
    (v_y_fwd, v_y_bwd, v_y_ctr),
    (a_x_fwd, a_x_bwd, a_x_ctr),
    (a_y_fwd, a_y_bwd, a_y_ctr),
]

labels = ["Forward", "Backward", "Centered"]

print(x_pos)
print(time)
# Plot each graph
for i, ax in enumerate(axes.flat):
    for j, diff_type in enumerate(data[i]):
        if i >= 2:
            ax.plot(time, diff_type, label=labels[j], alpha=0.7)
        else:
            ax.plot(time, diff_type)
    ax.set_xlabel("Time (s)")
    ax.set_ylabel("Meters" if i < 2 else "m/s" if i < 4 else "m/s²")
    ax.set_title(titles[i])
    ax.legend()
    ax.grid()

    

plt.subplots_adjust(hspace=0.5)

plt.tight_layout()

plt.savefig("puck3.png")
#plt.show()
