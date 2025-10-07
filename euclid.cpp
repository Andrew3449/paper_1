//
// Created by macke on 10/4/2025.
//
#include "euclid.h"

int euclidean(unsigned int m, unsigned int n, int* num_divisions){
    if (n == 0){
        return (int)m;
    }
    if (m > n){
        *num_divisions = *num_divisions + 1;
        return euclidean(n, m%n, num_divisions);
    }else{
        *num_divisions = *num_divisions + 1;
        return euclidean(m, n%m, num_divisions);
    }
}

int nReduce(unsigned int m, unsigned int n, int* numDivisions){
    bool is_gcd = false;
    int gcd = (int)n;
    // n will always divide itself, so we just need to check if n divides m
    while ((gcd >= 1) && (!is_gcd)){
        if ((m%gcd == 0) && (n%gcd == 0)){
            is_gcd = true;
        }else{
            gcd--;
            *numDivisions = *numDivisions + 1;
        }
    }
    return (int)gcd;
}

int primeFactorization(unsigned int m, unsigned int n, int* d){
    // check if either gcd is 0, at which point we return either m or n
    // we return m+n in the case that either is 0
    if ((m == 0) || (n == 0)){
        return (int)(m+n);
    }
    unsigned int gcd = 1;
    int i = 0;
    int j = 0;

    vector<unsigned int> m_factors = primes(m, d);
    vector<unsigned int> n_factors = primes(n, d);
    // iterate until the number of factors has been exceeded
    while((i < m_factors.size()) && (j < n_factors.size())){
        if (m_factors[i] < n_factors[j]){ // increment i
            i++;
        }
        else if (m_factors[i] > n_factors[j]){ // increment j so we go up
            j++;
        }
        else{ // common factors found, multiply gcd by common factor and increment both
            gcd *= m_factors[i];
            i++;
            j++;
        }
    }
    return (int)gcd;
}

// fills out an int vector with prime factors of i
// trial division
vector<unsigned int> primes(unsigned int i, int* d){
    vector<unsigned int> prime_factors;
    while (i % 2 == 0) {
        prime_factors.push_back(2);
        i /= 2;
        *d = *d+1;
    }
    // if the number is not divisible by 2, we don't need to check
    // the iterator will automatically skip all even numbers because they aren't 2
    for (int s = 3; s*s <= i; s += 2) {
        while (i % s == 0){
            if (isPrime(s)){
                prime_factors.push_back(s);
                i /= s;
            }
            *d = *d+1;
        }
    }
    if (i > 1){
        prime_factors.push_back(i);
    }
    return prime_factors;
}

// checks if the number is prime by dividing it by numbers until sqrt(n)
// this is the trial division method
// runs in O(sqrt(n)) time
bool isPrime(int n){
    if (n <= 1){
        return false;
    }
    int dividend = 2;
    while (dividend < sqrt(n)){
        if (n % dividend == 0) return false;
        dividend++;
    }
    return true;
}