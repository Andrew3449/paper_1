//
// Created by macke on 10/4/2025.
//
#include <cmath>
#include <iostream>
#include <vector>

using std::vector;
using std::sqrt;

#ifndef PAPER1_EUCLID_H
#define PAPER1_EUCLID_H
int euclidean(unsigned int, unsigned int, int*);
int nReduce (unsigned int, unsigned int, int*);
int primeFactorization(unsigned int, unsigned int, int*);
// helpers for primeFactorization()
vector<unsigned int> primes(unsigned int, int*);
bool isPrime(int);
#endif //PAPER1_EUCLID_H
