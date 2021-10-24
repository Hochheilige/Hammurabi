#include <iostream>

#include "initial_game_constants.hpp"
#include "counselor.hpp"
#include "game_manager.hpp"

auto main() -> int {
    Counselor counselor(
        kInitialRound,
        City(
            kDefaultLandsCount, 
            kDefaultPeopleCount, 
            kDefautWheatCount
        )
    );

    std::cout << sizeof(Counselor) << "\n";

    while(true) {
        counselor.GetInformationAboutCity();
        counselor.GetRulerInstructions();
        counselor.ManageCity();

        if (counselor.GetCurrentYear() > kMaxRounds || counselor.IsPopulationDead()) {
            break;
        }
    }
}
