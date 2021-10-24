#include <iostream>
#include <fstream>

#include "initial_game_constants.hpp"
#include "counselor.hpp"
#include "game_manager.hpp"
#include "saver.hpp"

auto main() -> int {
    Counselor counselor;
    GameManager gm;
    Saver saver;

    if (saver.IsFileExist()) {
        saver.Load(counselor, gm);
    } else {
        counselor.SetYear(kInitialRound)
                 .SetCity(
                    City(
                        kDefaultLandsCount,
                        kDefaultPeopleCount,
                        kDefautWheatCount
                    )
                );
    }

    while(true) {
        counselor.GetInformationAboutCity();
        counselor.GetRulerInstructions();
        counselor.ManageCity();

        gm.IncreasePeople(counselor.GetDeadPeople());
        if (counselor.GetCurrentYear() > kMaxRounds) {
            gm.GameResults(counselor.GetLands(), counselor.GetPeople(), counselor.GetCurrentYear());
            if (!gm.IsPlayerWantPlayAgain()) {
                break;
            } else {
                counselor.SetYear(kInitialRound)
                .SetCity(
                    City(
                        kDefaultLandsCount,
                        kDefaultPeopleCount,
                        kDefautWheatCount
                    )
                )
                .SetEvents();
            }
        } else if (counselor.IsPopulationDead()) {
            if (!gm.IsPlayerWantPlayAgain()) {
                break;
            } else {
                counselor.SetYear(kInitialRound)
                .SetCity(
                    City(
                        kDefaultLandsCount,
                        kDefaultPeopleCount,
                        kDefautWheatCount
                    )
                )
                .SetEvents();
            }
        }

        if (gm.IsPlayerExitGame()) {
            saver.Save(counselor, gm);
            break;
        }
    }
}
