//
// Created by jose-costa on 2/26/24.
//

#define BOTH_WAYS 1;
#define UNI_DIRECTIONAL 0;

#ifndef PROJETO_PUMPINGSTATIONS_H
#define PROJETO_PUMPINGSTATIONS_H

#include "stdafx.h"

class PumpingStations {
private:
    
    std::string servicePointA;
    std::string servicePointB;
    int capacity;
    bool direction;

public:
    PumpingStations(const std::string& servicePointA, const std::string& servicePointB,
                    int capacity, bool direction) :
            servicePointA(servicePointA), servicePointB(servicePointB),
            capacity(capacity), direction(direction) {}

    // Getters
    std::string getServicePointA() const { return servicePointA; }
    std::string getServicePointB() const { return servicePointB; }
    int getCapacity() const { return capacity; }
    bool getDirection() const { return direction; }

    // Setters
    void setServicePointA(const std::string& servicePointA) { this->servicePointA = servicePointA; }
    void setServicePointB(const std::string& servicePointB) { this->servicePointB = servicePointB; }
    void setCapacity(int capacity) { this->capacity = capacity; }
    void setDirection(bool direction) { this->direction = direction; }

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


#endif //PROJETO_PUMPINGSTATIONS_H
