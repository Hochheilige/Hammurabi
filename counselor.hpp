#pragma once

#include "city.hpp"

class Counselor {
public:
	explicit Counselor(uint32_t lands_count, uint32_t people_count, uint32_t wheat_count)
		: city(lands_count, people_count, wheat_count) {
	}
	
	void BuyLands(uint32_t lands_count);
private:
	static constexpr uint32_t kWheatPerPerson = 20;
	static constexpr uint32_t kMaxLandPersonFarm = 10;
	static constexpr float kWheatPerFarm = 0.5;
	uint32_t land_price;

	City city;
};
