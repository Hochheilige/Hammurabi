#pragma once

#include <vector>
#include <cstdint>
#include <iostream>
#include <fstream>

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

    inline uint32_t GetLands() const { return resources.lands; }
    inline uint32_t GetPeople() const { return resources.people; }
    inline uint32_t GetWheat() const { return resources.wheat; }

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

    friend inline std::ostream& operator << (std::ostream& out, City& city){
        out.write(reinterpret_cast<char*>(&city), sizeof(city));
        return out;
    }

    friend inline std::istream& operator >> (std::istream& in, City& city) {
        in.read(reinterpret_cast<char*>(&city), sizeof(city));
        return in;
    }

private:
    struct Resources {
        Resources() = default;
        Resources(const Resources&) = delete;
        Resources& operator= (const Resources&) = delete;
        Resources& operator= (Resources&& res) = delete;
       
        explicit Resources(Resources&& res)
            : lands(res.lands), people(res.people), wheat(res.wheat) {
                res.lands = res.people = res.wheat = 0;
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
