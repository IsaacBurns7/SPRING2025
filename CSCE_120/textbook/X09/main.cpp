#include <iostream>
#include <iomanip>
#include <array>
#include <iostream>
#include <unordered_map>

using std::cout, std::cin, std::string, std::vector;
// X.9 Structures, Unions, and Enumerations
// [1] (∗1) Define a struct with a member of each of the types bool, char, int, long, double, and long
// double. Order the members so as to get the largest size of the struct and the smallest size of
// the struct.

enum Season {
    spring,
    summer,
    autumn,
    winter
};

// [5] (∗2) Implement an enum called Season with enumerators spring, summer, autumn, and winter.
// Define operators ++ and −− for Season. Define input (>>) and output (<<) operations for Season, providing string values. Provide a way to control the mapping between Season values
// and their string representations. For example, I might want the strings to reflect the Danish
// names for the seasons. For further study, see Chapter 39.

const std::array<Season, 4> seasonSequence = {
    Season::spring, Season::summer, Season::autumn, Season::winter
};

int getSequencePosition(Season season){
    for(int i = 0;i<seasonSequence.size();i++){
        if(season == seasonSequence[i]){
            return i;
        }
    }
    return 0; //nothing found
}

//prefix - return modified object
Season& operator++(Season& season){
    int position = getSequencePosition(season);
    int nextPos = (position + 1) % seasonSequence.size();
    season = seasonSequence[nextPos];
    return season;
}

//postfix - return same object, but change original
Season operator++(Season& season, int ){
    Season original = season;
    ++season;
    return original;
}

//prefix - return modified
Season& operator--(Season& season){
    int position = getSequencePosition(season);
    int nextPos = (position - 1);
    if(nextPos < 0){
        nextPos += seasonSequence.size();
    }
    season = seasonSequence[nextPos];
    return season;
}

Season operator--(Season& season, int ){
    Season original = season;
    --season;
    return original;
}

// Define input (>>) and output (<<) operations for Season, providing string values. 
// Provide a way to control the mapping between Season values
// and their string representations. For example, I might want the strings to reflect the Danish Language.

std::unordered_map<Season, std::string> season_to_string {
    {Season::spring, "spring"},
    {Season::summer, "summer"},
    {Season::autumn, "autumn"},
    {Season::winter, "winter"}
};

std::unordered_map<std::string, Season> string_to_season;

void initStringToSeason(){
    for(const auto& pair: season_to_string){
        string_to_season[pair.second] = pair.first;
    }
}

std::string seasonToString(const Season& season){
    return season_to_string[season];
}

Season stringToSeason(const string& str){
    return string_to_season[str];
}


std::ostream& operator<<(std::ostream& os, const Season& season){
    os << seasonToString(season) << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, Season& season){
    string str;
    is >> str;
    season = stringToSeason(str);
    return is;
}



struct __attribute__((packed)) structural {
    char ch;
    bool b;
    int i;
    long l;
    double d;
    long double ld;
};

class Counter{
    public:
        Counter(){
            Counter::count = count + 1;
        }
        static void showCount() {
            std::cout << "Count: " << count << '\n';
        }
    private:
        static int count;
};
int Counter::count = 0;

struct Date{
    int year;
    int month;
    int day;
    Date(int y, int m, int d) : year(y), month(m), day(d){

    }
    Date(){
        year = 0;
        month = 0;
        day = 0;
    }
};
std::istream& operator>>(std::istream& is, Date& date){
    is >> date.year >> date.month >> date.day;
    return is;
}
std::ostream& operator<<(std::ostream& os, Date& date){
    os << date.year << "-"
        << std::setw(2) << std::setfill('0') << date.month << '-'
        << std::setw(2) << std::setfill('0') << date.day << '\n';
    return os;
}

int main(){
    // std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    // std::cout << "Size of bool: " << sizeof(bool) << " bytes\n";
    // std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    // std::cout << "Size of long: " << sizeof(long) << " bytes\n";
    // std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    // std::cout << "Size of long double: " << sizeof(long double) << " bytes\n";
    // std::cout << "Size of MyStruct: " << sizeof(structural) << " bytes\n";

        // [2] (∗1.5) Define a table of the names of months of the year and the number of days in each
    // month. Write out that table. Do this twice; once using an array of char for the names and an
    // array for the number of days and once using an array of structures, with each structure holding the name of a month and the number of days in it.
    const char months[12][10] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // Array of number of days in each month
    const int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    struct month {
        char month_name[10];
        int days;
        //OG
        // month(char mn[10], int d): days(d){
        //     int i = 0;
        //     while(month_name[i] != '\0' && mn[i] != '\0'){
        //         month_name[i] = mn[i];
        //         i++;
        //     }
        // }

        //better
        month(const char mn[10], int d): days(d){
            std::strncpy(month_name, mn, sizeof(month_name) - 1);
            month_name[sizeof(month_name) - 1] = '\0';
        }
        void display() const {
            std::cout << month_name << " has " << days << " days\n";
        }
    };

    // Define an array of months
    const month months2[12] = {
        {"January", 31}, {"February", 28}, {"March", 31}, {"April", 30},
        {"May", 31}, {"June", 30}, {"July", 31}, {"August", 31},
        {"September", 30}, {"October", 31}, {"November", 30}, {"December", 31}
    };
    // for (const auto& m : months2) {
    //     m.display();
    // }

    // [3] (∗1.5) Find an example where it would make sense to use a name in its own initializer.

    // Counter obj1, obj2, obj3;

    // Counter::showCount();

    //[4] (∗1.5) Define a struct Date to keep track of dates. Provide functions that read Dates from
// input, write Dates to output, and initialize a Date with a date.
    // Date today {};
    // cout << "Enter date(year month day)" << '\n';
    // cin >> today;
    // cout << "You entered " << today << '\n';

    // [5] (∗2) Implement an enum called Season with enumerators spring, summer, autumn, and winter.
// Define operators ++ and −− for Season. Define input (>>) and output (<<) operations for Season, providing string values. Provide a way to control the mapping between Season values
// and their string representations. For example, I might want the strings to reflect the Danish
// names for the seasons. For further study, see Chapter 39.
    initStringToSeason();
    Season season = Season::spring;
    season++;
    season++;
    cout << "Prefix addition " << season++ << '\n';
    cout << "Postfix addition: " << ++season << '\n';
    cout << "Prefix subtraction: " << season-- << '\n';
    cout << "Postfix subtraction: " << --season << '\n';

    Season season2;
    cout << "Enter desired season: spring, summer, autumn, or winter" << '\n';

    cin >> season2;

    cout << "You entered: " << season2 << '\n';
}
