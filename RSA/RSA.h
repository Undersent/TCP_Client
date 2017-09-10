//
// Created by rafal on 10.09.17.
//

#ifndef TCP_CLIENT_RSA_H
#define TCP_CLIENT_RSA_H
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
            : _module(module), _converserPublicKey(converserPublicKey) {initializeKeys(true);}


    void initializeKeys(bool);
    std::vector<long> decryptString(std::vector<long> text);
    std::vector<long> encryptString(std::vector<long> text);
    long get_publicKey() const;
    long get_module() const;
    void set_converserPublicKey(long key);

private:
    long decrypt(long codeRSA);
    long encrypt(long codeRSA);
    long GCD(long a, long b);
    long extendedEuclideanModulo(long a, long n);


};


#endif //TCP_CLIENT_RSA_H
