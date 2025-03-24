#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>

using std::string, std::cout;

class FileWriter{
    public:
        FileWriter(string init_file): file(init_file), gen(rd()), dist(1, 1000) {  
        }
        void WriteIntegers(int n){
            outputFileStream.open(file);
            if(!outputFileStream){
                std::cerr << "Error: could not open file " << this->file << '\n';
            }
            for(int i = 0;i < n;i++){
                outputFileStream << dist(gen) << '\n';
            }
            cout << n << " integers saved to " << this->file << '\n';
            outputFileStream.close();
        }
        ~FileWriter(){
            if(outputFileStream.is_open()){
                outputFileStream.close();
            }
        }

    private:
        string file;
        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> dist;
        std::ofstream outputFileStream;
};

class FileReader{
    public: 
        FileReader(string init_file): file(init_file) { }
        void ReadFileToConsole(){
            inputFileStream.open(file);
            if(!(this->inputFileStream)){
                std::cerr << "Error: could not open file " << this->file << '\n';
            }
            string line;
            while(std::getline(this->inputFileStream, line)){
                std::cout << line << '\n';
            }

            if (inputFileStream.eof()) {
                std::cout << "Reached the end of the file.\n";
            } else if (inputFileStream.fail()) {
                std::cerr << "Error: Failed to read the file completely.\n";
            }
            inputFileStream.close();
        }
        ~FileReader(){
            if(inputFileStream.is_open()){
                inputFileStream.close();
            }
        }
    private:
        string file;
        std::ifstream inputFileStream;
};
int main(){
    string path = "ints.txt";
    FileWriter fw(path);
    fw.WriteIntegers(500);
    FileReader fr(path);
    fr.ReadFileToConsole();
}