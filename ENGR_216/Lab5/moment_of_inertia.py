import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys

def find_velocity(csv_file, velocity_x_string, velocity_y_string):
    df = pd.read_csv(csv_file)

    df['velocity'] = np.sqrt(df[velocity_x_string] ** 2 + df[velocity_y_string] ** 2)
    max_frame = df['frame_no'].max()
    max_velocity = df['velocity'].max()

    plt.figure(figsize=(12,8))
    plt.subplot(2, 1, 1)
    plt.scatter(df['frame_no'], df['velocity'], color = "blue", alpha = 0.7, s = 20, label = "velocity")

    plt.title("Velocity vs Frame", fontsize = 16, pad = 15)
    plt.xlabel('Frame')
    plt.ylabel('Velocity(m/s)', fontsize = 12)
    plt.grid(True, linestyle = '-', alpha = 0.7)
    plt.xlim(0, max_frame)
    plt.ylim(0, max_velocity)

    plt.legend(loc = 'lower center', ncol = 3)
    plt.tight_layout


    return df, plt

if len(sys.argv) < 2:
    print("Usage: python script.py <csv_file_path> [<output_plot_file_path>]")
    print(sys.exit(1))

csv_file = sys.argv[1]
output_file = sys.argv[2] if len(sys.argv) > 2 else "velocity_analysis.png"

velocity_x_string = "v_x-darkorange"
velocity_y_string = "v_y-darkorange"
df, plt = find_velocity(csv_file, velocity_x_string, velocity_y_string)
plt.savefig(output_file, dpi = 300, bbox_inches = 'tight')