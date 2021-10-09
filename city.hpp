#pragma once

#include <vector>
#include <cstdint>

class City {
public:
    City() = delete;
    City(const City&) = delete;
    City& operator= (const City&) = delete;
    City& operator= (City&&) = delete;

    explicit City(City&& city) 
        : resources(std::move(city.resources)) {
    }

    explicit City(uint32_t lands, uint32_t people, uint32_t wheat)
        : resources(lands, people, wheat) {
    }

    inline uint32_t GetLands() { return resources.lands; }
    inline uint32_t GetPeople() { return resources.people; }
    inline uint32_t GetWheat() { return resources.wheat; }

    inline City& SetLands(const uint32_t lands) {
        resources.lands = lands;
        return *this;
    }

    inline City& SetPeople(const uint32_t people) {
        resources.people = people; 
        return *this;
    }

    inline City& SetWheat(const uint32_t wheat) {
        resources.wheat = wheat;
        return *this;
    }

private:
    struct Resources {
        Resources() = delete;
        Resources(const Resources&) = delete;
        Resources& operator= (const Resources&) = delete;
        Resources& operator= (Resources&&) = delete;
        
        explicit Resources(Resources&& res)
            : lands(res.lands), people(res.people), wheat(res.wheat) {
        }

        explicit Resources(uint32_t lands_count, uint32_t people_count, uint32_t wheat_count)
            : lands(lands_count), people(people_count), wheat(wheat_count) {
        }

        uint32_t lands;
        uint32_t people;
        uint32_t wheat;
    };

    Resources resources;
};
