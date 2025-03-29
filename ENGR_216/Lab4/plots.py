import pandas as pd
import os
import math
import numpy as np
import matplotlib.pyplot as plt

m = 0.0280 
del_m = 0.0005 

# def find_stddev_velocity(file_path):
#     df = pd.read_csv(file_path)

#     vel1_mean = 0.0
#     vel2_mean = 0.0
#     n = 0

#     for vel1_x, vel1_y, vel2_x, vel2_y, in zip(df['v_x-green'], 
#         df['v_y-green'], 
#         df['v_x-hotpink'], 
#         df['v_y-hotpink']):

#         vel1_magnitude = math.sqrt(vel1_x ** 2 + vel1_y ** 2)
#         vel2_magnitude = math.sqrt(vel2_x ** 2 + vel2_y ** 2)
#         vel1_mean += vel1_magnitude
#         vel2_mean += vel2_magnitude
#         n += 1

#     vel1_mean /= n
#     vel2_mean /= n





def find_momentum_and_velocity(file_path, beforeTimestamp, afterTimestamp):
    df = pd.read_csv(file_path)

    vel1_magnitudes = np.sqrt(df["v_x-green"] ** 2 + df["v_y-green"])
    vel1_std_dev = np.std(vel1_magnitudes)
    vel2_magnitudes = np.sqrt(df["v_x-hotpink"] ** 2 + df["v_y-hotpink"])
    vel2_std_dev = np.std(vel2_magnitudes)

    theta = 0
    theta_count = 0

    momentumBefore = 0
    momentumBeforeCount = 0
    momentumAfter = 0
    momentumAfterCount =0
    
    kineticEnergyBefore = 0
    kineticEnergyBeforeCount = 0
    kineticEnergyAfter = 0
    kineticEnergyAfterCount = 0

    for vel1_x, vel1_y, vel2_x, vel2_y, timestamp, in zip(df['v_x-green'], 
        df['v_y-green'], 
        df['v_x-hotpink'], 
        df['v_y-hotpink'],
        df['frame_no']):
        

        #find theta
        dot = vel1_x * vel2_x + vel1_y * vel2_y
        vel1_magnitude = math.sqrt(vel1_x ** 2 + vel1_y ** 2)
        vel2_magnitude = math.sqrt(vel2_x ** 2 + vel2_y ** 2)
        magnitude = vel1_magnitude * vel2_magnitude
        theta_curr = math.acos(dot / magnitude)

        #del velocities
        del_v1 = vel1_std_dev / 2
        del_v2 = vel2_std_dev / 2

        #find momentum
        #del_v1 is std dev / 2
        momentum1 = vel1_magnitude * m
        del_momentum1 = math.sqrt((vel1_magnitude * del_m) ** 2 + (m * del_v1) ** 2)
        momentum2 = vel2_magnitude * m
        del_momentum2 = math.sqrt((vel2_magnitude * del_m) ** 2 + (m * del_v2) ** 2)
        momentum_total = momentum1 + momentum2
        del_momentum_total = del_momentum1 + del_momentum2

        #find kinetic energy
        kinetic_energy1 = (1 / 2) * m * vel1_magnitude ** 2
        del_kinetic_energy1 = math.sqrt(((vel1_magnitude ** 2 / 2) * del_m) ** 2 + (m * vel1_magnitude * del_v1) ** 2)
        kinetic_energy2 = (1 / 2) * m * vel2_magnitude ** 2
        del_kinetic_energy2 = math.sqrt(((vel2_magnitude ** 2 / 2) * del_m) ** 2 + (m * vel2_magnitude * del_v2) ** 2)
        kinetic_energy_total = kinetic_energy1 + kinetic_energy2
        del_kinetic_energy_total = del_kinetic_energy1 + del_kinetic_energy2

        print(timestamp)
        if(timestamp <= beforeTimestamp):
            theta += theta_curr
            theta_count += 1

            momentumBefore += momentum_total
            momentumBeforeCount += 1

            kineticEnergyBefore += kinetic_energy_total
            kineticEnergyBeforeCount += 1
        else:
            momentumAfter += momentum_total
            momentumAfterCount += 1

            kineticEnergyAfter += kinetic_energy_total
            kineticEnergyAfterCount += 1
    momentumBefore = momentumBefore / momentumBeforeCount
    momentumAfter = momentumAfter / momentumAfterCount

    data = {"theta": theta,
             "momentum": {
                 "before": {
                     "val" : momentumBefore,
                     "count": momentumAfterCount

                 },
                 "after": {
                     "val": momentumAfter,
                     "count": momentumAfterCount
                 }
             }}
    return  data

csv_dir = "shared/"
filepath1 = "1_collision_225_clipped.csv"
timeStamp1Before = 740
timeStamp1After = 745
collision1Data = find_momentum_and_velocity(os.path.join(csv_dir, filepath1), timeStamp1Before, timeStamp1After)
theta1 = collision1Data["theta"]

# Define the collision angles and momentum values
angles = [theta1, 17, 45, 70, 90, 110, 130, 180]

# Example momentum values (replace with your actual data)
momentum_before = [collision1Data["momentum"]["before"]["val"], 8, 15, 18, 7, 17, 19, 22] #total momentum
del_momentum_before = [2, 1.5, 3, 2.5, 1, 2, 2.5, 3] #total del momentum
momentum_after = [9, 6, 14, 17, 6, 16, 18, 23] 
del_momentum_after = [1.8, 1.2, 2.8, 2.2, 0.9, 1.8, 2.3, 2.7]

plt.figure(figsize = (10,6))

bar_width = 0.35
r1 = np.arange(len(angles))
print(r1)
r2 = [x + bar_width for x in r1]

plt.bar(r1, momentum_before, color = "blue", width = bar_width, edgecolor = "white", 
        label = "Before", yerr = del_momentum_before, capsize = 5)
plt.bar(r2, momentum_after, color = "orange", width = bar_width, edgecolor = "white",
        label = "After", yerr = del_momentum_after, capsize = 5)

plt.xlabel('Collision angle(degrees)', fontweight='bold')
plt.ylabel("Momentum(kg * cm/s)", fontweight = 'bold')
plt.title('Px Momentum Before and After Collision', fontweight='bold')
plt.xticks([r + bar_width / 2 for r in range(len(angles))], angles)

plt.legend()

plt.grid(axis='y', linestyle = '--', alpha = 0.7)

plt.tight_layout()
plt.show()
