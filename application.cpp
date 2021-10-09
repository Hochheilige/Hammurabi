#include <iostream>

#include "counselor.hpp"

auto main() -> int {
    const uint32_t kMaxRounds = 10;
    uint32_t game_round = 0;
    
    Counselor counselor(City(1000, 100, 2800));
    
    while(game_round < kMaxRounds) {
        counselor.ManageCity();

        ++game_round;
    }
}
