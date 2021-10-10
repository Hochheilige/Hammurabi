#include <iostream>

#include "counselor.hpp"

auto main() -> int {
    static constexpr uint32_t kInitialRound = 1;
    static constexpr uint32_t kMaxRounds = 10;
    static constexpr uint32_t kDefaultLandsCount = 1000;
    static constexpr uint32_t kDefaultPeopleCount = 100;
    static constexpr uint32_t kDefautWheatCount = 2800;

    Counselor counselor(
        kInitialRound,
        City(
            kDefaultLandsCount, 
            kDefaultPeopleCount, 
            kDefautWheatCount
        )
    );
    
    while(counselor.GetCurrentYear() <= kMaxRounds || !counselor.IsPopulationDead()) {
        counselor.ManageCity();
    }
}
