#pragma once

#include "city.hpp"

class Counselor {
public:
	Counselor() = delete;
	Counselor(const Counselor&) = delete;
	Counselor(Counselor&&) = delete;
	Counselor& operator= (const Counselor&) = delete;
    Counselor& operator= (Counselor&&) = delete;

	explicit Counselor(City&& c)
		: city(std::move(c)) {
	}
	
	void ManageCity();

	void BuyLands(uint32_t lands_count);
private:
	void GreetRuler();

	static constexpr uint32_t kWheatPerPerson = 20;
	static constexpr uint32_t kMaxLandPersonFarm = 10;
	static constexpr float kWheatPerFarm = 0.5;
	uint32_t land_price;

	City city;
};
