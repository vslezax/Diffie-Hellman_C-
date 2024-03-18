#ifndef DIFFIE_HELLMAN_HACKER_H
#define DIFFIE_HELLMAN_HACKER_H

#include <openssl/bn.h>
#include <iostream>

#include "Utils.h"

class Hacker{
private:
    BIGNUM* a_A;
    BIGNUM* a_B;
    BIGNUM* g;
    BIGNUM* p;
    BIGNUM* A;
    BIGNUM* B;
    BIGNUM* A_new;
    BIGNUM* B_new;
    BN_CTX* ctx;
    std::string name;
public:
    Hacker(const std::string& name){
        this->name = name;
        A = BN_new();
        B = BN_new();
        g = BN_new();
        p = BN_new();
        A_new = BN_new();
        B_new = BN_new();
        a_A = BN_new();
        a_B = BN_new();
        ctx = BN_CTX_new();
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
    bool set_A(BIGNUM* A_copy){
        try{
            BN_copy(A, A_copy);
        }
        catch (std::exception& e){
            std::cout << name + "'s func set_A thrown exception:\n" << e.what() << std::endl;
            return false;
        }
        return true;
    }
    bool set_B(BIGNUM* B_copy){
        try{
            BN_copy(B, B_copy);
        }
        catch (std::exception& e){
            std::cout << name + "'s func set_B thrown exception:\n" << e.what() << std::endl;
            return false;
        }
        return true;
    }
    bool generate_a_A(){
        if (BN_rand(a_A, BN_num_bits(A), BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
            std::cout << "BN_rand(a) error." << std::endl;
            return false;
        }
        return true;
    }
    bool generate_a_B(){
        if (BN_rand(a_B, BN_num_bits(B), BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
            std::cout << "BN_rand(a) error." << std::endl;
            return false;
        }
        return true;
    }
    bool calculate_new_A(){
        if (BN_mod_exp(A_new, g, a_A, p, ctx) == 0){
            std::cout << "BN_mod_exp(A) error." << std::endl;
            return false;
        }
        return true;
    }
    bool calculate_new_B(){
        if (BN_mod_exp(B_new, g, a_B, p, ctx) == 0){
            std::cout << "BN_mod_exp(B) error." << std::endl;
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
    void print_A(){
        printBignum(A, name + "'s A:");
    }
    void print_new_A(){
        printBignum(A_new, name + "'s A_new:");
    }
    void print_B(){
        printBignum(B, name + "'s B:");
    }
    void print_new_B(){
        printBignum(B_new, name + "'s B_new:");
    }
    void print_a_A(){
        printBignum(a_A, name + "'s a_A:");
    }
    void print_a_B(){
        printBignum(a_B, name + "'s a_B:");
    }
    BIGNUM* get_p(){
        return p;
    }
    BIGNUM* get_g(){
        return g;
    }
    BIGNUM* get_new_A(){
        return A_new;
    }
    BIGNUM* get_new_B(){
        return B_new;
    }
    ~Hacker(){
        BN_clear(p);
        BN_clear(g);
        BN_clear(A);
        BN_clear(B);
        BN_clear(A_new);
        BN_clear(B_new);
        BN_clear(a_A);
        BN_clear(a_B);
        BN_CTX_free(ctx);
        std::cout << name + "'s object deleted." << std::endl;
        name.clear();
    }
};

#endif //DIFFIE_HELLMAN_HACKER_H
