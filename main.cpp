#include <iostream>
#include <openssl/rand.h>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <vector>

#define SIZE 16

void exit(std::vector<BIGNUM*> nums, BN_CTX* ctx, int code){
    for (auto i: nums){
        BN_clear(i);
    }
    nums.clear();
    BN_CTX_free(ctx);
    exit(code);
}

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


int main() {
    BN_CTX* ctx = BN_CTX_new();

    // Generate p and g
    BIGNUM* p = BN_new();
    if (BN_generate_prime_ex(p, SIZE, 1, nullptr, nullptr, nullptr) == 0){
        std::cout << "BN_generate_prime_ex2 error." << std::endl;
        exit({p}, ctx, 1);
    }
    printBignum(p, "p generated:");
    BIGNUM* g = BN_new();
    if (BN_generate_prime_ex(g, SIZE, 1, nullptr, nullptr, nullptr) == 0){
        std::cout << "BN_rand(g) error." << std::endl;
        exit({p, g}, ctx, 1);
    }
    printBignum(g, "g generated:");

    // Generate a and b
    BIGNUM* a = BN_new();
    if (BN_rand(a, SIZE, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_rand(a) error." << std::endl;
        exit({p, g, a}, ctx, 1);
    }
    printBignum(a, "a generated:");
    BIGNUM* b = BN_new();
    if (BN_rand(b, SIZE, BN_RAND_TOP_ONE, BN_RAND_BOTTOM_ANY) == 0){
        std::cout << "BN_rand(b) error." << std::endl;
        exit({p, g, a, b}, ctx, 1);
    }
    printBignum(b, "b generated:");

    // Generate A
    BIGNUM* A = BN_new();
    if (BN_mod_exp(A, g, a, p, ctx) == 0){
        std::cout << "BN_mod_exp(A) error." << std::endl;
        exit({p, g, a, b, A}, ctx, 1);
    }
    printBignum(A, "A generated:");
    // Generate B
    BIGNUM* B = BN_new();
    if (BN_mod_exp(B, g, b, p, ctx) == 0){
        std::cout << "BN_mod_exp(B) error." << std::endl;
        exit({p, g, a, b, A, B}, ctx, 1);
    }
    printBignum(B, "B generated:");

    // Generate K_A
    BIGNUM* K_A = BN_new();
    if (BN_mod_exp(K_A, A, b, p, ctx) == 0){
        std::cout << "BN_mod_exp(K) error." << std::endl;
        exit({p, g, a, b, A, B, K_A}, ctx, 1);
    }
    printBignum(K_A, "K_A generated:");
    // Generate K_B
    BIGNUM* K_B = BN_new();
    if (BN_mod_exp(K_B, A, b, p, ctx) == 0){
        std::cout << "BN_mod_exp(K) error." << std::endl;
        exit({p, g, a, b, A, B, K_A, K_B}, ctx, 1);
    }
    printBignum(K_B, "K_B generated:");

    exit({p, g, a, b, A, B, K_A, K_B}, ctx, 0);
}
