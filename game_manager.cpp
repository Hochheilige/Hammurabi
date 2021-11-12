#include <game_manager.hpp>

void GameManager::GameInitialMessage() {
    std::cout << "Welcome to Hammurabi game\nTake on the role of the ruler of the city.\n" 
              << "Your task is to lead the country to prosperity or at least keep your place on the throne for 10 years\n\n";
}

void GameManager::GameResults(const uint32_t lands, const uint32_t people, const uint8_t year) {
    land_per_person = lands / people;
    people_death_from_hunger /= year;

    std::cout << "Game statistic:\n";

    if (people_death_from_hunger > 33 && land_per_person < 7) {
        std::cout << "Game result is bad\nBecause of your incompetence in management," 
                  << "the people staged a riot, and expelled you from their city.\n"
                  << "Now you are forced to eke out a miserable existence in exile";
    } else if (people_death_from_hunger > 10 && land_per_person < 9) {
        std::cout << "Game result is satisfactory\nYou ruled with an iron hand,"
                  << "like Nero and Ivan the Terrible.\n"
                  <<  "The people have breathed a sigh of relief, and no one wants to see you as a ruler anymore";
    } else if (people_death_from_hunger > 3 && land_per_person < 10) {
        std::cout << "Game result is good\n"
                  << "You did quite well, of course, you have detractors, but many would like to see you at the head of the city again";
    } else {
        std::cout << "Game result is excellent\n"
                  << "Fantastic! Charlemagne, Disraeli and Jefferson couldn't have done better together";
    }
}

bool GameManager::IsPlayerWantPlayAgain() {
    std::cout << "Would you like to play again? Y or N: ";
    char answer;
    std::cin >> answer;
    return answer == 'Y';
}

bool GameManager::IsPlayerExit() {
    std::cout << "Would you like to exit? Y or N: ";
    char answer;
    std::cin >> answer;
    return answer == 'Y';
}

void GameManager::StartNewGame(Counselor& counselor) {
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
