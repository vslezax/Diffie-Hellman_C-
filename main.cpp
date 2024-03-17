#include <iostream>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/bn.h>

#define SIZE 16

int main() {
    // Generate p and g
    BIGNUM* p = BN_new();
    if (BN_rand(p, SIZE, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_generate_prime_ex2 error." << std::endl;
        BN_clear(p);
        exit(-1);
    }
    std::cout << "p generated." << std::endl;
    BIGNUM* g = BN_new();
    if (BN_rand(g, SIZE, BN_RAND_TOP_ANY, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_rand(g) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        exit(-1);
    }
    std::cout << "g generated." << std::endl;

    // Generate a and b
    BIGNUM* a = BN_new();
    if (BN_rand(a, SIZE, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_rand(a) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        BN_clear(a);
        exit(-1);
    }
    std::cout << "a generated." << std::endl;
    BIGNUM* b = BN_new();
    if (BN_rand(b, SIZE, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_rand(b) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        BN_clear(a);
        BN_clear(b);
        exit(-1);
    }
    std::cout << "b generated." << std::endl;

    // Generate A, then K
    BIGNUM* A = BN_new();
    if (BN_mod_exp(A, g, a, p, nullptr) == 0){
        std::cout << "BN_mod_exp(A) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        BN_clear(a);
        BN_clear(b);
        BN_clear(A);
        exit(-1);
    }
    std::cout << "A generated." << std::endl;
    BIGNUM* K = BN_new();
    if (BN_mod_exp(K, A, b, p, nullptr) == 0){
        std::cout << "BN_mod_exp(K) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        BN_clear(a);
        BN_clear(b);
        BN_clear(A);
        BN_clear(K);
        exit(-1);
    }
    std::cout << "K generated." << std::endl;

    auto* str = new unsigned char[BN_num_bytes(K)];
    if (BN_bn2bin(K, str) == NULL){
        std::cout << "BN_bn2bin(K) error." << std::endl;
        BN_clear(p);
        BN_clear(g);
        BN_clear(a);
        BN_clear(b);
        BN_clear(A);
        BN_clear(K);
        exit(-1);
    }
    std::cout << str;

    BN_clear(p);
    BN_clear(g);
    BN_clear(a);
    BN_clear(b);
    BN_clear(A);
    BN_clear(K);
}
