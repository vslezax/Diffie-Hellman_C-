#ifndef DIFFIE_HELLMAN_USER_H
#define DIFFIE_HELLMAN_USER_H

#include <openssl/bn.h>
#include <iostream>

void printBignum(BIGNUM* num, const std::string& message){
    std::cout << message << std::endl;
    auto* str = new unsigned char[BN_num_bytes(num)];
    if (BN_bn2bin(num, str) == -1) {
        std::cerr << "BN_bn2bin error." << std::endl;
        delete[] str;
        return;
    }
    for (int i = 0; i < BN_num_bytes(num); i++){
        std::cout << static_cast<int>(str[i]);
    }
    delete[] str;
    std::cout << std::endl;
}

class User{
private:
    BIGNUM* a;
    BIGNUM* g;
    BIGNUM* p;
    BIGNUM* A;
    BIGNUM* K;
    BN_CTX* ctx;
    std::string name;
    int SIZE;
public:
    User(int size, const std::string& name){
        SIZE = size;
        a = BN_new();
        g = BN_new();
        p = BN_new();
        A = BN_new();
        K = BN_new();
        ctx = BN_CTX_new();
        this->name = name;
    }
    bool init_a(){
        if (BN_rand(a, SIZE, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
            std::cout << "BN_rand(a) error." << std::endl;
            return false;
        }
        return true;
    }
    bool generate_p_and_g(){
        if (BN_generate_prime_ex(p, SIZE, 1, nullptr, nullptr, nullptr) == 0){
            std::cout << "BN_generate_prime_ex2(p) error." << std::endl;
            return false;
        }
        if (BN_generate_prime_ex(g, SIZE, 1, nullptr, nullptr, nullptr) == 0){
            std::cout << "BN_rand(g) error." << std::endl;
            return false;
        }
        return true;
    }
    bool calculate_A(){
        if (BN_mod_exp(A, g, a, p, ctx) == 0){
            std::cout << "BN_mod_exp(A) error." << std::endl;
            return false;
        }
        return true;
    }
    bool calculate_K(){
        if (BN_mod_exp(K, A, a, p, ctx) == 0){
            std::cout << "BN_mod_exp(K) error." << std::endl;
            return false;
        }
        return true;
    }
    bool set_p_and_g(BIGNUM* p_copy, BIGNUM* g_copy){
        try{
            BN_copy(p, p_copy);
            BN_copy(g, g_copy);
        }
        catch (std::exception& e){
            std::cout << name + "'s func set_p_and_g thrown exception:\n" << e.what() << std::endl;
            return false;
        }
        return true;
    }
    void print_p(){
        printBignum(p, name + "'s p:");
    }
    void print_g(){
        printBignum(g, name + "'s g:");
    }
    void print_a(){
        printBignum(a, name + "'s a:");
    }
    void print_A(){
        printBignum(A, name + "'s A:");
    }
    void print_K(){
        printBignum(K, name + "'s K:");
    }
    BIGNUM* get_p(){
        return p;
    }
    BIGNUM* get_g(){
        return g;
    }
    BIGNUM* get_a(){
        return a;
    }
    BIGNUM* get_A(){
        return A;
    }
    BIGNUM* get_K(){
        return K;
    }
    ~User(){
        std::cout << name + "'s object start for deleting..." << std::endl;
        if (p != nullptr){
            BN_clear(p);
            std::cout << name + "'s p cleared." << std::endl;
        }
        if (g != nullptr){
            BN_clear(g);
            std::cout << name + "'s g cleared." << std::endl;
        }
        if (a != nullptr){
            BN_clear(a);
            std::cout << name + "'s a cleared." << std::endl;
        }
        if (A != nullptr){
            BN_clear(A);
            std::cout << name + "'s A cleared." << std::endl;
        }
        if (K != nullptr){
            BN_clear(K);
            std::cout << name + "'s K cleared." << std::endl;
        }
        if (ctx != nullptr){
            BN_CTX_free(ctx);
            std::cout << name + "'s ctx cleared." << std::endl;
        }
        std::cout << name + "'s object deleted.\n" << std::endl;
    }
};

#endif //DIFFIE_HELLMAN_USER_H
