#include <random>

class Randomizer {
public:
    Randomizer() 
        : generator(device()), 
          wheat_distribution(kMinWheatPerLand, kMaxWheatPerLand),
          land_cost_distribution(kMinLandCost, kMaxLandCost) {
    }

    inline int32_t GetWheat() {
        return wheat_distribution(generator);
    }

    inline int32_t GetLandCost() {
        return land_cost_distribution(generator);
    }

    inline int32_t GetWheatEatenByRat(uint32_t current_wheat) {
        const int32_t kMaxWheatPerRat = static_cast<int32_t>(kRatCoefficient * static_cast<float>(current_wheat));
        rat_distribution = std::uniform_int_distribution<>(kMinWheatPerRat, kMaxWheatPerRat);
        return rat_distribution(generator);
    }

private:
    static constexpr uint8_t kMinWheatPerLand = 1;
    static constexpr uint8_t kMaxWheatPerLand = 6;
    static constexpr uint8_t kMinLandCost = 17;
    static constexpr uint8_t kMaxLandCost = 26;
    static constexpr uint8_t kMinWheatPerRat = 0;
    static constexpr float kRatCoefficient = 0.07f;
    std::random_device device;
    std::mt19937 generator;
    std::uniform_int_distribution<> wheat_distribution;
    std::uniform_int_distribution<> land_cost_distribution;
    std::uniform_int_distribution<> rat_distribution;
};
