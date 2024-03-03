#ifndef PROJETO_DELIVERYSITES_H
#define PROJETO_DELIVERYSITES_H

#include "stdafx.h"
#include "optional"

enum nodeTypes{
    FIRE_STATION,
    CITY,
    WATER_RESERVOIR
};

class DeliverySite {
private:
    nodeTypes type;

    //mandatory
    int id;
    std::string code;

    //optional
    std::shared_ptr<std::string> name;
    std::shared_ptr<std::string> municipality;

    std::shared_ptr<int> maxDelivery;
    std::shared_ptr<int> demand;
    std::shared_ptr<int> population;
public:
    DeliverySite(std::string  name,
                 std::string  municipality,
                 std::string  code,
                 int id,
                 int maxDelivery,
                 int demand,
                 int population,
                 nodeTypes type);

    // Getters
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getMunicipality() const;
    [[nodiscard]] std::string getCode() const;
    [[nodiscard]] int getId() const;
    [[nodiscard]] int getMaxDelivery() const;
    [[nodiscard]] int getDemand() const; // New getter
    [[nodiscard]] int getPopulation() const; // New getter
    nodeTypes getNodeType() const;

    // Setters
    void setCode(const std::string& code);
    void setMunicipality(const std::string& municipality);
    void setName(const std::string& name);
    void setId(int id);
    void setMaxDelivery(int maxDelivery);
    void setDemand(int demand); // New setter
    void setPopulation(int population); // New setter

    void printInfo() const;

    bool operator==(const DeliverySite& other) const {
        return code == other.code;
    }
};

namespace std {
    template <>
    struct hash<DeliverySite> {
        size_t operator()(const DeliverySite& deliverySite) const {
            // Use hash of the city code for hashing
            return hash<string>{}(deliverySite.getCode());
        }
    };

    template<>
    struct equal_to<DeliverySite> {
        bool operator()(const DeliverySite& deliverySite1, const DeliverySite& deliverySite2) const {
            // Compare only the city codes for equality
            return deliverySite1.getCode() == deliverySite2.getCode();
        }
    };
}

#endif //PROJETO_DELIVERYSITES_H
