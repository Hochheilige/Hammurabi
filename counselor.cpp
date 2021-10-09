#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    GreetRuler();
    ++current_year;
}

bool Counselor::IsPopulationDead() {
    return true; // at this moment
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}
