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

if __name__ == "__main__":
    smallwood1_file_path = "./Small Wood/static_smallwood_1_clipped.csv"  
    smallwood2_file_path = "./Small Wood/static_smallwood_2_clipped.csv"
    smallwood3_file_path = "./Small Wood/static_smallwood_3_clipped.csv"
    
    smallwood1_data_columns = read_csv_columns(smallwood1_file_path)
    smallwood2_data_columns = read_csv_columns(smallwood2_file_path)
    smallwood3_data_columns = read_csv_columns(smallwood3_file_path)

    bigwood1_file_path = "./Big Wood/static_bigwood_1_clipped.csv"
    bigwood2_file_path = "./Big Wood/static_bigwood_2_clipped.csv"
    bigwood3_file_path = "./Big Wood/static_bigwood_3_clipped.csv"

    bigwood1_data_columns = read_csv_columns(bigwood1_file_path)
    bigwood2_data_columns = read_csv_columns(bigwood2_file_path)
    bigwood3_data_columns = read_csv_columns(bigwood3_file_path)

    bigrubber1_file_path = "./Big Rubber/static_bigrubber_1_clipped.csv"
    bigrubber2_file_path = "./Big Rubber/static_bigrubber_2_clipped.csv"
    bigrubber3_file_path = "./Big Rubber/static_bigrubber_3_clipped.csv"

    bigrubber1_data_columns = read_csv_columns(bigrubber1_file_path)
    bigrubber2_data_columns = read_csv_columns(bigrubber2_file_path)
    bigrubber3_data_columns = read_csv_columns(bigrubber3_file_path)
    
    smallwood1_y = float(smallwood1_data_columns["r_y-darkorange"][0]) - float(smallwood1_data_columns["r_y-yellowneon"][0])
    smallwood1_x = float(smallwood1_data_columns["r_x-darkorange"][0]) - float(smallwood1_data_columns["r_x-hotpink"][0])
    smallwood1_theta = math.acos(smallwood1_x / math.sqrt(smallwood1_x ** 2 + smallwood1_y ** 2)) 
    smallwood1_mu = math.sin(smallwood1_theta) / math.cos(smallwood1_theta)

    smallwood2_y = float(smallwood2_data_columns["r_y-darkorange"][0]) - float(smallwood2_data_columns["r_y-yellowneon"][0])
    smallwood2_x = float(smallwood2_data_columns["r_x-darkorange"][0]) - float(smallwood2_data_columns["r_x-hotpink"][0])
    smallwood2_theta = math.acos(smallwood2_x / math.sqrt(smallwood2_x ** 2 + smallwood2_y ** 2)) 
    smallwood2_mu = math.sin(smallwood2_theta) / math.cos(smallwood2_theta)
    
    smallwood3_y = float(smallwood3_data_columns["r_y-darkorange"][0]) - float(smallwood3_data_columns["r_y-yellowneon"][0])
    smallwood3_x = float(smallwood3_data_columns["r_x-darkorange"][0]) - float(smallwood3_data_columns["r_x-hotpink"][0])
    smallwood3_theta = math.acos(smallwood3_x / math.sqrt(smallwood3_x ** 2 + smallwood3_y ** 2)) 
    smallwood3_mu = math.sin(smallwood3_theta) / math.cos(smallwood3_theta)
    
    smallwood_avg = (smallwood1_mu + smallwood2_mu + smallwood3_mu) /3
    smallwood_std_dev = (smallwood_avg - smallwood1_mu) ** 2 + (smallwood_avg - smallwood2_mu) ** 2 + (smallwood_avg - smallwood3_mu) ** 2
    smallwood_std_dev /= 3
    smallwood_std_dev = math.sqrt(smallwood_std_dev)


    bigwood1_y = float(bigwood1_data_columns["r_y-darkorange"][0]) - float(bigwood1_data_columns["r_y-yellowneon"][0])
    bigwood1_x = float(bigwood1_data_columns["r_x-darkorange"][0]) - float(bigwood1_data_columns["r_x-hotpink"][0])
    bigwood1_theta = math.acos(bigwood1_x / math.sqrt(bigwood1_x ** 2 + bigwood1_y ** 2)) 
    bigwood1_mu = math.sin(bigwood1_theta) / math.cos(bigwood1_theta)

    bigwood2_y = float(bigwood2_data_columns["r_y-darkorange"][0]) - float(bigwood2_data_columns["r_y-yellowneon"][0])
    bigwood2_x = float(bigwood2_data_columns["r_x-darkorange"][0]) - float(bigwood2_data_columns["r_x-hotpink"][0])
    bigwood2_theta = math.acos(bigwood2_x / math.sqrt(bigwood2_x ** 2 + bigwood2_y ** 2)) 
    bigwood2_mu = math.sin(bigwood2_theta) / math.cos(bigwood2_theta)
    
    bigwood3_y = float(bigwood3_data_columns["r_y-darkorange"][0]) - float(bigwood3_data_columns["r_y-yellowneon"][0])
    bigwood3_x = float(bigwood3_data_columns["r_x-darkorange"][0]) - float(bigwood3_data_columns["r_x-hotpink"][0])
    bigwood3_theta = math.acos(bigwood3_x / math.sqrt(bigwood3_x ** 2 + bigwood3_y ** 2)) 
    bigwood3_mu = math.sin(bigwood3_theta) / math.cos(bigwood3_theta)

    bigwood_avg = (bigwood1_mu + bigwood2_mu + bigwood3_mu) /3
    bigwood_std_dev = (bigwood_avg - bigwood1_mu) ** 2 + (bigwood_avg - bigwood2_mu) ** 2 + (bigwood_avg - bigwood3_mu) ** 2
    bigwood_std_dev /= 3
    bigwood_std_dev = math.sqrt(bigwood_std_dev)


    bigrubber1_y = float(bigrubber1_data_columns["r_y-darkorange"][0]) - float(bigrubber1_data_columns["r_y-yellowneon"][0])
    bigrubber1_x = float(bigrubber1_data_columns["r_x-darkorange"][0]) - float(bigrubber1_data_columns["r_x-hotpink"][0])
    bigrubber1_theta = math.acos(bigrubber1_x / math.sqrt(bigrubber1_x ** 2 + bigrubber1_y ** 2)) 
    bigrubber1_mu = math.sin(bigrubber1_theta) / math.cos(bigrubber1_theta)

    bigrubber2_y = float(bigrubber2_data_columns["r_y-darkorange"][0]) - float(bigrubber2_data_columns["r_y-yellowneon"][0])
    bigrubber2_x = float(bigrubber2_data_columns["r_x-darkorange"][0]) - float(bigrubber2_data_columns["r_x-hotpink"][0])
    bigrubber2_theta = math.acos(bigrubber2_x / math.sqrt(bigrubber2_x ** 2 + bigrubber2_y ** 2)) 
    bigrubber2_mu = math.sin(bigrubber2_theta) / math.cos(bigrubber2_theta)

    bigrubber3_y = float(bigrubber3_data_columns["r_y-darkorange"][0]) - float(bigrubber3_data_columns["r_y-yellowneon"][0])
    bigrubber3_x = float(bigrubber3_data_columns["r_x-darkorange"][0]) - float(bigrubber3_data_columns["r_x-hotpink"][0])
    bigrubber3_theta = math.acos(bigrubber3_x / math.sqrt(bigrubber3_x ** 2 + bigrubber3_y ** 2)) 
    bigrubber3_mu = math.sin(bigrubber3_theta) / math.cos(bigrubber3_theta)

    bigrubber_avg = (bigrubber1_mu + bigrubber2_mu + bigrubber3_mu) /3
    bigrubber_std_dev = (bigrubber_avg - bigrubber1_mu) ** 2 + (bigrubber_avg - bigrubber2_mu) ** 2 + (bigrubber_avg - bigrubber3_mu) ** 2
    bigrubber_std_dev /= 3
    bigrubber_std_dev = math.sqrt(bigrubber_std_dev)

    print("smallwood1 mu IS:", smallwood1_mu)
    print("smallwood2 mu IS:", smallwood2_mu)
    print("smallwood3 mu IS:", smallwood3_mu)
    print("smallwood mu avg is: ", smallwood_avg)
    print("smallwood mu std dev is: ", smallwood_std_dev)
    print("smallwood mu uncertainty is: ", smallwood_std_dev / 2)

    print("bigwood1 mu IS:", bigwood1_mu)
    print("bigwood2 mu IS:", bigwood2_mu)
    print("bigwood3 mu IS:", bigwood3_mu)
    print("bigwood mu avg is: ", bigwood_avg)
    print("bigwood mu std dev is: ", bigwood_std_dev)
    print("bigwood mu uncertainty is: ", bigwood_std_dev / 2)
    
    print("bigrubber1 mu IS:", bigrubber1_mu)
    print("bigrubber2 mu IS:", bigrubber2_mu)
    print("bigrubber3 mu IS:", bigrubber3_mu)
    print("bigrubber mu avg is: ", bigrubber_avg)
    print("bigrubber mu std dev is: ", bigrubber_std_dev)
    print("bigrubber mu uncertainty is: ", bigrubber_std_dev / 2)

    #theta = arc cos (x / sqrt( x^2 + y^2))

    # if data_columns:
    #     # Print the first 5 entries of each column
    #     for column_name, column_data in data_columns.items():
    #         preview = column_data[:5]
    #         print(f"Column '{column_name}': {preview}...")