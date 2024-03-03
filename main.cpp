#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();

    Graph<DeliverySite>* g;

    createGraph(g);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
