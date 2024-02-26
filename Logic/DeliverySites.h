//
// Created by jose-costa on 2/26/24.
//

#ifndef PROJETO_DELIVERYSITES_H
#define PROJETO_DELIVERYSITES_H

#include "string"

enum class DeliverySiteType {
    FIRE_STATION,
    CITY
};

class DeliverySites {
private:
    DeliverySiteType type;

    std::string* name;
    std::string code;
    u_int8_t id;
    u_int16_t* demand;
    u_int16_t* population;

};


#endif //PROJETO_DELIVERYSITES_H
