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

    std::vector<Vertex<DeliverySite>*> sources;

    for(Vertex<DeliverySite>* deliverySite : g.getVertexSet()){
        if(deliverySite->getInfo().getNodeType() == WATER_RESERVOIR){
            sources.push_back(deliverySite);
        }
    }

    for(auto v : g.getVertexSet()){
    }

    return 0;
}
