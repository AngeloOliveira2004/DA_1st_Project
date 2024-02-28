//
// Created by jose-costa on 2/26/24.
//

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
};


#endif //PROJETO_WATERRESERVATIONS_H
