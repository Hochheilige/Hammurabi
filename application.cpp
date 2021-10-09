#include <iostream>

#include "city.hpp"

auto main() -> int {
    const uint32_t kMaxRounds = 10;
    uint32_t game_round = 0;

    City city(1000, 100, 2800);

    while(game_round < kMaxRounds) {
        std::cout << "My lord, deign to tell you\n";

        ++game_round;
    }
}
