#include <cstdint>
#include <iostream>

class GameManager {
public:
    GameManager() 
        : people_death_from_hunger(0),
          land_per_person(0) {
    }
    
    inline void IncreasePeople(const uint32_t people) {
        people_death_from_hunger += people;
    }

    void GameResults(const uint32_t lands, const uint32_t people, const uint8_t year);

private:
    uint32_t people_death_from_hunger;
    uint32_t land_per_person;
}