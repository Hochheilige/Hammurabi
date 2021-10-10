#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    GreetRuler();

    if (IsFirstYear()) {
        GetOriginInformationAboutCity();
    } else {
        GetInformationAboutCity();
    }
    
    std::cout << "Land cost is: " << randomizer.GetLandCost() << '\n'
              << "Wheat per land: " << randomizer.GetWheat() << '\n'
              << "Rat ate wheat: " << randomizer.GetWheatEatenByRat(city.GetWheat()) << '\n'
              << "Is plague happened? " << randomizer.IsPlagueHappened() << '\n';
    ++current_year;
}

bool Counselor::IsPopulationDead() {
    return true; // at this moment
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}

void Counselor::GetInformationAboutCity() {
    std::cout << "In the " << current_year << " of your highest permission\n";
}

void Counselor::GetOriginInformationAboutCity() {
    std::cout << "In the 1 year of your highest permission\n" 
              << "The population of the city is " << city.GetPeople() << " people\n"
              << "We have " << city.GetWheat() << " bushels of wheat in the barn\n"
              << "Our city occupies " << city.GetLands() << " acres of land\n";
}
