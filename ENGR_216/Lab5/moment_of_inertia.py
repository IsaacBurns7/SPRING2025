import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sys
import math

def find_moment_of_inertia(csv_file, velocity_x_string, velocity_y_string, stable_radius,
                  beforeLeftBoundary, beforeRightBoundary,
                  afterLeftBoundary, afterRightBoundary,
                  moi_mass = 1.32e-6, mass = 0.020): #kg m^2 / s
    df = pd.read_csv(csv_file)

    df['velocity'] = np.sqrt(df[velocity_x_string] ** 2 + df[velocity_y_string] ** 2)
    stable_radius = float(stable_radius) 
    
    avg_velocity_before = df.loc[(df['frame_no'] >= int(beforeLeftBoundary)) & (df['frame_no'] < int(beforeRightBoundary)), 'velocity'].mean()
    avg_velocity_after = df.loc[(df['frame_no'] >= int(afterLeftBoundary)) & (df['frame_no'] < int(afterRightBoundary)), 'velocity'].mean(); 
    I_mass = moi_mass + mass * stable_radius ** 2
    w_new = avg_velocity_before / stable_radius
    w_old = avg_velocity_after / stable_radius
    
    moi_object = (w_new - w_old / w_old) * I_mass

    dIobj_dImass = (w_new - w_old) / w_old 
    dIobj_dWnew = I_mass / w_old 
    dIobj_dWold = -1 * I_mass / w_old ** 2
    dImass_dR = 2 * mass * stable_radius
    dImass_dM = stable_radius ** 2
    dWold_dV = 1 / stable_radius
    dWold_dR = - 1 * avg_velocity_before / stable_radius ** 2
    dWnew_dV = 1 / stable_radius
    dWnew_dR = - 1 * avg_velocity_after / stable_radius ** 2

    del_R = 0.001 #1 mm
    del_M = 0.001 #1 g
    del_V = 0.001 #1 mm/s

    delI_mass = math.sqrt((dImass_dR * del_R) ** 2 + 
                          (dImass_dM * del_M) ** 2)
    delW_old = math.sqrt((dWold_dV * del_V) ** 2 + 
                         (dWold_dR * del_R) ** 2)
    delW_new = math.sqrt((dWnew_dV * del_V) ** 2 + 
                         (dWnew_dR * del_R) ** 2)

    moi_object_uncertainty = math.sqrt((dIobj_dImass * delI_mass) ** 2 +
                                       (dIobj_dWnew * delW_new) ** 2 + 
                                       (dIobj_dWold * delW_old) ** 2)

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


    return plt, moi_object, moi_object_uncertainty

if len(sys.argv) < 7:
    print("Usage: python script.py <csv_file_path> <stable_distance> <beforeLeftBoundary> <beforeRightBoundary> <afterLeftBoundary> <afterRightBoundary> [output_velocity_plot_file]\nPlease note boundaries are in frame.")
    print(sys.exit(1))

csv_file = sys.argv[1]
stable_radius = sys.argv[2]
beforeLeftBoundary = sys.argv[3]
beforeRightBoundary = sys.argv[4]
afterLeftBoundary = sys.argv[5]
afterRightBoundary = sys.argv[6]
output_file = sys.argv[7] if len(sys.argv) > 2 else "velocity_analysis.png"

velocity_x_string = "v_x-darkorange"
velocity_y_string = "v_y-darkorange"


plt, moment_of_inertia_object, moment_of_inertia_object_uncertainty = find_moment_of_inertia(csv_file, velocity_x_string, velocity_y_string, stable_radius, 
                       beforeLeftBoundary, beforeRightBoundary, 
                       afterLeftBoundary, afterRightBoundary)
print("Moment of Inertia found(kg m^2): ", moment_of_inertia_object)
print("Uncertainty of Moment of Inertia found(kg m^2): ", moment_of_inertia_object_uncertainty)

#df, plt = find_velocity(csv_file, velocity_x_string, velocity_y_string)
plt.savefig(output_file, dpi = 300, bbox_inches = 'tight')

# python3 moment_of_inertia.py ./Lab5-Clipped/2_pentagon_trial.csv 0.0493 100 200 400 600 ./Lab5-graphs/velocity/2_pentagon_trial.png
# circle1: 0.0793 300 400 500 600
# circle2: 0.0709 180 350 400 800
# pentagon1: 0.0597 220 350 450 750
# pentagon2: 0.0493 100 200 400 600
