#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    GreetRuler();
    std::cout << "Land cost is: " << randomizer.GetLandCost() << std::endl
              << "Wheat per land: " << randomizer.GetWheat() << std::endl
              << "Rat ate wheat: " << randomizer.GetWheatEatenByRat(city.GetWheat()) << std::endl
              << "Is plague happened? " << randomizer.IsPlagueHappened() << std::endl;
    ++current_year;
}

bool Counselor::IsPopulationDead() {
    return true; // at this moment
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}
