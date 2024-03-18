#ifndef DIFFIE_HELLMAN_UTILS_H
#define DIFFIE_HELLMAN_UTILS_H

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

#endif //DIFFIE_HELLMAN_UTILS_H
