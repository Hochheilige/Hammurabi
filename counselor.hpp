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
	explicit Counselor(uint8_t rounds, City&& c)
		: current_year(rounds),
		  people_changes(new uint32_t[2]),
		  wheat_changes(new uint32_t[3]),
		  ruler_input(new int32_t[3]), 
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
	static constexpr float kPercentPopulationToLoseGame =  0.45f;

	enum PeopleChanges : uint8_t {
		kNotFedPeople = 0,
		kArrivedPeople,
	};

	enum WheatChanges : uint8_t {
		kWheatCollected = 0,
		kWheatPerAcre,
		kWheatRatAte,
	};

	enum RulerInput : uint8_t {
		kLandBuy = 0,
		kWheatToEat,
		kAcreToSow,
	};

private:
	uint8_t current_year = 0;
	uint8_t land_cost = 0;
	
	bool is_plague_happened = false;
	bool is_most_population_starved_to_death = false;

	std::unique_ptr<uint32_t[]> people_changes;
	std::unique_ptr<uint32_t[]> wheat_changes;
	std::unique_ptr<int32_t[]> ruler_input;
	
private:
	std::unique_ptr<City> city;
	std::unique_ptr<Randomizer> randomizer;
};
