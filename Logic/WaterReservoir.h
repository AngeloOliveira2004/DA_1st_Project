//Sink

#include "string"

#ifndef PROJETO_WATERRESERVATIONS_H
#define PROJETO_WATERRESERVATIONS_H

#include "stdafx.h"

class WaterReservoir {
private:
    std::string name;
    std::string municipality;
    std::string code;
    u_int8_t id;
    u_int16_t maxDelivery;
public:
    WaterReservoir(const std::string& name,
                   const std::string& municipality,
                   const std::string& code,
                   u_int8_t id,
                   u_int16_t maxDelivery)
            : name(name), municipality(municipality), code(code), id(id), maxDelivery(maxDelivery) {}

    // Getters
    std::string getName() const { return name; }
    std::string getMunicipality() const { return municipality; }
    std::string getCode() const { return code; }
    u_int8_t getId() const { return id; }
    u_int16_t getMaxDelivery() const { return maxDelivery; }

    // Setters
    void setName(const std::string& name) { this->name = name; }
    void setMunicipality(const std::string& municipality) { this->municipality = municipality; }
    void setCode(const std::string& code) { this->code = code; }
    void setId(u_int8_t id) { this->id = id; }
    void setMaxDelivery(u_int16_t maxDelivery) { this->maxDelivery = maxDelivery; }

    void printInfo()
    {
        std::cout << name << " " << municipality << " " << code << " "<<maxDelivery <<  " " << id<<"\n";
    }
};


#endif //PROJETO_WATERRESERVATIONS_H
