#include <iostream>

#include <counselor.hpp>

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
        std::cout << "In the " << static_cast<uint32_t>(current_year) << " of your highest permission\n";

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

    land_cost = static_cast<uint8_t>(randomizer->GetLandCost());
    std::cout << "Land cost is: " << static_cast<uint32_t>(land_cost) << '\n';
}

void Counselor::GetRulerInstructions() {
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
            temp_city->SetLands(city->GetLands())
                      .SetPeople(city->GetPeople())
                      .SetWheat(city->GetWheat());
            std::cout << "Oh, Lord, spare us! We have only " << city->GetPeople() << " people, "
                      << city->GetWheat() << " bushels of wheat and " 
                      << city->GetLands() << " acres of land\n";
        }
    }
}

bool Counselor::IsPopulationDead() {
    if (is_most_population_starved_to_death) {
        std::cout << "My Lord, we lost most of our people! The city is dead!\n\nGAME OVER\n\n";
        return true;
    }
    return false;
}

std::ofstream& operator << (std::ofstream& out, Counselor& counselor) {
    out.write(reinterpret_cast<char*>(&counselor.current_year), sizeof(counselor.current_year));
    out.write(reinterpret_cast<char*>(&counselor.land_cost), sizeof(counselor.land_cost));
    out.write(reinterpret_cast<char*>(&counselor.is_plague_happened), sizeof(counselor.is_plague_happened));
    out.write(
        reinterpret_cast<char*>(&counselor.is_most_population_starved_to_death),
        sizeof(counselor.is_most_population_starved_to_death)
    );
    
    for (size_t i = 0; i < 2; ++i) {
        out.write(reinterpret_cast<char*>(&counselor.people_changes[i]), sizeof(counselor.people_changes[i]));
    }

    for (size_t i = 0; i < 3; ++i) {
        out.write(reinterpret_cast<char*>(&counselor.wheat_changes[i]), sizeof(counselor.wheat_changes[i]));
        out.write(reinterpret_cast<char*>(&counselor.ruler_input[i]), sizeof(counselor.ruler_input[i]));
    }

    out << *counselor.city.get();
    return out;
}

std::ifstream& operator >> (std::ifstream& in, Counselor& counselor) {
    in.read(reinterpret_cast<char*>(&counselor.current_year), sizeof(counselor.current_year));
    in.read(reinterpret_cast<char*>(&counselor.land_cost), sizeof(counselor.land_cost));
    in.read(reinterpret_cast<char*>(&counselor.is_plague_happened), sizeof(counselor.is_plague_happened));
    in.read(
        reinterpret_cast<char*>(&counselor.is_most_population_starved_to_death),
        sizeof(counselor.is_most_population_starved_to_death)
    );
    
    for (size_t i = 0; i < 2; ++i) {
        in.read(reinterpret_cast<char*>(&counselor.people_changes[i]), sizeof(counselor.people_changes[i]));
    }

    for (size_t i = 0; i < 3; ++i) {
        in.read(reinterpret_cast<char*>(&counselor.wheat_changes[i]), sizeof(counselor.wheat_changes[i]));
        in.read(reinterpret_cast<char*>(&counselor.ruler_input[i]), sizeof(counselor.ruler_input[i]));
    }

    in >> *counselor.city;
    
    return in;
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
    wheat_changes[WheatChanges::kWheatPerAcre] =  static_cast<uint32_t>(
        randomizer->GetWheat()
    );

    const uint32_t acre_to_sow = static_cast<uint32_t>(ruler_input[RulerInput::kAcreToSow]);
    wheat_changes[WheatChanges::kWheatCollected] = acre_to_sow * wheat_changes[WheatChanges::kWheatPerAcre];

    uint32_t wheat_collected = wheat_changes[WheatChanges::kWheatCollected];

    wheat_changes[WheatChanges::kWheatRatAte] = static_cast<uint32_t>(
        randomizer->GetWheatEatenByRat(city->GetWheat() + wheat_collected)
    );

    wheat_collected -= wheat_changes[WheatChanges::kWheatRatAte];

    city->SetWheat(city->GetWheat() + wheat_collected);
}

void Counselor::CalculatePeopleArrivedToCity() {
    const uint32_t not_fed_people = people_changes[PeopleChanges::kNotFedPeople];
    const uint32_t wheat_per_acre = wheat_changes[WheatChanges::kWheatPerAcre];
    const int32_t arrived_people = not_fed_people / 2 + (5 - wheat_per_acre) * city->GetWheat() / 600 + 1;
    if (arrived_people <= 0) {
        people_changes[PeopleChanges::kArrivedPeople] = 0;
    } else if (arrived_people > 50) {
        people_changes[PeopleChanges::kArrivedPeople] = 50;
    } else {
        people_changes[PeopleChanges::kArrivedPeople] = static_cast<uint32_t>(arrived_people);
    }
}

void Counselor::BuyLands() {
    std::cout << "How many lands do u want to buy? ";
    int32_t land_buy = 0;
    std::cin >> land_buy;
    if (land_buy < 0 || static_cast<uint32_t>(land_buy) * land_cost > city->GetWheat()) {
        throw("Not enough wheat to buy lands");
    } else {
        city->SetWheat(city->GetWheat() - static_cast<uint32_t>(land_buy) * land_cost);
        ruler_input[RulerInput::kLandBuy] = land_buy;
    }

}

void Counselor::GetWheatToEat() {
    std::cout << "How many wheat do u want to eat? ";
    int32_t wheat_to_eat = 0;
    std::cin >> wheat_to_eat;
    if (wheat_to_eat < 0 || static_cast<uint32_t>(wheat_to_eat) > city->GetWheat()) {
        throw("Not enough wheat to eat");
    } else {
        city->SetWheat(city->GetWheat() - static_cast<uint32_t>(wheat_to_eat));
        ruler_input[RulerInput::kWheatToEat] = wheat_to_eat;
    }
}

void Counselor::GetWheatToSow() {
    std::cout << "How many acre to sow? ";
    int32_t acre_to_sow = 0;
    std::cin >> acre_to_sow;
    if (acre_to_sow < 0 || static_cast<uint32_t>(acre_to_sow) / kWheatPerFarm > city->GetWheat()
        || static_cast<uint32_t>(acre_to_sow) / kMaxLandPersonFarm > city->GetPeople()) {
        throw("Not enough wheat or people to sow");
    } else {
        city->SetWheat(city->GetWheat() - static_cast<uint32_t>(acre_to_sow) / kWheatPerFarm);
        ruler_input[RulerInput::kAcreToSow] = acre_to_sow;
    }
}
