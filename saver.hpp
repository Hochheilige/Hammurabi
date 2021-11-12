#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include <counselor.hpp>
#include <game_manager.hpp>

class Saver {
public:
    Saver() = default;
    Saver(const Saver&) = delete;
    Saver(std::string&& file) = delete;
    Saver& operator= (const Saver&) = delete;
    Saver& operator= (Saver&&) = delete;

    inline void Save(Counselor& counselor, GameManager& gm) {
        std::ofstream out(filename, std::ios::binary);
        out << counselor << gm;
    }

    inline void Load(Counselor& counselor, GameManager& gm) {
        std::cout << "Game is loaded\n";
        std::ifstream in(filename, std::ios::binary);
        in >> counselor >> gm;
    }

    inline bool IsFileExist() {
        return std::filesystem::exists(filename);
    }

    bool IsPlayerWantToLoad();

private:
    std::string filename = "HammurabiGameSave.bin";
};
