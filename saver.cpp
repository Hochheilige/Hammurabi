#include <saver.hpp>

bool Saver::IsPlayerWantToLoad() {
    std::cout << "Would you like to load a game? Y or N : ";
    char answer; 
    std::cin >> answer;
    return answer == 'Y';
}
