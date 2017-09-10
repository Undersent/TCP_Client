//
// Created by rafal on 10.09.17.
//

#include <vector>
#include <cstdlib>
#include <algorithm>
#include "RSA.h"


RSA::RSA() {
    initializeKeys(false);
}

long RSA::decrypt(long codeRSA) {
    long result, q;

//algorithm Horner

    result = 1;
    for (q = _privateKey; q > 0; q /= 2) {
        if (q % 2) result = (result * codeRSA) % _module;
        codeRSA = (codeRSA * codeRSA) % _module; // kolejna potęga
    }
    return result;
}


long RSA::encrypt(long codeRSA) {
    long result, q;

//algorithm Horner

    result = 1;
    for (q = _converserPublicKey; q > 0; q /= 2) {
        if (q % 2) result = (result * codeRSA) % _module;
        codeRSA = (codeRSA * codeRSA) % _module; // kolejna potęga
    }
    return result;
}


std::vector<long> RSA::decryptString(std::vector<long> text) {

    for(long & c : text) {
        decrypt(c);
    }
    return text;
}

std::vector<long> RSA::encryptString(std::vector<long> text) {
    for(long & c : text){
        encrypt(c);
    }
    return text;
}


void RSA::initializeKeys(bool isConverser) {
     //TODO:
    std::vector<int> primes{11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    long p, q, phi, e;
    int n = {0};
    std::default_random_engine generator;
    generator.seed (time( NULL ));
    std::uniform_int_distribution<int> distribution(0,primes.size()-1);
    do {
        p = primes[distribution(generator)];
        q = primes[distribution(generator)];
    } while (p == q);

    phi = (p - 1) * (q - 1);
    if(!isConverser) {
        _module = p * q;
    }

    for (e = 3; GCD(e, phi) != 1; e += 2);

    _privateKey = extendedEuclideanModulo(e, phi);
    _ownPublicKey = e;


}


long RSA::GCD(long a, long b) {
    long temp;

    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    };
    return a;
}


long RSA::extendedEuclideanModulo(long a, long n) {
    long a0, n0, p0, p1, q, r, temp;

    p0 = 0;
    p1 = 1;
    a0 = a;
    n0 = n;
    q = n0 / a0;
    r = n0 % a0;
    while (r > 0) {
        temp = p0 - q * p1;
        if (temp >= 0)
            temp = temp % n;
        else
            temp = n - ((-temp) % n);
        p0 = p1;
        p1 = temp;
        n0 = a0;
        a0 = r;
        q = n0 / a0;
        r = n0 % a0;
    }
    return p1;
}

long RSA::get_publicKey() const {
    return _ownPublicKey;
}


void RSA::set_converserPublicKey(long key) {
    _converserPublicKey = key;
}

long RSA::get_module() const {
    return _module;
}
