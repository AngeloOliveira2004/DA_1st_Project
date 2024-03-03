#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
int main() {

    std::vector<Sinks> deliverySites;
    std::vector<PumpingStations> pumpingStations;
    std::vector<WaterReservoir> waterReservations;

    Graph<int>* g;

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
