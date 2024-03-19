#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadCities();
    LoadPipes();

    Graph<DeliverySite> g;

    createGraph(&g);


    //calculateMaxFlow(&g , cityToTest);
    calculateMaxFlowInEntireNetwork(&g);
    //maxFlowWithSuperSource(&g , cityToTest);

    std::vector<Edge<DeliverySite>*> pipes = getPipes(&g);

    double averageFlow = averagePipeCapacity(pipes);

    std::vector<std::pair<double , Edge<DeliverySite>*>> varianceInEachPoint;
    //double variance = variancePipeCapacityFlow(pipes , varianceInEachPoint);

    std::pair<double , Edge<DeliverySite>*> maxDif = maximumDIfferenceCapacityFlow(pipes);

    double avgVariance = 0.0;
    for(int i = 0 ; i <= 1000 ; i++){
        avgVariance += variancePipeCapacityFlow(pipes , varianceInEachPoint);
    }

    print("Average: ", false);
    print(averageFlow , true);


    print("Variance: ", false);
    print(avgVariance/1000 , true);

    print("Maximum Difference: " , false);
    print(maxDif.first , true);
    //maxDif.second->getOrig()->getInfo().printInfo();
    //maxDif.second->getDest()->getInfo().printInfo();

    print(maxDif.second->getFlow() , true);

    for(Vertex<DeliverySite>* ds: g.getVertexSet()){
        int sumFlow = 0;
        for(Edge<DeliverySite>* p : ds->getIncoming()){
            sumFlow += p->getFlow();
        }
        ds->setIncomingFlow(sumFlow);

        int difference = ds->getInfo().getDemand() - ds->getIncomingFlow();

        if(ds->getInfo().getNodeType() == CITY && difference > 0 ){
            std::cout << "The city of " << ds->getInfo().getName() << " with code " << ds->getInfo().getCode() << " doesn't receive enough water needing more " << difference << " units \n";
        }
    }

    return 0;
}
