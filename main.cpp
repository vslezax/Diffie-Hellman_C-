#include "User.h"

#define SIZE 16

int main() {
    User bob(SIZE, "Bob");
    User alice(SIZE, "Alice");

    std::cout << (bob.init_a() ? "Bob's init_a() success." : "Bob's init_a() fail") << std::endl;
    bob.print_a();
    std::cout << (alice.init_a() ? "Alice's init_a() success." : "Alice's init_a() fail") << std::endl;
    alice.print_a();
    std::cout << std::endl;

    bob.generate_p_and_g();
    bob.print_p();
    bob.print_g();
    alice.set_p_and_g(bob.get_p(), bob.get_g());
    alice.print_p();
    alice.print_g();
    std::cout << std::endl;

    bob.calculate_A();
    alice.calculate_A();
    bob.print_A();
    alice.print_A();
    std::cout << std::endl;
}
