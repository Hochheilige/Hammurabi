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

	// TODO: make move semantic work in this constructor
	explicit Counselor(uint32_t rounds, City&& c)
		: current_year(rounds), city(std::move(c)) {
	}
	
	inline uint32_t GetCurrentYear() { return current_year; }

	void ManageCity();

	void GetInformationAboutCity();

	void BuyLands();

	void WheatToEat();

	void WheatToSow();

	bool IsPopulationDead();

private:
	void GreetRuler();

	void GetOriginInformationAboutCity();

	void GetLandCost();

	inline bool IsFirstYear() { return current_year == 1; }

	void NumberOfPeopleArrivedToCity();

private:
	static constexpr uint32_t kWheatPerPerson = 20;
	static constexpr uint32_t kMaxLandPersonFarm = 10;
	static constexpr uint32_t kWheatPerFarm = 2;

private:
	uint32_t current_year;
	uint32_t land_cost;
	uint32_t land_buy;
	uint32_t wheat_to_eat;
	uint32_t acre_to_sow;
	uint32_t not_fed_people;
	uint32_t arrived_people;
	uint32_t wheat_collected;
	uint32_t wheat_per_acre;
	uint32_t wheat_rat_ate;
	bool is_plague_happened;

private:
	City city;
	Randomizer randomizer;
};
