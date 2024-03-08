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
        std::cout << node->getInfo().getCode() << " " << node->getInfo().getNodeType() << std::endl;
    }

    std::vector<DeliverySite> waterSources;

    return 0;
}
