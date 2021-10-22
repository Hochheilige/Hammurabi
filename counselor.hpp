#pragma once

#include <memory>
#include <exception>

#include "city.hpp"
#include "randomizer.hpp"


// TODO: think how to reduce occupied space
class Counselor {
public:
	Counselor() = delete;
	Counselor(const Counselor&) = delete;
	Counselor(Counselor&&) = delete;
	Counselor& operator= (const Counselor&) = delete;
    Counselor& operator= (Counselor&&) = delete;

	// TODO: make move semantic work in this constructor
	explicit Counselor(uint32_t rounds, City&& c)
		: current_year(rounds), 
		  city(std::make_unique<City>(std::move(c))),
		  randomizer(new Randomizer()) {
	}
	
	inline uint32_t GetCurrentYear() { return current_year; }

	void ManageCity();

	void GetInformationAboutCity();

	void GetRulerInstructions();

	bool IsPopulationDead();

private:
	inline bool IsFirstYear() { return current_year == 1; }

	void GreetRuler();

	void GetOriginInformationAboutCity();

	void PopulationChange();

	void CollectWheat();

	void CalculatePeopleArrivedToCity();
	
	void BuyLands();

	void GetWheatToEat();

	void GetWheatToSow();

private:
	static constexpr uint32_t kWheatPerPerson = 20;
	static constexpr uint32_t kMaxLandPersonFarm = 10;
	static constexpr uint32_t kWheatPerFarm = 2;

private:
	// Может быть переменные заменить на С-массивы или просто массивы
	// и сделать енум чтобы обращаться к нужным полям
	uint32_t current_year;
	uint32_t land_cost;
	uint32_t not_fed_people;
	uint32_t arrived_people;
	uint32_t wheat_collected;
	uint32_t wheat_per_acre;
	uint32_t wheat_rat_ate;
	int32_t land_buy;
	int32_t wheat_to_eat;
	int32_t acre_to_sow;
	bool is_plague_happened;

private:
	std::unique_ptr<City> city;
	std::unique_ptr<Randomizer> randomizer;
};
