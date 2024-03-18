#include "User.h"

#define SIZE 16

int main() {
    User bob(SIZE, "Bob");
    User alice(SIZE, "Alice");

    // Alice and Bob generate a
    std::cout << "~~~ Alice and Bob generate a ~~~" << std::endl;
    bob.init_a();
    bob.print_a();
    alice.init_a();
    alice.print_a();
    std::cout << std::endl;

    // Alice generate p, g, A
    std::cout << "~~~ Alice generate p, g, A ~~~" << std::endl;
    alice.generate_p_and_g();
    alice.calculate_A();
    alice.print_p();
    alice.print_g();
    alice.print_A();

    // Alice's p, g, A  --->  Bob
    std::cout << "~~~ Alice's p, g, A  --->  Bob ~~~" << std::endl;
    bob.set_p_and_g(alice.get_p(), alice.get_g());
    bob.set_A(alice.get_A());
    bob.print_p();
    bob.print_g();
    bob.print_A();
    std::cout << std::endl;

    // Bob generate B, K by A
    std::cout << "~~~ Bob generate B, K by A ~~~" << std::endl;
    bob.calculate_B();
    bob.print_B();
    bob.calculate_K_by_A();
    bob.print_K();
    std::cout << std::endl;

    // Bob's B ---> Alice
    std::cout << "~~~ Bob's B ---> Alice ~~~" << std::endl;
    alice.set_B(bob.get_B());
    alice.print_B();
    std::cout << std::endl;

    // Alice generate K
    std::cout << "~~~ Alice generate K ~~~" << std::endl;
    alice.calculate_K_by_B();
    alice.print_K();
    std::cout << std::endl;
}
