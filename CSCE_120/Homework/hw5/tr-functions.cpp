#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include "tr-functions.h"
#include <cmath>

using std::vector, std::string;
using std::cout, std::cin;
using std::stringstream;
using std::ifstream;

// Part 1 Functions

void getUserInput(std::string& filename, unsigned int& rows, unsigned int& cols) {
    filename = "";
    rows = 0;
    cols = 0;
    // update to guarantee filename is not an empty string and rows and cols are values from 1 to 4000
    while(!(filename.length() > 0)){
        cout << "Enter filename: ";
        cin >> filename;
    }
    while(!(rows >= 1 && rows <= 4000)){
        cout << "Enter number of rows (1 - 4000): ";
        cin >> rows;
        if(cin.fail()){
            std::cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    while(!(cols >= 1 && cols <= 4000)){
        cout << "Enter number of columns (1 - 4000): ";
        cin >> cols;
        if(cin.fail()){
            std::cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

vector<vector<unsigned int>> loadElevations(string filename, unsigned int rows, unsigned int cols) {
    vector<vector<unsigned int>> elevationMap;
    //try{
        ifstream inputFileStream(filename);
        std::ofstream outputFileStream("test.txt");

        if(!inputFileStream.is_open()){
            throw std::invalid_argument("loadElevations: Failed to open " + filename);
            //throw std::invalid_argument();
        }
        stringstream sstream;
        sstream << inputFileStream.rdbuf();
        for(unsigned int i = 0;i<rows;i++){
            //string str;
            vector<unsigned int> vec(cols, 0);
            elevationMap.push_back(std::move(vec));
            // if(inputFileStream.eof()){
            //     throw std::runtime_error("loadElevations: Not enough values"); //before getline b/c if after getline, last iteration would throw in happy paths
            // }
            //getline(inputFileStream, str);
            //stringstream sstream(str);
            for(unsigned int j = 0;j<cols;j++){
                unsigned int x;
                sstream >> x;
                elevationMap.at(i).at(j) = x;
                if(sstream.fail()){
                    if(sstream.eof()){
                        throw std::runtime_error("loadElevations: Not enough values");
                    }
                    throw std::runtime_error("loadElevations: Invalid elevation value");
                }
                //outputFileStream << elevationMap.at(i).at(j) << " ";
            }
            //outputFileStream << '\n';
        }
        char c;
        while(sstream.get(c)){
            if(!std::isspace(static_cast<unsigned char>(c))){
                throw std::runtime_error("loadElevations: Too many values");
            }
        }
        if(!sstream.eof()){
            //std::cout << sstream.str() << '\n';
            throw std::runtime_error("loadElevations: Too many values");
        }
    // } catch( std::exception& e){
    //     std::cout << e.what() << '\n';
    // }
    return elevationMap;
}

void findMinMax(const vector<vector<unsigned int>>& elevations, unsigned int& min, unsigned int& max) {
    min = std::numeric_limits<unsigned int>::max();
    max = std::numeric_limits<unsigned int>::min();
    if(elevations.size() == 0){
        throw std::invalid_argument("findMinMax: Invalid elevations vector");
    }
    for(std::size_t i = 0;i<elevations.size();i++){
        if(elevations.at(i).size() == 0){
            throw std::invalid_argument("findMinMax: Invalid elevations vector");
        }
    }
    for(std::size_t i = 0;i<elevations.size(); i++){
        for(std::size_t j = 0;j< elevations.at(i).size(); j++){
            min = std::min(min, elevations.at(i).at(j));
            max = std::max(max, elevations.at(i).at(j));
        }
    }
}

unsigned short scaleValue(unsigned int value, unsigned int min, unsigned int max) {
    if(min >= max){
        throw std::out_of_range("scaleValue: min must be less than max");
    }
    if(value < min || value > max){
        throw std::out_of_range("scaleValue: value must be in the range min <= value <= max");
    }
    double numerator = 255 * (value - min);
    double denominator = (max - min);
    return static_cast<unsigned short>(std::round(numerator / denominator));
}

vector<vector<Pixel>> createImage(const vector<vector<unsigned int>>& elevations) {
    unsigned int min;
    unsigned int max;
    vector<vector<Pixel>> ans;
    if(elevations.size() == 0){
        throw std::invalid_argument("createImage: Invalid elevations vector");
    }
    for(std::size_t i = 0;i<elevations.size();i++){
        if(elevations.at(i).size() == 0){
            throw std::invalid_argument("createImage: Invalid elevations vector");
        }
    }
    findMinMax(elevations, min, max);
    for(std::size_t i = 0;i<elevations.size();i++){
        vector<Pixel> row;
        for(std::size_t j = 0;j<elevations.at(i).size(); j++){
            unsigned short brightness = scaleValue(elevations.at(i).at(j), min, max);
            Pixel pixel{brightness, brightness, brightness};
            row.push_back(pixel);
        }
        ans.push_back(std::move(row));
    }
    //b/c graphics community is restarted, we must make a transpose

    size_t rows = elevations.size();
    size_t cols = elevations[0].size();
    vector<vector<Pixel>> transpose(cols, vector<Pixel>(rows));
    for(size_t i = 0; i< rows;i++){
        for(size_t j = 0;j<cols; j++){
            transpose[j][i] = ans[i][j];
        }
    }
    return transpose;
}

void saveImage(string filename, const vector<vector<Pixel>>& image) { 
    std::ofstream ofs;
    ofs.open(filename + ".ppm");

    if(!ofs.is_open()){
        throw std::invalid_argument("saveImage: Failed to open" + filename);
    }
    
    if(image.size() == 0){
        throw std::invalid_argument("saveImage: Invalid image vector");
    }
    for(std::size_t i = 0;i<image.size();i++){
        if(image.at(i).size() == 0){
            throw std::invalid_argument("saveImage: Invalid image vector");
        }
    }

    ofs << "P3\n";
    int rows = image.size();
    int cols = image[0].size();
    ofs << cols << " " << rows << '\n';
    ofs << "255" << '\n';
    for(size_t i = 0;i<image[0].size();i++){
        for(size_t j = 0;j<image.size();j++){
            ofs << image.at(j).at(i).r << " ";
            ofs << image.at(j).at(i).g << " ";
            ofs << image.at(j).at(i).b << " ";
        }
        ofs << " ";
    }
    ofs.close();
}

//uncomment the following for part 2

void processRoutes(vector<vector<Pixel>>& image, const vector<vector<unsigned int>>& elevations, Pixel colorAll, Pixel colorMin) {
    if(image.size() == 0){
        throw std::invalid_argument("processRoutes: Invalid image vector");
    }
    for(std::size_t i = 0;i<image.size();i++){
        if(image.at(i).size() == 0){
            throw std::invalid_argument("processRoutes: Invalid image vector");
        }
    }

    if(elevations.size() == 0){
        throw std::invalid_argument("processRoutes: Invalid elevations vector");
    }
    for(std::size_t i = 0;i<elevations.size();i++){
        if(elevations.at(i).size() == 0){
            throw std::invalid_argument("processRoutes: Invalid elevations vector");
        }
    }

    if(colorAll.r > 255 //|| color.r < 0
        || colorAll.g > 255 //|| color.g < 0 
        || colorAll.b > 255 //|| color.b < 0
    ){
        throw std::invalid_argument("processRoutes: Invalid Pixel");
    }
    if(colorMin.r > 255 //|| color.r < 0
        || colorMin.g > 255 //|| color.g < 0 
        || colorMin.b > 255 //|| color.b < 0
    ){
        throw std::invalid_argument("processRoutes: Invalid Pixel");
    }


    int bestRow = -1;
    int bestRowElevationChange = std::numeric_limits<int>::max();
    int rows = image.at(0).size();
    for(int row = 0;row<rows;row++){
        int elevationChange = colorRoute(image, elevations, colorAll, row);
        if(bestRowElevationChange > elevationChange){
            bestRowElevationChange = elevationChange;
            bestRow = row;
        }
    }
    colorRoute(image, elevations, colorMin, bestRow);
}
unsigned int elevationChange(const vector<vector<unsigned int>>& elevations, int startRow, int endRow, int col){
    unsigned int elevationStart = elevations.at(startRow).at(col-1);
    unsigned int elevationEnd = elevations.at(endRow).at(col);
    return elevationStart > elevationEnd ? 
    elevationStart - elevationEnd :
    elevationEnd - elevationStart; 
}
int colorRoute(vector<vector<Pixel>>& image, const vector<vector<unsigned int>>& elevations, Pixel color, int startRow) {
    //greedy route
    if(image.size() == 0){
        throw std::invalid_argument("colorRoute: Invalid image vector");
    }
    for(std::size_t i = 0;i<image.size();i++){
        if(image.at(i).size() == 0){
            throw std::invalid_argument("colorRoute: Invalid image vector");
        }
    }

    if(elevations.size() == 0){
        throw std::invalid_argument("colorRoute: Invalid elevations vector");
    }
    for(std::size_t i = 0;i<elevations.size();i++){
        if(elevations.at(i).size() == 0){
            throw std::invalid_argument("colorRoute: Invalid elevations vector");
        }
    }

    if(color.r > 255 //|| color.r < 0
    || color.g > 255 //|| color.g < 0 
    || color.b > 255 //|| color.b < 0
    ){
        throw std::invalid_argument("colorRoute: Invalid Pixel");
    }

    unsigned int elevationChangeSum = 0;
    //int currentRow = startRow;
    image.at(0).at(startRow) = color;

    int rows = image.at(0).size();
    int cols = image.size();

    //note: image is currently 189X87, whereas elevations is 87X189. 
    //image is gonna be transposed in saveImage
    //image -> (col, row)
    //elevations -> (row, col)
    for(int col = 1;col<cols;col++){
        int row0 = startRow - 1;
        int row1 = startRow;
        int row2 = startRow + 1;
        unsigned int elevationChange1 = elevationChange(elevations, startRow, row1, col);
        unsigned int elevationChange0 = std::numeric_limits<unsigned int>::max();
        unsigned int elevationChange2 = std::numeric_limits<unsigned int>::max();
        if(row0 >= 0){
            elevationChange0 = elevationChange(elevations, startRow, row0, col);
        }
        if(row2 < rows){
            elevationChange2 = elevationChange(elevations, startRow, row2, col);
        }
        if(elevationChange2 <= elevationChange0 && elevationChange2 <= elevationChange1){
            startRow = row2;
            elevationChangeSum += elevationChange2;
        }else if(elevationChange1 < elevationChange2 && elevationChange1 <= elevationChange0){
            startRow = row1; // doesnt change, here symbolically
            elevationChangeSum += elevationChange1;
        }else if(elevationChange0 < elevationChange2 && elevationChange0 < elevationChange1){
            startRow = row0;
            elevationChangeSum += elevationChange0;
        }else{
            std::cout << "something has gone horribly wrong.\n";
        }
        image.at(col).at(startRow) = color;
    }
    return static_cast<int>(elevationChangeSum);














    // for(int col = 1;col<image.size();col++){
    //     int row0 = currentRow-1;
    //     int row1 = currentRow;
    //     int row2 = currentRow+1; 
    //     int elevationChange1 = elevationChange(elevations, currentRow, row1, col);
    //     if(row0 < 0){
    //         if(row2 >= image.at(col).size()){
    //             elevationChangeSum += elevationChange1;
    //         }else{
    //             int elevationChange2 = elevationChange(elevations, currentRow, row2, col);
    //             if(elevationChange1 >= elevationChange2){
    //                 currentRow = row2;
    //                 elevationChangeSum += elevationChange2;
    //             }else{
    //                 elevationChangeSum += elevationChange1;
    //             }
    //         }
    //     }else if(row2 >= image.at(col).size()){
    //         //check between row0 and row1
    //         int elevationChange0 = elevationChange(elevations, currentRow, row0, col);
    //         if(elevationChange1 > elevationChange0){
    //             currentRow = row0;
    //             elevationChangeSum += elevationChange0;
    //         }else{
    //             elevationChangeSum += elevationChange1;
    //         }
    //     }else{
    //         //0, 1, and 2 all valid
    //         int elevationChange0 = elevationChange(elevations, currentRow, row0, col);
    //         int elevationChange2 = elevationChange(elevations, currentRow, row2, col);
    //         if(elevationChange2 <= elevationChange1 && elevationChange2 <= elevationChange1){
    //             currentRow = row2;
    //             elevationChangeSum += elevationChange2;
    //         }else if(elevationChange1 <= elevationChange0 && elevationChange1 <= elevationChange2){
    //             currentRow = row1;
    //             elevationChangeSum += elevationChange1;
    //         }else{
    //             currentRow = row0;
    //             elevationChangeSum += elevationChange0;
    //         }
    //     }
        
    //     //now that we've found the right row, color the right pixel
    //     image.at(col).at(currentRow) = color;
    // }
    // return elevationChangeSum;
}

