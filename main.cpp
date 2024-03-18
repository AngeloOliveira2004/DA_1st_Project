#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {

    std::thread t1(LoadFireStations);
    std::thread t2(LoadWaterReservoirs);
    std::thread t3(LoadPipes);
    std::thread t4(LoadCities);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    Graph<DeliverySite> g;

    createGraph(&g);

    DeliverySite cityToTest = DeliverySite("C_1");

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

    return 0;
}
