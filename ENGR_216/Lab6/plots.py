# [30%, 10% for each spring] plots showing the position as a function of time for each of the springs tested
# [30%, 10% for each spring] the value of k for each spring, along with the uncertainty associated with this measurement

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import sys
from scipy.signal import find_peaks
import math

def make_plots(csv_file, pos_x_string, pos_y_string, color, height_threshold, mass = .550):
    df = pd.read_csv(csv_file)

    df['time (s)'] = df['time (ms)'] / 1000
    max_time = df['time (s)'].max()
    max_position_x = df[pos_x_string].max()

    plt.figure(figsize=(12,8))
    plt.subplot(2, 1, 1)
    plt.scatter(df['time (s)'], df[pos_x_string], color = {color}, alpha = 0.7, s = 20, label = "position x")

    plt.title(f'Position vs Time ({color} spring)', fontsize = 16, pad = 15)
    plt.xlabel('Time(s)')
    plt.ylabel('Position(m)', fontsize = 12)
    plt.grid(True, linestyle = '-', alpha = 0.7)
    plt.xlim(0, max_time)
    plt.ylim(0, max_position_x)
    
    plt.legend(loc = 'lower center', ncol = 3)
    plt.tight_layout

    x_raw_vals = df[pos_x_string].values
    t_vals = df['time (s)'].values

    valid_mask = ~np.isnan(x_raw_vals)

    x_vals = x_raw_vals[valid_mask]
    print("x_vals: ", x_vals)

    # height_threshold = np.mean(y_vals) + np.std(y_vals)
    height_threshold = height_threshold
    print('height_threshold: ', height_threshold)

    peaks, _ = find_peaks(x_vals, height = height_threshold)
    print("peaks: ", peaks)

    peak_times = t_vals[peaks]



    if len(peak_times) < 2:
        print("Not enough peaks found to calculate the period")
        return plt
    periods = np.diff(peak_times)
    average_period = np.mean(periods)
    std_dev_period = np.std(periods)

    # k = (4𝝅^2) * (m / T^2). 

    k = (4 * math.pi ** 2) * (mass / average_period ** 2)

    # dkdT = (4𝝅^2) * (m / T^3) * (-2)
    # dkdm = (4𝝅^2) * (1 / T^2)
    del_T = std_dev_period / 2
    del_m = 2 * (1/1000) # 2g

    dkdT = (4 * math.pi ** 2) * (mass / average_period ** 3) * (-2)
    dkdm = (4 * math.pi ** 2) * (1 / average_period ** 2)

    del_k = math.sqrt( (dkdT * del_T) ** 2 + (dkdm * del_m) ** 2 )
    
    print(f"Estimated period: {average_period:.4f} seconds")
    print(f"Standard deviation of periods: {std_dev_period:.4f} seconds")
    print(f"Reported k value: {k:.4f} N/m")
    print(f"Error in reported k value: {del_k:.4f} N/m")

    return plt

if len(sys.argv) < 2: 
    print("Usage: python script.py <csv_file_path> [output_file_path] <pos_x_string> <pos_y_string> ")
    print(sys.exit(1))

csv_file = sys.argv[1]
height_threshold = .55
output_file = sys.argv[2] if len(sys.argv) > 2 else "position_plot.png"
color = sys.argv[3] if len(sys.argv) > 3 else "blue"
pos_x_string = sys.argv[4] if len(sys.argv) > 4 else "r_x-hotpink"
pos_y_string = sys.argv[5] if len(sys.argv) > 5 else "r_y-hotpink"


plt = make_plots(csv_file, pos_x_string, pos_y_string, color, height_threshold)

plt.savefig(output_file, dpi = 300, bbox_inches = 'tight')