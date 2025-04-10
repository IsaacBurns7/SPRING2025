import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats


def find_stable_frames(csv_file, x1_string, y1_string, x2_string, y2_string, window_size = 150, threshold=0.01):
    df = pd.read_csv(csv_file)

    df['distance'] = np.sqrt((df[x2_string] - df[x1_string]) ** 2 + (df[y2_string] - df[y1_string]) ** 2)

    max_distance = df['distance'].max()
    df['normalized_distance'] = df['distance'] / max_distance

    stable_frames = []
    stable_values = []

    if len(df) >= window_size:
        for i in range(len(df) - window_size + 1):
            window = df['normalized_distance'].iloc[i:i+window_size]
            mean_val = window.mean()
            std_val = window.std()

            if std_val <= threshold * mean_val:
                stable_frames.append(df['frame_no'].iloc[i])
                stable_values.append(mean_val)
    # if not stable_frames and len(df) > 10:
    #     from sklearn.cluster import KMeans

    #     X = df['normalized_distance'].values.reshape(-1, 1)
    #     max_clusters = min(5, len(df) // 3)
    #     if max_clusters >= 2:
    #         inertias = []
    #         for k in range(1, max_clusters+1):
    #             kmeans = KMeans(n_clusters=k, random_state=0)
    #             kmeans.fit(X)
    #             inertias.append(kmeans.inertia_)
    #         optimal_k

    result = pd.DataFrame({
        'frame_no': stable_frames,
        'stable_normalized_distance': stable_values
    })

    if not result.empty:
        result = pd.merge(result, df[['frame_no', 'distance', 'normalized_distance']], on = "frame_no")

    plt.figure(figsize=(12,8))

    plt.subplot(2, 1, 1)
    plt.plot(df['frame_no'], df['distance'], 'b-', label = 'Raw Distance')
    if not result.empty:
        plt.scatter(result['frame_no'], result['distance'], color='red', s=50, label = 'Stable Points')
        plt.axhline(y=result['distance'].mean(), color='r', linestyle='--',
                    label = f'Stable Value: {result["distance"].mean():.4f}')
        plt.title('Point Distance Over Frames')
        plt.xlabel('Frame Number')
        plt.ylabel('Distance')
        plt.grid(True, alpha=0.3)
        plt.legend()

    return df, result, plt, stable_frames

import sys

if len(sys.argv) < 2:
    print("Usage: python script.py <csv_file_path> output_image[constant_value] [tolerance]")
    print(sys.exit(1))

csv_file = sys.argv[1]
output_image = sys.argv[2] if len(sys.argv) > 2 else "distance_analysis.png"
window_size = int(sys.argv[3]) if len(sys.argv) > 3 else 5
threshold = float(sys.argv[4]) if len(sys.argv) > 4 else 0.05

x1_string = "pos_pixel_x-green"
y1_string = "pos_pixel_y-green" 
x2_string = "pos_pixel_x-hotpink"
y2_string = "pos_pixel_y-hotpink"
df, result, plt, stable_frames = find_stable_frames(csv_file, x1_string, y1_string, x2_string, y2_string, window_size, threshold)
if result.empty:
    print("No frames found where distance stabilizes to a constant value")
else:
    print(f"Found {len(result)} frames where distance stabilizes:")
    print(result)
    print(f"\nStable normalized distance value: {result['stable_normalized_distance'].mean():.4f}")
    print(f"Stable actual distance value: {result['distance'].mean():.4f}")
    print(f"First stable frame: {stable_frames[0]}")
    
plt.savefig(output_image, dpi = 300, bbox_inches='tight')
print(f"Plot saved as {output_image}")

