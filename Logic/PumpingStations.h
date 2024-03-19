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
    bool canRemovePumping(Graph<std::string>& g, const std::string& PumpingStationRemove);
};


#endif //PROJETO_PUMPINGSTATIONS_H
