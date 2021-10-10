#pragma once

#include "city.hpp"
#include "randomizer.hpp"

class Counselor {
public:
	Counselor() = delete;
	Counselor(const Counselor&) = delete;
	Counselor(Counselor&&) = delete;
	Counselor& operator= (const Counselor&) = delete;
    Counselor& operator= (Counselor&&) = delete;

	explicit Counselor(uint32_t rounds, City&& c)
		: current_year(rounds), city(std::move(c)) {
	}
	
	inline uint32_t GetCurrentYear() { return current_year; }

	void ManageCity();

	bool IsPopulationDead();

	void BuyLands(uint32_t lands_count);

private:
	void GreetRuler();

	void GetInformationAboutCity();

	void GetOriginInformationAboutCity();

	inline bool IsFirstYear() { return current_year == 1; }

private:
	static constexpr uint32_t kWheatPerPerson = 20;
	static constexpr uint32_t kMaxLandPersonFarm = 10;
	static constexpr float kWheatPerFarm = 0.5;

private:
    uint32_t current_year;
	uint32_t land_price;
	City city;
	Randomizer randomizer;
};
