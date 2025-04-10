import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys


# [15%] A plot showing the angular momentum of the L shape and 20 g mass, 
# and total as a function of time. This plot should include data before and 
# after dropping the mass on the rotating shape. 
# I = Icm + Md^2 
#moi = moment of intertia
def find_momentum_of_system(csv_file, output_file,
                            x1_string, y1_string, x2_string, y2_string, 
                            velocity_x_mass_string, velocity_y_mass_string, 
                            moi_mass = 1.32e-6, moi_object = 9.7e-4, mass = 0.020): #units in kg m^2
    df = pd.read_csv(csv_file)

    df['mass_radius'] = np.sqrt((df[x2_string] - df[x1_string]) ** 2 + (df[y2_string] - df[y1_string]) ** 2)
    df['mass_velocity'] = np.sqrt((df[velocity_x_mass_string] ** 2 + df[velocity_y_mass_string] ** 2) ** 2)
    df['new_moi_mass'] = moi_mass + mass * df['mass_radius'] ** 2
    df['angular_speed'] = df["mass_velocity"] / df['mass_radius']
    df['angular_momentum_mass'] = df['new_moi_mass'] * df['angular_speed']
    df['angular_momentum_object'] = moi_object * df['angular_speed']
    df['time (s)'] = df['time (ms)'] * 1000

    max_second = df['time (s)'].max()
    max_angular_momentum = df['angular_momentum_mass'].max() + df['angular_momentum_object'].max() * 0.3

    # for i in range(len(df)):
    #     new_moi_mass = moi_mass + mass * df['radius_mass'].iloc[i] ** 2 
    #     angular_speed = df[velocity_mass_string] / df['radius_mass'].iloc[i]
    #     angular_momentum_mass = new_moi_mass * angular_speed
    #     angular_momentum_object = moi_object * angular_speed

    plt.figure(figsize=(12,8))

    plt.subplot(2, 1, 1)
    plt.scatter(df['time (s)'], df['angular_momentum_object'], color = "blue", alpha = 0.7, s = 20, label = 'L-Shape')
    plt.scatter(df['time (s)'], df['angular_momentum_mass'], color = "red", alpha = 0.7, s = 20, label = 'Mass')
    plt.scatter(df['time (s)'], df['angular_momentum_mass'] + df['angular_momentum_object'], color = "green", alpha = 0.7, s = 20, label = 'Composite')

    plt.title('Angular Momentum', fontsize = 16, pad = 15)
    plt.xlabel('time (s)', fontsize= 12) #figure out how to turn frame into s
    plt.ylabel('L (kg·m²/s)', fontsize = 12)
    plt.grid(True, linestyle = '-', alpha = 0.7)
    plt.xlim(0, max_second)
    plt.ylim(0, max_angular_momentum)

    plt.legend(loc = 'lower center', ncol=3)
    plt.tight_layout()

    return df, plt

if len(sys.argv) < 2:
    print("Usage: python script.py <csv_file_path> [<output_plot_file_path>]")
    print(sys.exit(1))

csv_file = sys.argv[1]
output_plot_file_path = sys.argv[2] if len(sys.argv) > 2 else "momentum_analysis.png"

x1_string = "r_x-green"
y1_string = "r_y-green" 
x2_string = "r_x-hotpink"
y2_string = "r_y-hotpink"
velocity_x_mass_string = "v_x-green"
velocity_y_mass_string = "v_y-green"

df, plt = find_momentum_of_system(csv_file, output_plot_file_path, 
                            x1_string, y1_string, x2_string, y2_string,
                            velocity_x_mass_string, velocity_y_mass_string)

plt.savefig(output_plot_file_path, dpi = 300, bbox_inches='tight')


