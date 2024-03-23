#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"

int main() {

    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();

    Graph<DeliverySite> g;

    createGraph(&g);

    DeliverySite cityToTest = DeliverySite("C_6");

    //calculateMaxFlow(&g , cityToTest);
    calculateMaxFlowInEntireNetwork(&g);
    //maxFlowWithSuperSource(&g , cityToTest);

/*
    std::vector<Edge<DeliverySite>*> pipes = getPipes(&g);

    double averageFlow = averagePipeCapacity(pipes);

    std::vector<std::pair<double , Edge<DeliverySite>*>> varianceInEachPoint;
    double variance = variancePipeCapacityFlow(pipes , varianceInEachPoint);

    std::pair<double , Edge<DeliverySite>*> maxDif = maximumDIfferenceCapacityFlow(pipes);

    print("Average: ", false);
    print(averageFlow , true);


    print("Variance: ", false);
    print(variance , true);

    print("Maximum Difference: " , false);
    print(maxDif.first , true);

    //maxDif.second->getOrig()->getInfo().printInfo();
    //maxDif.second->getDest()->getInfo().printInfo();

    print(maxDif.second->getFlow() , true);
*/

    //printDistance(&g);
    /*
    auto sum = 0;
    auto required = 0;
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == CITY){
            for(auto e : v->getIncoming()){
                sum += e->getFlow();
            }

            if(sum >= v->getInfo().getDemand()){
                required++;
            }else{

                print("City " , false);
                print(v->getInfo().getCode() , false);
                print("Did not meet requirements", true);
                print("Current flow: ", false);
                print(sum, true);
                print("Desired flow: ", false);
                print(v->getInfo().getDemand(), true);


            }
            sum = 0;
        }
    }

    print("Cities meeting requirements: " , false);
    print(required , true);
    */

    std::unordered_set<Edge<DeliverySite>*> edgesSet;

    for(Vertex<DeliverySite>* v : g.getVertexSet()){
        for(Edge<DeliverySite>* e : v->getAdj()){
            edgesSet.insert(e);
        }
    }

    std::vector<Edge<DeliverySite>*> edgeVector(edgesSet.begin() , edgesSet.end());
    auto flow = 0;
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == CITY){
            for(auto e : v->getIncoming()){
                flow += e->getFlow();
            }
        }
    }
    std::vector<Edge<DeliverySite>*> pipes = getPipes(&g);
    double variance = variancePipeCapacityFlow(pipes , nullptr);

    print(variance , true);

    int initialFlow = g.calculateFlowAcrossEdges();

    heuristic(&g , edgeVector);

    auto newflow = 0;
    for(auto v : g.getVertexSet()){

        if(v->getInfo().getNodeType() == CITY){
            for(auto e : v->getIncoming()){
                newflow += e->getFlow();
            }
        }
    }

    print(newflow , true);

    initialFlow = g.calculateFlowAcrossEdges();

    print("End flow : " , false);
    print(initialFlow , true);

    print(g.checkEdgesFlow() , true);
/*
    for(auto v : g.getVertexSet()){
        for(auto e : v->getAdj()){
            print(e->getFlow() , false);
            print(" " , false);
            print(e->getOrig()->getInfo().getCode() , false);
            print(" " , false);
            print(e->getDest()->getInfo().getCode() , false);
            print(" " , true);
        }
    }
*/
    return 0;
}
