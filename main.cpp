#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();

    Graph<DeliverySite> g;

    createGraph(&g);

    for(auto node : g.getVertexSet()){
        std::cout << node->getInfo().getCode() << std::endl;
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
