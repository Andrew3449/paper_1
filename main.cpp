#include <iostream>
#include "euclid.h"
#include <chrono>
#include <random>

#define M_START 100000
#define N_START 60000

using u32    = uint_least32_t;
using engine = std::mt19937;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::microseconds;

enum GCDMETHOD {
    EUCLID,
    NREDUCE,
    PRIME
};

unsigned int rng(int, int);
void rngTest(GCDMETHOD, int, int, int, int);
void print_results(unsigned int, unsigned int, unsigned int, std::chrono::duration<double, std::micro>, int*);

int main() {
    unsigned int m = M_START;
    unsigned int n = N_START;

    int m_min = (int)m;
    int m_max = (int)(m+n);

    int n_min = (int)n;
    int n_max = (int)(n+(m-n));
    int* d = nullptr;
    int num_divisions = 0;
    d = &num_divisions;
    // tests: for number of divisions and time taken
    std::cout << "----------EUCLID---------\n";
    // first set of m: 100, 124, 116, 126, 139, 101
    // first set of n: 60, 80, 90, 83, 96, 73
    auto t1 = high_resolution_clock::now();
    int x = euclidean(m, n, d);
    auto t2 = high_resolution_clock::now();

    duration<double, std::micro> euclid_time = t2 - t1;

    print_results(m,n,x,euclid_time, d);
    // random numbers, euclid
    for (int i = 1; i <= 5; i++){
        rngTest(EUCLID, m_min, m_max, n_min, n_max);
    }
    d = nullptr; // set d to null each time to reset it
    std::cout << "\n----------N REDUCE BY 1---------\n";
    // first set of m: 100, 135, 106, 148, 109, 155
    // first set of n: 60, 70, 69, 88, 70, 72
    d = &num_divisions;
    auto t3 = high_resolution_clock::now();
    x = nReduce(m, n, d);
    auto t4 = high_resolution_clock::now();

    duration<double, std::micro> n_reduce_time = t2 - t1;

    print_results(m,n,x,n_reduce_time, d);
    // random numbers, n-reduction
    for (int i = 1; i <= 5; i++){
        rngTest(NREDUCE, m_min, m_max, n_min, n_max);
    }
    d = nullptr;
    std::cout << "\n----------PRIME FACTORIZATION---------\n";
    // first set of m: 100, 129, 127, 114, 123, 113
    // first set of n: 60, 93, 76, 94, 100, 91
    d = &num_divisions;
    auto t5 = high_resolution_clock::now();
    x = primeFactorization(m, n, d);
    auto t6 = high_resolution_clock::now();

    duration<double, std::micro> prime_time = t6-t5;

    print_results(m,n,x,prime_time, d);
    // random numbers, n-reduction
    for (int i = 1; i <= 5; i++){
        rngTest(PRIME, m_min, m_max, n_min, n_max);
    }
    return 0;
}

unsigned int rng(int a, int b){
    unsigned int x;
    std::random_device rng_seed;
    const u32 seed = rng_seed();

    engine rng(seed);
    std::uniform_int_distribution<u32> distribute(a, b);
    x = distribute(rng);
    return x;
}
void rngTest(GCDMETHOD algorithm, int m_min, int m_max, int n_min, int n_max){

    // time variables keep track of the time the algorithm took to complete
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t1;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t2;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t3;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t4;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t5;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double, std::micro>> t6;
    duration<double, std::micro> timeRand{};
    unsigned int m = rng(m_min, m_max);
    unsigned int n = rng(n_min, n_max);
    int* i; // number of divisions
    int num = 0;
    i = &num;
    int result;
    // chooses the algorithmic method
    switch (algorithm){
        case EUCLID:
            t1 = high_resolution_clock::now();
            result = euclidean(m, n, i);
            t2 = high_resolution_clock::now();
            timeRand = t2-t1;
            break;
        case NREDUCE:
            t3 = high_resolution_clock::now();
            result = nReduce(m, n, i);
            t4 = high_resolution_clock::now();
            timeRand = t4-t3;
            break;
        case PRIME:
            t5 = high_resolution_clock::now();
            result = primeFactorization(m, n, i);
            t6 = high_resolution_clock::now();
            timeRand = t6-t5;
            break;
    }
    print_results(m,n,result,timeRand, i);
}
void print_results(unsigned int m, unsigned int n, unsigned int y, std::chrono::duration<double, std::micro> time, int* d){
    std::cout << "GCD of " << m << " and " << n << " = " << y << std::endl;
    std::cout << "Time Taken: " << time.count() << " \xE6s\n";
    std::cout << "Number of Divisions: " << *d << std::endl;
}