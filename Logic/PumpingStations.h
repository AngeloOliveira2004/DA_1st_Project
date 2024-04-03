/**
 * @file PumpingStations.h
 * @brief Declaration of PumpingStations class.
 */
#define BOTH_WAYS 1;
#define UNI_DIRECTIONAL 0;

#ifndef PROJETO_PUMPINGSTATIONS_H
#define PROJETO_PUMPINGSTATIONS_H

#include "stdafx.h"

/**
 * @class PumpingStations
 * @brief Represents a pumping station.
 */
class PumpingStations {
private:

    std::string servicePointA; /**< First service point. */
    std::string servicePointB; /**< Second service point. */
    int capacity;               /**< Capacity of the pumping station. */
    bool direction;             /**< Direction of the pumping station. */

public:
    /**
     * @brief Constructs a new PumpingStations object.
     * @param servicePointA The first service point.
     * @param servicePointB The second service point.
     * @param capacity Capacity of the pumping station.
     * @param direction Direction of the pumping station.
     */
    PumpingStations(const std::string& servicePointA, const std::string& servicePointB,
                    int capacity, bool direction) :
            servicePointA(servicePointA), servicePointB(servicePointB),
            capacity(capacity), direction(direction) {}

    // Getters
    /**
     * @brief Gets the first service point.
     * @return The first service point.
     */
    std::string getServicePointA() const { return servicePointA; }
    /**
     * @brief Gets the second service point.
     * @return The second service point.
     */
    std::string getServicePointB() const { return servicePointB; }
    /**
     * @brief Gets the capacity of the pumping station.
     * @return The capacity.
     */
    int getCapacity() const { return capacity; }
    /**
     * @brief Gets the direction of the pumping station.
     * @return The direction.
     */
    bool getDirection() const { return direction; }

    // Setters
    /**
    * @brief Sets the first service point.
    * @param servicePointA The first service point to set.
    */
    void setServicePointA(const std::string& servicePointA) { this->servicePointA = servicePointA; }
    /**
     * @brief Sets the second service point.
     * @param servicePointB The second service point to set.
     */
    void setServicePointB(const std::string& servicePointB) { this->servicePointB = servicePointB; }
    /**
     * @brief Sets the capacity of the pumping station.
     * @param capacity The capacity to set.
     */
    void setCapacity(int capacity) { this->capacity = capacity; }
    /**
     * @brief Sets the direction of the pumping station.
     * @param direction The direction to set.
     */
    void setDirection(bool direction) { this->direction = direction; }

    /**
    * @brief Prints information about the pumping station.
    * @details Time Complexity: O(1)
    */
    void printInfo()
    {
        std::cout << servicePointA << " " << servicePointB << " " << capacity << " " << direction << "\n";
    }
    size_t hash() const {
        size_t hashValue = 0;

        // Combine hash values of member variables
        std::hash<std::string> stringHasher;
        std::hash<int> intHasher;
        std::hash<bool> boolHasher;

        hashValue ^= stringHasher(servicePointA) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        hashValue ^= stringHasher(servicePointB) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        hashValue ^= intHasher(capacity) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);
        hashValue ^= boolHasher(direction) + 0x9e3779b9 + (hashValue << 6) + (hashValue >> 2);

        return hashValue;
    }
};

// Define a custom hash function for PumpingStations
struct PumpingStationsHash {
    size_t operator()(const PumpingStations& ps) const {
        return ps.hash();
    }
};


#endif //PROJETO_PUMPINGSTATIONS_H
