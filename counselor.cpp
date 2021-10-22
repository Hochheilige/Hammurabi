#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    city->SetLands(city->GetLands() + land_buy);
    PopulationChange();
    CollectWheat();
    ++current_year;
}

void Counselor::GetInformationAboutCity() {
    GreetRuler();
    if (IsFirstYear()) {
        GetOriginInformationAboutCity();
    } else { 
        std::cout << "In the " << current_year << " of your highest permission\n";
        if (not_fed_people != 0) {
            std::cout << not_fed_people << " starved to death and ";
        }  
        if (arrived_people != 0) {
            std::cout << arrived_people << " arrived to city\n";
        }
        if (is_plague_happened) {
            std::cout << "Plague killed half of people\n";
        } 
        std::cout << "The population of the city is " << city->GetPeople() << " people\n"
                  << "We collected " << wheat_collected << " by " << wheat_per_acre << " per acre\n"
                  << "Rats ate " << wheat_rat_ate << " left " << city->GetWheat() << " bushels in the barn\n"
                  << "Our city occupies " << city->GetLands() << " acres of land\n";
    }

    land_cost = static_cast<uint32_t>(randomizer->GetLandCost());
    std::cout << "Land cost is: " << land_cost << '\n';
}

void Counselor::GetRulerInstructions() {
    // maybe should create copy-ctor for city???
    std::unique_ptr<City> temp_city = std::make_unique<City>(
        city->GetLands(), city->GetPeople(), city->GetWheat()
    );
    while (true) {
        try{
            BuyLands();
            GetWheatToEat();
            GetWheatToSow();
            break;
        } catch (...) {
            std::cout << "error";
            temp_city.swap(city);
        }
    }
}

bool Counselor::IsPopulationDead() {
    return true; // at this moment
}

void Counselor::GreetRuler() {
    std::cout << "My lord, deign to tell you\n";
}

void Counselor::GetOriginInformationAboutCity() {
    std::cout << "In the 1 year of your highest permission\n" 
              << "The population of the city is " << city->GetPeople() << " people\n"
              << "We have " << city->GetWheat() << " bushels of wheat in the barn\n"
              << "Our city occupies " << city->GetLands() << " acres of land\n";
}

void Counselor::PopulationChange() {
    uint32_t fed_people = wheat_to_eat / kWheatPerPerson;
    not_fed_people = city->GetPeople() - fed_people;
    if (is_plague_happened = randomizer->IsPlagueHappened(); is_plague_happened) {
        fed_people /= 2;
    }
    CalculatePeopleArrivedToCity();
    city->SetPeople(fed_people + arrived_people);
}

void Counselor::CollectWheat() {
    wheat_rat_ate = static_cast<uint32_t>(randomizer->GetWheatEatenByRat(city->GetWheat()));
    wheat_per_acre = static_cast<uint32_t>(randomizer->GetWheat());
    wheat_collected = acre_to_sow * wheat_per_acre;
    city->SetWheat(city->GetWheat() + wheat_collected - wheat_rat_ate);
}

void Counselor::CalculatePeopleArrivedToCity() {
    arrived_people = not_fed_people / 2 + (5 - wheat_per_acre) * city->GetWheat() / 600 + 1;
	switch (arrived_people) {
		case 0: 
            arrived_people = 0;
            break;
		default:
            arrived_people = 50;
			break;
	}
}

void Counselor::BuyLands() {
    std::cout << "How many lands do u want to buy? ";
    while (true) {
        std::cin >> land_buy;
        if (land_buy * land_cost > city->GetWheat() || land_buy < 0) {
            throw("Not enough wheat to buy lands");
        } else {
            city->SetWheat(city->GetWheat() - land_buy * land_cost);
            break;
        }
    }
}

void Counselor::GetWheatToEat() {
    std::cout << "How many wheat do u want to eat ";
    while (true) {
        std::cin >> wheat_to_eat;
        if (wheat_to_eat < city->GetWheat() || wheat_to_eat < 0) {
            throw("Not enough wheat to eat");
        } else {
            city->SetWheat(city->GetWheat() - wheat_to_eat);
            break;
        }
    }
}

void Counselor::GetWheatToSow() {
    std::cout << "How many acre to sow? ";
    while (true) {
        std::cin >> acre_to_sow;
        if (acre_to_sow / kWheatPerFarm < city->GetWheat() || acre_to_sow < 0) {
            throw("Not enough wheat to sow");
        } else {
            city->SetWheat(city->GetWheat() - acre_to_sow / kWheatPerFarm);
            break;
        }
    }
}
