#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <condition_variable>
#include <queue>
#include <future>
#include <numeric>
using std::string, std::queue, std::condition_variable, std::mutex, std::unique_lock, std::cout,
std::thread, std::packaged_task, std::future, std::vector;

//2
// std::queue<std::string> mqueue;
// std::condition_variable mcond;
// std::mutex mmutex;
// bool ready = false;

// void consumer(){
//     while(true){
//         unique_lock<mutex> lck{mmutex};
//         mcond.wait(lck, [] {return ready;});

//         auto m = mqueue.front();
//         mqueue.pop();
//         lck.unlock();
//         cout << m << '\n';
//     }
// }

double accum(double* beg, double* end, double init){
    return std::accumulate(beg, end, init); // return sum from beginning to end w/ starting value init
}

double comp2(vector<double>& v){
    try{
        using Task_type = double(double*, double*, double); //type of task

        std::packaged_task<Task_type> pt0{accum}; //package the task, which is the accum function
        std::packaged_task<Task_type> pt1{accum};

        std::future<double> f0{pt0.get_future()}; //get hold of pt0's future
        std::future<double> f1{pt1.get_future()};

        double* first = &v[0];
        thread t1 {std::move(pt0), first, first+v.size()/2, 0}; //start thread for pt0
        thread t2 {std::move(pt1), first+v.size()/2, first+v.size(), 0}; //start thread for pt1

        return f0.get() + f1.get(); //wait for results and retrieve
    }catch(std::exception e){
        cout << e.what() << '\n';
    }
    return 0;
}


int main(){
    //1
    // auto t0 = std::chrono::high_resolution_clock::now();
    // std::this_thread::sleep_for(std::chrono::milliseconds{20});
    // auto t1 = std::chrono::high_resolution_clock::now();
    // //std::cout << duration_cast<std::chrono::nanoseconds>(t1-t0).count() << " nanoseconds passed\n";

    // //2
    // mqueue.push("string1");
    // mqueue.push("string2");
    // consumer();

    vector<double> v{1,2,3,4,5,6,7,8,9,10};
    double x = comp2(v);
}

