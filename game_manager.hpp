#pragma once

#include <cstdint>
#include <iostream>
#include <fstream>

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

    bool IsPlayerWantPlayAgain();

    bool IsPlayerExitGame();

    friend inline std::ofstream& operator << (std::ofstream& out, GameManager& gm) {
    	out.write(reinterpret_cast<char*>(&gm), sizeof(gm));
    	return out;
	}

	friend inline std::ifstream& operator >> (std::ifstream& in, GameManager& gm) {
    	in.read(reinterpret_cast<char*>(&gm), sizeof(gm));
    	return in;
	}

private:
    uint32_t people_death_from_hunger;
    uint32_t land_per_person;
};
