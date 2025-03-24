import csv
import math

def read_csv_columns(file_path):
    # Initialize a dictionary to store columns
    columns = {}
    
    try:
        with open(file_path, 'r', newline='') as csv_file:
            # Create a CSV reader
            csv_reader = csv.reader(csv_file)
            
            # Read the header row
            headers = next(csv_reader)
            
            # Initialize lists for each column
            for header in headers:
                columns[header] = []
            
            # Read data rows
            for row in csv_reader:
                # Add each value to the corresponding column list
                for i, value in enumerate(row):
                    if i < len(headers):  # Ensure we don't go out of bounds
                        columns[headers[i]].append(value)
            
            print(f"Successfully read {len(next(iter(columns.values())))} rows from {file_path}")
            return columns
            
    except FileNotFoundError:
        print(f"Error: File '{file_path}' not found.")
        return None
    except Exception as e:
        print(f"Error reading CSV file: {e}")
        return None

def calculate_mu(acceleration_y_vector, acceleration_x_vector, theta):
    g = 9.8
    avg_acceleration = 0
    avg_mu = 0
    std_dev_mu = 0
    count = 0
    n = len(acceleration_x_vector)
    # g_y = g * math.sin(theta)
    # g_x = g * math.cos(theta)

    for i in range(n):
        if(acceleration_x_vector[i] == '' or acceleration_y_vector[i] == ''):
            continue
        a_x = float(acceleration_x_vector[i])
        a_y = float(acceleration_y_vector[i])
        acceleration = math.sqrt(a_x ** 2 + a_y ** 2)
        mu  = abs((g * math.sin(theta) - acceleration ) / (g * math.cos(theta)))
        
        avg_mu += mu
        count += 1
    
#double pass for std dev
    for i in range(n):
        if(acceleration_x_vector[i] == '' or acceleration_y_vector[i] == ''):
            continue
        a_x = float(acceleration_x_vector[i])
        a_y = float(acceleration_y_vector[i])
        acceleration = math.sqrt(a_x ** 2 + a_y ** 2)
        mu  = abs(g * math.sin(theta) - acceleration ) / (g * math.cos(theta))
        # print("acceleration: ",acceleration)
        # print("mu: ", mu)

        std_dev_mu = (mu - avg_mu) ** 2

    std_dev_mu /= count
    std_dev_mu = math.sqrt(std_dev_mu)
    avg_mu /= count

    ans = [avg_mu, std_dev_mu]
    return ans

if __name__ == "__main__":

    y = 775 
    x = 459
    theta = math.asin(x / math.sqrt(x ** 2 + y ** 2))
    g = 9.8

    #print(theta)

    #avg_mu = g * math.sin(theta) - avg_acceleration 

    bigwood1_file_path = "./Big Wood/kinetic_bigwood_1_clipped.csv"
    bigwood2_file_path = "./Big Wood/kinetic_bigwood_2_clipped.csv"
    bigwood3_file_path = "./Big Wood/kinetic_bigwood_3_clipped.csv"
    bigwood4_file_path = "./Big Wood/kinetic_bigwood_4_clipped.csv"
    bigwood5_file_path = "./Big Wood/kinetic_bigwood_5_clipped.csv"
    bigwood6_file_path = "./Big Wood/kinetic_bigwood_6_clipped.csv"
    bigwood7_file_path = "./Big Wood/kinetic_bigwood_7_clipped.csv"
    bigwood8_file_path = "./Big Wood/kinetic_bigwood_8_clipped.csv"
    bigwood9_file_path = "./Big Wood/kinetic_bigwood_9_clipped.csv"

    bigwood1_data_columns = read_csv_columns(bigwood1_file_path)
    bigwood2_data_columns = read_csv_columns(bigwood2_file_path)
    bigwood3_data_columns = read_csv_columns(bigwood3_file_path)
    bigwood4_data_columns = read_csv_columns(bigwood4_file_path)
    bigwood5_data_columns = read_csv_columns(bigwood5_file_path)
    bigwood6_data_columns = read_csv_columns(bigwood6_file_path)
    bigwood7_data_columns = read_csv_columns(bigwood7_file_path)
    bigwood8_data_columns = read_csv_columns(bigwood8_file_path)
    bigwood9_data_columns = read_csv_columns(bigwood9_file_path)

    bigrubber1_file_path = "./Big Rubber/kinetic_bigrubber_1_clipped.csv"
    bigrubber2_file_path = "./Big Rubber/kinetic_bigrubber_2_clipped.csv"
    bigrubber3_file_path = "./Big Rubber/kinetic_bigrubber_3_clipped.csv"
    bigrubber4_file_path = "./Big Rubber/kinetic_bigrubber_4_clipped.csv"
    bigrubber5_file_path = "./Big Rubber/kinetic_bigrubber_5_clipped.csv"
    bigrubber6_file_path = "./Big Rubber/kinetic_bigrubber_6_clipped.csv"
    bigrubber7_file_path = "./Big Rubber/kinetic_bigrubber_7_clipped.csv"
    bigrubber8_file_path = "./Big Rubber/kinetic_bigrubber_8_clipped.csv"
    bigrubber9_file_path = "./Big Rubber/kinetic_bigrubber_9_clipped.csv"

    bigrubber1_data_columns = read_csv_columns(bigrubber1_file_path)
    bigrubber2_data_columns = read_csv_columns(bigrubber2_file_path)
    bigrubber3_data_columns = read_csv_columns(bigrubber3_file_path) 
    bigrubber4_data_columns = read_csv_columns(bigrubber4_file_path)
    bigrubber5_data_columns = read_csv_columns(bigrubber5_file_path)
    bigrubber6_data_columns = read_csv_columns(bigrubber6_file_path) 
    bigrubber7_data_columns = read_csv_columns(bigrubber7_file_path)
    bigrubber8_data_columns = read_csv_columns(bigrubber8_file_path)
    bigrubber9_data_columns = read_csv_columns(bigrubber9_file_path) 

    bigwood1_acceleration_x = bigwood1_data_columns["a_x-green"]
    bigwood1_acceleration_y = bigwood1_data_columns["a_y-green"]
    bigwood1_mu_vector = calculate_mu(bigwood1_acceleration_x,bigwood1_acceleration_y, theta)
    bigwood1_mu = bigwood1_mu_vector[0]
    bigwood1_uncertainty = bigwood1_mu_vector[1] / 2 #std_dev / 2

    bigwood2_acceleration_x = bigwood2_data_columns["a_x-green"]
    bigwood2_acceleration_y = bigwood2_data_columns["a_y-green"]
    bigwood2_mu_vector = calculate_mu(bigwood2_acceleration_x,bigwood2_acceleration_y, theta)
    bigwood2_mu = bigwood2_mu_vector[0]
    bigwood2_uncertainty = bigwood2_mu_vector[1] / 2 #std_dev / 2
    
    bigwood3_acceleration_x = bigwood3_data_columns["a_x-green"]
    bigwood3_acceleration_y = bigwood3_data_columns["a_y-green"]
    bigwood3_mu_vector = calculate_mu(bigwood3_acceleration_x,bigwood3_acceleration_y, theta)
    bigwood3_mu = bigwood3_mu_vector[0]
    bigwood3_uncertainty = bigwood3_mu_vector[1] / 2 #std_dev / 2

    bigwood4_acceleration_x = bigwood4_data_columns["a_x-green"]
    bigwood4_acceleration_y = bigwood4_data_columns["a_y-green"]
    bigwood4_mu_vector = calculate_mu(bigwood4_acceleration_x,bigwood4_acceleration_y, theta)
    bigwood4_mu = bigwood4_mu_vector[0]
    bigwood4_uncertainty = bigwood4_mu_vector[1] / 2 #std_dev / 2

    bigwood5_acceleration_x = bigwood5_data_columns["a_x-green"]
    bigwood5_acceleration_y = bigwood5_data_columns["a_y-green"]
    bigwood5_mu_vector = calculate_mu(bigwood5_acceleration_x,bigwood5_acceleration_y, theta)
    bigwood5_mu = bigwood5_mu_vector[0]
    bigwood5_uncertainty = bigwood5_mu_vector[1] / 2 #std_dev / 2

    bigwood6_acceleration_x = bigwood6_data_columns["a_x-green"]
    bigwood6_acceleration_y = bigwood6_data_columns["a_y-green"]
    bigwood6_mu_vector = calculate_mu(bigwood6_acceleration_x,bigwood6_acceleration_y, theta)
    bigwood6_mu = bigwood6_mu_vector[0]
    bigwood6_uncertainty = bigwood6_mu_vector[1] / 2 #std_dev / 2

    bigwood7_acceleration_x = bigwood7_data_columns["a_x-green"]
    bigwood7_acceleration_y = bigwood7_data_columns["a_y-green"]
    bigwood7_mu_vector = calculate_mu(bigwood7_acceleration_x,bigwood7_acceleration_y, theta)
    bigwood7_mu = bigwood7_mu_vector[0]
    bigwood7_uncertainty = bigwood7_mu_vector[1] / 2 #std_dev / 2

    bigwood8_acceleration_x = bigwood8_data_columns["a_x-green"]
    bigwood8_acceleration_y = bigwood8_data_columns["a_y-green"]
    bigwood8_mu_vector = calculate_mu(bigwood8_acceleration_x,bigwood8_acceleration_y, theta)
    bigwood8_mu = bigwood8_mu_vector[0]
    bigwood8_uncertainty = bigwood8_mu_vector[1] / 2 #std_dev / 2

    bigwood9_acceleration_x = bigwood9_data_columns["a_x-green"]
    bigwood9_acceleration_y = bigwood9_data_columns["a_y-green"]
    bigwood9_mu_vector = calculate_mu(bigwood9_acceleration_x,bigwood9_acceleration_y, theta)
    bigwood9_mu = bigwood9_mu_vector[0]
    bigwood9_uncertainty = bigwood9_mu_vector[1] / 2 #std_dev / 2

    print("bigwood1 mu is", bigwood1_mu)
    print("bigwood2 mu is", bigwood2_mu)
    print("bigwood3 mu is", bigwood3_mu)
    print("bigwood4 mu is", bigwood4_mu)
    print("bigwood5 mu is", bigwood5_mu)
    print("bigwood6 mu is", bigwood6_mu)
    print("bigwood7 mu is", bigwood7_mu)
    print("bigwood8 mu is", bigwood8_mu)
    print("bigwood9 mu is", bigwood9_mu)

    bigwood_avg = (bigwood1_mu 
    + bigwood2_mu 
    + bigwood3_mu
    + bigwood4_mu
    + bigwood5_mu
    + bigwood6_mu
    + bigwood7_mu
    + bigwood8_mu
    + bigwood9_mu
    ) / 9

    bigwood_std_dev = (bigwood_avg - bigwood1_mu) ** 2 
    + (bigwood_avg - bigwood2_mu) ** 2 
    + (bigwood_avg - bigwood3_mu) ** 2
    + (bigwood_avg - bigwood4_mu) ** 2
    + (bigwood_avg - bigwood5_mu) ** 2
    + (bigwood_avg - bigwood6_mu) ** 2
    + (bigwood_avg - bigwood7_mu) ** 2
    + (bigwood_avg - bigwood8_mu) ** 2
    + (bigwood_avg - bigwood9_mu) ** 2
        
    bigwood_std_dev /= 9
    bigwood_std_dev = math.sqrt(bigwood_std_dev)
    bigwood_uncertainty = (1.96 * bigwood_std_dev) / math.sqrt(9)


    print("bigwood mu avg is: ", bigwood_avg)
    print("bigwood mu std dev is: ", bigwood_std_dev)
    print("bigwood mu uncertainty is: ", bigwood_uncertainty)


    
    bigrubber1_acceleration_x = bigrubber1_data_columns["a_x-green"]
    bigrubber1_acceleration_y = bigrubber1_data_columns["a_y-green"]
    bigrubber1_mu_vector = calculate_mu(bigrubber1_acceleration_x,bigrubber1_acceleration_y, theta)
    bigrubber1_mu = bigrubber1_mu_vector[0]
    bigrubber1_uncertainty = bigrubber1_mu_vector[1] / 2 #std_dev / 2

    bigrubber2_acceleration_x = bigrubber2_data_columns["a_x-green"]
    bigrubber2_acceleration_y = bigrubber2_data_columns["a_y-green"]
    bigrubber2_mu_vector = calculate_mu(bigrubber2_acceleration_x,bigrubber2_acceleration_y, theta)
    bigrubber2_mu = bigrubber2_mu_vector[0]
    bigrubber2_uncertainty = bigrubber2_mu_vector[1] / 2 #std_dev / 2
    
    bigrubber3_acceleration_x = bigrubber3_data_columns["a_x-green"]
    bigrubber3_acceleration_y = bigrubber3_data_columns["a_y-green"]
    bigrubber3_mu_vector = calculate_mu(bigrubber3_acceleration_x,bigrubber3_acceleration_y, theta)
    bigrubber3_mu = bigrubber3_mu_vector[0]
    bigrubber3_uncertainty = bigrubber3_mu_vector[1] / 2 #std_dev / 2

    bigrubber4_acceleration_x = bigrubber4_data_columns["a_x-green"]
    bigrubber4_acceleration_y = bigrubber4_data_columns["a_y-green"]
    bigrubber4_mu_vector = calculate_mu(bigrubber4_acceleration_x,bigrubber4_acceleration_y, theta)
    bigrubber4_mu = bigrubber4_mu_vector[0]
    bigrubber4_uncertainty = bigrubber4_mu_vector[1] / 2 #std_dev / 2

    bigrubber5_acceleration_x = bigrubber5_data_columns["a_x-green"]
    bigrubber5_acceleration_y = bigrubber5_data_columns["a_y-green"]
    bigrubber5_mu_vector = calculate_mu(bigrubber5_acceleration_x,bigrubber5_acceleration_y, theta)
    bigrubber5_mu = bigrubber5_mu_vector[0]
    bigrubber5_uncertainty = bigrubber5_mu_vector[1] / 2 #std_dev / 2

    bigrubber6_acceleration_x = bigrubber6_data_columns["a_x-green"]
    bigrubber6_acceleration_y = bigrubber6_data_columns["a_y-green"]
    bigrubber6_mu_vector = calculate_mu(bigrubber6_acceleration_x,bigrubber6_acceleration_y, theta)
    bigrubber6_mu = bigrubber6_mu_vector[0]
    bigrubber6_uncertainty = bigrubber6_mu_vector[1] / 2 #std_dev / 2

    bigrubber7_acceleration_x = bigrubber7_data_columns["a_x-green"]
    bigrubber7_acceleration_y = bigrubber7_data_columns["a_y-green"]
    bigrubber7_mu_vector = calculate_mu(bigrubber7_acceleration_x,bigrubber7_acceleration_y, theta)
    bigrubber7_mu = bigrubber7_mu_vector[0]
    bigrubber7_uncertainty = bigrubber7_mu_vector[1] / 2 #std_dev / 2

    bigrubber8_acceleration_x = bigrubber8_data_columns["a_x-green"]
    bigrubber8_acceleration_y = bigrubber8_data_columns["a_y-green"]
    bigrubber8_mu_vector = calculate_mu(bigrubber8_acceleration_x,bigrubber8_acceleration_y, theta)
    bigrubber8_mu = bigrubber8_mu_vector[0]
    bigrubber8_uncertainty = bigrubber8_mu_vector[1] / 2 #std_dev / 2

    bigrubber9_acceleration_x = bigrubber9_data_columns["a_x-green"]
    bigrubber9_acceleration_y = bigrubber9_data_columns["a_y-green"]
    bigrubber9_mu_vector = calculate_mu(bigrubber9_acceleration_x,bigrubber9_acceleration_y, theta)
    bigrubber9_mu = bigrubber9_mu_vector[0]
    bigrubber9_uncertainty = bigrubber9_mu_vector[1] / 2 #std_dev / 2

    print("bigrubber1 mu is", bigrubber1_mu)
    print("bigrubber2 mu is", bigrubber2_mu)
    print("bigrubber3 mu is", bigrubber3_mu)
    print("bigrubber4 mu is", bigrubber4_mu)
    print("bigrubber5 mu is", bigrubber5_mu)
    print("bigrubber6 mu is", bigrubber6_mu)
    print("bigrubber7 mu is", bigrubber7_mu)
    print("bigrubber8 mu is", bigrubber8_mu)
    print("bigrubber9 mu is", bigrubber9_mu)

    bigrubber_avg = (bigrubber1_mu 
    + bigrubber2_mu 
    + bigrubber3_mu
    + bigrubber4_mu
    + bigrubber5_mu
    + bigrubber6_mu
    + bigrubber7_mu
    + bigrubber8_mu
    + bigrubber9_mu
    ) / 9

    bigrubber_std_dev = (bigrubber_avg - bigrubber1_mu) ** 2 
    + (bigrubber_avg - bigrubber2_mu) ** 2 
    + (bigrubber_avg - bigrubber3_mu) ** 2
    + (bigrubber_avg - bigrubber4_mu) ** 2
    + (bigrubber_avg - bigrubber5_mu) ** 2
    + (bigrubber_avg - bigrubber6_mu) ** 2
    + (bigrubber_avg - bigrubber7_mu) ** 2
    + (bigrubber_avg - bigrubber8_mu) ** 2
    + (bigrubber_avg - bigrubber9_mu) ** 2
        
    bigrubber_std_dev /= 9
    bigrubber_std_dev = math.sqrt(bigrubber_std_dev)
    bigrubber_uncertainty = (1.96 * bigrubber_std_dev) / math.sqrt(9)

    print("bigrubber mu avg is: ", bigrubber_avg)
    print("bigrubber mu std dev is: ", bigrubber_std_dev)
    print("bigrubber mu uncertainty is: ", bigrubber_uncertainty)
    


    #theta = arc cos (x / sqrt( x^2 + y^2))

    # if data_columns:
    #     # Print the first 5 entries of each column
    #     for column_name, column_data in data_columns.items():
    #         preview = column_data[:5]
    #         print(f"Column '{column_name}': {preview}...")