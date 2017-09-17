//
// Created by rafal on 08.09.17.
//

#ifndef PROJECT_RSA_H
#define PROJECT_RSA_H

#include <vector>

class RSA {

private:
    long _ownPublicKey{};
    long _converserPublicKey{};
    long _privateKey{};
    long _module{};


public:
    RSA();

    RSA(long module, long converserPublicKey)
            : _module(module), _converserPublicKey(converserPublicKey) { initializeKeys(true); }


    void initializeKeys(bool);

    std::vector<long> &decryptString(std::vector<long> &text) const;

    std::vector<long> &encryptString(std::vector<long> &text) const;

    std::string encryptString(const std::string &text) const;

    std::string decryptString(const std::string &text) const;

    const long get_publicKey() const;

    const long get_module() const;

    void set_converserPublicKey(const long &key);

private:
    long decrypt(long codeRSA) const;

    long encrypt(long codeRSA) const;

    long GCD(long a, long b);

    long extendedEuclideanModulo(long a, long n);

};


#endif //PROJECT_RSA_H
