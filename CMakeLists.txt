cmake_minimum_required(VERSION 3.27)
project(Diffie_Hellman)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(Diffie_Hellman main.cpp)

target_link_libraries(Diffie_Hellman ${OPENSSL_LIBRARIES})
