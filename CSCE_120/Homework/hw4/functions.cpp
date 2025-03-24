#include "functions.h"

bool SumIsEven(int a, int b) {
  if((a+b)%2 != 0){
    return false;
  }else{
    return true;
  }
}
int Largest(int a, int b, int c) {
  if (a >= b && a >= c) {
    return a;
  } else if (b >= a && b >= c) {
    return b;
  } else {
    return c;
  }
}

unsigned int BoxesNeeded(int apples) {
  if(apples <= 0){
    return 0;
  }
  return ((apples+19)/20);
}

bool SmarterSection(int A_correct, int A_total, int B_correct, int B_total) {
  //true = A did better
  if(A_correct > A_total || B_correct > B_total || A_correct < 0 || B_correct < 0 || A_total < 0 || B_total < 0){
    throw std::invalid_argument("");
  }
  return static_cast<float>(A_correct) / static_cast<float>(A_total) > static_cast<float>(B_correct) / static_cast<float>(B_total) ;
}


bool GoodDinner(int pizzas, bool is_weekend) {
  if (pizzas >= 10 && (pizzas <= 20 || is_weekend)) {
    return true;
  }
  return false;
}

long long SumBetween(long long low, long long high) {
  if(low > high){
    throw std::invalid_argument("");
  }

  long long n = high-low+1; //n can also overflow :(
  
  //special case where n = 1 -> low = high
  if(n == 1){
    return low; //or high
  }


  if (low > 0 && high > LLONG_MAX - low) {// (low + high) might overflow
    long long c1 = LLONG_MAX-low;
    throw std::overflow_error("");
  }
  if (low < 0 && high < LLONG_MIN - low) {// (low + high) might underflow
    long long c2 = LLONG_MIN-low;
    throw std::overflow_error("");
  }

  long long sum_two_terms = low + high; //now safe
  long long sum = (n/2) * sum_two_terms;
  if(n % 2 == 0){
    long long a = n/2;
    long long b = sum_two_terms;
    if (a > 0 && b > 0 && a > LLONG_MAX / b) {
      throw std::overflow_error("");
    }
    if (a < 0 && b < 0 && a < LLONG_MAX / b) { //llong_max used b/c two negatives make a positive
      throw std::overflow_error("");
    }
    if (a > 0 && b < 0 && b < LLONG_MIN / a) {
      throw std::overflow_error("");
    }
    if (a < 0 && b > 0 && a < LLONG_MIN / b) {
      throw std::overflow_error("");
    }
  }else{
    //now equation is (n/2) > (LLONG_MAX - b/2) / b
    //
    long long a = n/2;
    long long b = sum_two_terms;
    if(b > 0 && a > (LLONG_MAX - (b/2)) / b) {
      throw std::overflow_error("");
    }
    if(b < 0 && b < (LLONG_MIN - (b/2)) / a) {
      throw std::overflow_error("");
    }
    sum += sum_two_terms / 2;
  }
  return sum;
}

long long Product(long long a, long long b) {
  if ((a == LLONG_MIN && b == -1) || (b == LLONG_MIN && a == -1)) {
    throw std::overflow_error("");
  }

  if (a > 0 && b > 0 && a > LLONG_MAX / b) {
    throw std::overflow_error("");
  }
  if (a < 0 && b < 0 && a < LLONG_MAX / b) { //llong_max used b/c two negatives make a positive
    throw std::overflow_error("");
  }
  if (a > 0 && b < 0 && b < LLONG_MIN / a) {
    throw std::overflow_error("");
  }
  if (a < 0 && b > 0 && a < LLONG_MIN / b) {
    throw std::overflow_error("");
  }

  return a * b;
}