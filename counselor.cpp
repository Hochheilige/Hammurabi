#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    city.SetLands(city.GetLands() + land_buy);

    wheat_rat_ate = static_cast<uint32_t>(randomizer.GetWheatEatenByRat(city.GetWheat()));
    wheat_per_acre = static_cast<uint32_t>(randomizer.GetWheat());
    uint32_t current_wheat = city.GetWheat();
    wheat_collected = acre_to_sow * wheat_per_acre;
    city.SetWheat(wheat_collected + (current_wheat - acre_to_sow / kWheatPerFarm) - wheat_rat_ate - wheat_to_eat - land_buy * land_cost);

    const uint32_t current_people = city.GetPeople();
    uint32_t fed_people = wheat_to_eat / 20;
    not_fed_people = current_people - fed_people;
    if (is_plague_happened = randomizer.IsPlagueHappened(); is_plague_happened) {
        is_plague_happened = true;
        fed_people /= 2;
    }
    NumberOfPeopleArrivedToCity();
    city.SetPeople(fed_people + arrived_people);

    ++current_year;
}

void Counselor::GetInformationAboutCity() {
    GreetRuler();
    if (IsFirstYear()) {
        GetOriginInformationAboutCity();
    } else { 
        std::cout << "In the " << current_year << " of your highest permission\n"
                  << not_fed_people << " starved to death and " << arrived_people << " arrived to city\n";
        if (is_plague_happened) {
            std::cout << "Plague killed half of people\n";
        } 
        std::cout << "The population of the city is " << city.GetPeople() << " people\n"
                  << "We collected " << wheat_collected << " by " << wheat_per_acre << " per acre\n"
                  << "Rats ate " << wheat_rat_ate << " left " << city.GetWheat() << " bushels in the barn\n"
                  << "Our city occupies " << city.GetLands() << " acres of land\n";
    }

    GetLandCost();
}

void Counselor::BuyLands() {
    std::cout << "How many lands do u want to buy? ";
    std::cin >> land_buy;
}

void Counselor::WheatToEat() {
    std::cout << "How many wheat do u want to eat ";
    std::cin >> wheat_to_eat;
}

void Counselor::WheatToSow() {
    std::cout << "How many acre to sow? ";
    std::cin >> acre_to_sow;
}

bool Counselor::IsPopulationDead() {
    return true; // at this moment
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}

void Counselor::GetOriginInformationAboutCity() {
    std::cout << "In the 1 year of your highest permission\n" 
              << "The population of the city is " << city.GetPeople() << " people\n"
              << "We have " << city.GetWheat() << " bushels of wheat in the barn\n"
              << "Our city occupies " << city.GetLands() << " acres of land\n";
}

void Counselor::GetLandCost() {
    land_cost = static_cast<uint32_t>(randomizer.GetLandCost());
    std::cout << "Land cost is: " << land_cost << '\n';
}

void Counselor::NumberOfPeopleArrivedToCity() {
    arrived_people = not_fed_people / 2 + (5 - wheat_per_acre) * city.GetWheat() / 600 + 1;
	switch (arrived_people) {
		case 0: 
            arrived_people = 0;
            break;
		default:
            arrived_people = 50;
			break;
	}
}
