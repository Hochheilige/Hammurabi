#include <iostream>

#include "counselor.hpp"

void Counselor::ManageCity() {
    city->SetLands(city->GetLands() + static_cast<uint32_t>(ruler_input[RulerInput::kLandBuy]));
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

        const uint32_t not_fed_people = people_changes[PeopleChanges::kNotFedPeople];
        const uint32_t arrived_people = people_changes[PeopleChanges::kArrivedPeople];
        const uint32_t wheat_collected = wheat_changes[WheatChanges::kWheatCollected];
        const uint32_t wheat_per_acre = wheat_changes[WheatChanges::kWheatPerAcre];
        const uint32_t wheat_rat_ate = wheat_changes[WheatChanges::kWheatRatAte];

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
                  << "We collected " << wheat_collected << " bushels of wheat by " << wheat_per_acre << " per acre\n"
                  << "Rats destroyed " << wheat_rat_ate << " bushels of wheat, left " << city->GetWheat() << " bushels in the barn\n"
                  << "Our city now occupies " << city->GetLands() << " acres of land\n";
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
            temp_city.swap(city);
            std::cout << "Oh, Lord, spare us! We have only " << city->GetPeople() << " people, "
                      << city->GetWheat() << " bushels of wheat and " 
                      << city->GetLands() << " acres of land\n";
        }
    }
}

bool Counselor::IsPopulationDead() {
    if (is_most_population_starved_to_death) {
        std::cout << "My Lord, we lost most of our people! The city is dead!\nGAME OVER\n";
        return true;
    }
    return false;
}

void Counselor::GreetRuler() {
    std::cout << "--------------------------------------------------------------------------\n"
              <<"My lord, deign to tell you\n";
}

void Counselor::GetOriginInformationAboutCity() {
    std::cout << "In the 1 year of your highest permission\n" 
              << "The population of the city is " << city->GetPeople() << " people\n"
              << "We have " << city->GetWheat() << " bushels of wheat in the barn\n"
              << "Our city occupies " << city->GetLands() << " acres of land\n";
}

void Counselor::PopulationChange() {
    const uint32_t wheat_to_eat = static_cast<uint32_t>(
        ruler_input[RulerInput::kWheatToEat]
    );
    uint32_t fed_people = static_cast<uint32_t>(wheat_to_eat) / kWheatPerPerson;
    people_changes[PeopleChanges::kNotFedPeople] = city->GetPeople() - fed_people;

    const uint32_t not_fed_people_limit = static_cast<uint32_t>(
        static_cast<float>(city->GetPeople()) * kPercentPopulationToLoseGame
    );

    if (not_fed_people_limit <= people_changes[PeopleChanges::kNotFedPeople]) {
        is_most_population_starved_to_death = true;
    }
    
    if (is_plague_happened = randomizer->IsPlagueHappened(); is_plague_happened) {
        fed_people /= 2;
    }

    CalculatePeopleArrivedToCity();
    city->SetPeople(fed_people + people_changes[PeopleChanges::kArrivedPeople]);
}

void Counselor::CollectWheat() {
    wheat_changes[WheatChanges::kWheatRatAte] = static_cast<uint32_t>(
        randomizer->GetWheatEatenByRat(city->GetWheat())
    );

    wheat_changes[WheatChanges::kWheatPerAcre] =  static_cast<uint32_t>(
        randomizer->GetWheat()
    );

    const uint32_t acre_to_sow = static_cast<uint32_t>(ruler_input[RulerInput::kAcreToSow]);
    wheat_changes[WheatChanges::kWheatCollected] = acre_to_sow * wheat_changes[WheatChanges::kWheatPerAcre];

    const uint32_t wheat_collected = wheat_changes[WheatChanges::kWheatCollected] 
                                   - wheat_changes[WheatChanges::kWheatRatAte];
    city->SetWheat(city->GetWheat() + wheat_collected);
}

void Counselor::CalculatePeopleArrivedToCity() {
    const uint32_t not_fed_people = people_changes[PeopleChanges::kNotFedPeople];
    const uint32_t wheat_per_acre = wheat_changes[WheatChanges::kWheatPerAcre];
    const uint32_t arrived_people = not_fed_people / 2 + (5 - wheat_per_acre) * city->GetWheat() / 600 + 1;
	switch (arrived_people) {
		case 0: 
            people_changes[PeopleChanges::kArrivedPeople] = 0;
            break;
		default:
            people_changes[PeopleChanges::kArrivedPeople] = 50;
			break;
	}
}

void Counselor::BuyLands() {
    std::cout << "How many lands do u want to buy? ";
    int32_t land_buy = 0;
    while (true) {
        std::cin >> land_buy;
        if (land_buy < 0 || static_cast<uint32_t>(land_buy) * land_cost > city->GetWheat()) {
            throw("Not enough wheat to buy lands");
        } else {
            city->SetWheat(city->GetWheat() - static_cast<uint32_t>(land_buy) * land_cost);
            ruler_input[RulerInput::kLandBuy] = land_buy;
            break;
        }
    }
}

void Counselor::GetWheatToEat() {
    std::cout << "How many wheat do u want to eat? ";
    int32_t wheat_to_eat = 0;
    while (true) {
        std::cin >> wheat_to_eat;
        if (wheat_to_eat < 0 || static_cast<uint32_t>(wheat_to_eat) > city->GetWheat()) {
            throw("Not enough wheat to eat");
        } else {
            city->SetWheat(city->GetWheat() - static_cast<uint32_t>(wheat_to_eat));
            ruler_input[RulerInput::kWheatToEat] = wheat_to_eat;
            break;
        }
    }
}

void Counselor::GetWheatToSow() {
    std::cout << "How many acre to sow? ";
    int32_t acre_to_sow = 0;
    while (true) {
        std::cin >> acre_to_sow;
        if (acre_to_sow < 0 || static_cast<uint32_t>(acre_to_sow) / kWheatPerFarm > city->GetWheat()
            || static_cast<uint32_t>(acre_to_sow) / kMaxLandPersonFarm > city->GetPeople()) {
            throw("Not enough wheat or people to sow");
        } else {
            city->SetWheat(city->GetWheat() - static_cast<uint32_t>(acre_to_sow) / kWheatPerFarm);
            ruler_input[RulerInput::kAcreToSow] = acre_to_sow;
            break;
        }
    }
}
