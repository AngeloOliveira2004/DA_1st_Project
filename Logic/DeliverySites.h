#ifndef PROJETO_DELIVERYSITES_H
#define PROJETO_DELIVERYSITES_H

#include "stdafx.h"
#include "optional"

enum nodeTypes {
    FIRE_STATION,
    CITY,
    WATER_RESERVOIR
};

class DeliverySite {
private:
    std::string code;
    nodeTypes type;

public:
    DeliverySite(std::string code);
    std::string getCode() const;
    virtual int getDemand() const {return 0;};
    void setCode(const std::string& code);
    virtual nodeTypes getNodeType() const;

    bool operator==(const DeliverySite& other) const {
        return code == other.code;
    }
};

class FireStation : public DeliverySite {
    private:
        int id;
    public:
        FireStation(std::string code,int id);
        int getId() const;
        void setId(int id);
        nodeTypes getNodeType() const override;
};

class City : public DeliverySite {
    private:
        std::string name;
        int id;
        int demand;
        int population;
public:
    City(std::string name,std::string code,int id,int demand,int population);

    std::string getName() const;
    int getId() const;
    int getDemand() const override;
    int getPopulation() const;
    nodeTypes getNodeType() const override;

    void setName(const std::string& name);
    void setId(int id);
    void setDemand(int demand);
    void setPopulation(int population);



};

class WaterReservoir : public DeliverySite {
    private:
        std::string name;
        std::string municipality;
        int id;
        int maxDelivery;
    public:
        WaterReservoir(std::string name,std::string municipality,std::string code,int id,int maxDelivery);

        std::string getName() const;
        std::string getMunicipality() const;
        int getId() const;
        int getMaxDelivery() const;
        nodeTypes getNodeType() const override;

        void setName(const std::string& name);
        void setMunicipality(const std::string& municipality);
        void setId(int id);
        void setMaxDelivery(int maxDelivery);
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
