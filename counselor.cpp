#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    GreetRuler();
    ++current_year;
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}
