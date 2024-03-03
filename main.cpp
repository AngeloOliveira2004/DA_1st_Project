#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();

    Graph<DeliverySite> g;

    createGraph(&g);
    int a = 0;
    for(auto node : g.getVertexSet()){
        std::cout << node->getInfo().getCode() << " " << node->getInfo().getNodeType() << std::endl;
        a += node->getAdj().size();
    }

    std::cout << a << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
