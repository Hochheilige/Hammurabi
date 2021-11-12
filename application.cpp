#include <iostream>
#include <fstream>

#include <game_manager.hpp>
#include <saver.hpp>

auto main() -> int {
    Counselor counselor;
    GameManager gm;
    Saver saver;

    gm.GameInitialMessage();
    if (saver.IsFileExist() && saver.IsPlayerWantToLoad()) {
        saver.Load(counselor, gm);
    } else {
        gm.StartNewGame(counselor);
    }

    while(true) {
        counselor.GetInformationAboutCity();
        counselor.GetRulerInstructions();
        counselor.ManageCity();

        if (gm.IsPlayerExit()) {
            saver.Save(counselor, gm);
            break;
        }

        gm.IncreasePeople(counselor.GetDeadPeople());
        if (counselor.GetCurrentYear() > kMaxRounds) {
            gm.GameResults(counselor.GetLands(), counselor.GetPeople(), counselor.GetCurrentYear());
            if (!gm.IsPlayerWantPlayAgain()) {
                saver.Save(counselor, gm);
                break;
            } else {
                gm.StartNewGame(counselor); 
            }
        } else if (counselor.IsPopulationDead()) {
            if (!gm.IsPlayerWantPlayAgain()) {
                saver.Save(counselor, gm);
                break;
            } else {
                gm.StartNewGame(counselor);
            }
        } 
    }
}
