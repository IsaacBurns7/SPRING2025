#include <string>
#include <iostream>
#include <vector>
class Student{
    public:
        Student(std::string s)
        : name(s){
        }
        int grade_at(unsigned int i){
            return grade_list.at(i);
        }
        std::vector<int> operator+=(unsigned int g){
            grade_list.push_back(g);
            return grade_list;
        }
        friend void operator<<(std::ostream& os, const Student& student){
            double grade_average{0};
            os << student.name << '\n'; 
            int n = student.grade_list.size();
            for(int i = 0;i<n;i++){
                os << student.grade_list[i] << " ";
                grade_average += student.grade_list[i];
            }
            os << '\n';
            os << "AVERAGE: " << grade_average / n << '\n';
        }
        ~Student(){
            name = "";
            grade_list.clear();
        }
    private:
        std::string name;
        std::vector<int> grade_list;
};

int main(){
    Student jeff{"jeffery dahmer"};
    jeff += 15;
    std::cout << jeff;
}