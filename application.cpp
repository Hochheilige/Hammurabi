#include <iostream>

#include "initial_game_constants.hpp"
#include "counselor.hpp"

auto main() -> int {
    Counselor counselor(
        kInitialRound,
        City(
            kDefaultLandsCount, 
            kDefaultPeopleCount, 
            kDefautWheatCount
        )
    );

    while(counselor.GetCurrentYear() <= kMaxRounds && !counselor.IsPopulationDead()) {
        counselor.GetInformationAboutCity();
        counselor.GetRulerInstructions();
        counselor.ManageCity();
    }
}
