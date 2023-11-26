#include "GUIGenerator.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>

std::string generateGUID() {
    // Get current time
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    // Generate a random number
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis(0, std::numeric_limits<uint64_t>::max());
    uint64_t randomValue = dis(gen);

    // Combine timestamp and random number to create a GUID-like value
    uint64_t combinedValue = (milliseconds << 16) | (randomValue & 0xFFFF);

    // Format the result as a string
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << combinedValue;

    return ss.str();
}