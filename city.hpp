#pragma once

#include <vector>
#include <cstdint>

using Land = bool; 
using People = uint32_t;
using Wheat = uint32_t;

class City {
public:
    City() = delete;
    City(const City&) = delete;
    City(const City&&) = delete;
    City& operator= (const City&) = delete;
    City& operator= (const City&&) = delete;

    explicit City(uint32_t lands_count, People people, Wheat wheat) 
        : resources(lands_count, people, wheat) {
    }

private:
    struct Resources {
        explicit Resources(uint32_t lands_count, People people_count, Wheat wheat_count) 
            : lands(lands_count), people(people_count), wheat(wheat_count) {
        }

        std::vector<Land> lands;
        People people;
        Wheat wheat;
    };

    Resources resources;
};
