//
// Created by rafal on 08.09.17.
//

#ifndef PROJECT_RSA_H
#define PROJECT_RSA_H
#include <vector>

namespace RSA {

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
        std::string encryptString(std::string text);
        std::string decryptString(std::string String);
        long get_publicKey() const;
        long get_module() const;
        void set_converserPublicKey(long key);

    private:
        long decrypt(long codeRSA);
        long encrypt(long codeRSA);
        long GCD(long a, long b);
        long extendedEuclideanModulo(long a, long n);

        friend class RSATest;

    };

}
#endif //PROJECT_RSA_H
