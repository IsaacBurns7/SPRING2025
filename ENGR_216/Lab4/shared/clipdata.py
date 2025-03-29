import csv
import glob

csvFiles = glob.glob("*.csv")

for workingFile in csvFiles:
    with open(workingFile, newline='', encoding='utf-8') as rF:
        reader = csv.DictReader(rF)
        columnNames = reader.fieldnames

        outputList = []
        for row in reader:
            # Check for velocity, bc we are NOT calculating that by hand
            if ((row['v_x-green'] != '') and (row['v_x-hotpink'] != '')):
                outputList.append(row)
                print(row)
        print(outputList)
        
        with open(workingFile[:-4] + "_clipped.csv", mode='w', newline='', encoding='utf-8') as wF:
            writer = csv.DictWriter(wF, columnNames)
            writer.writeheader()
            writer.writerows(outputList)
