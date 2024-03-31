#include "Logic/stdafx.h"
#include "Logic/LoadingFunctions.h"
#include "Logic/Logic.h"
#include "Interface/UI.h"

int main() {

    UI ui;
    ui.loading_stuff(ui);

    /*
    calculateMaxFlowInEntireNetwork(&g);

    auto flow = 0;
    for(auto v : g.getVertexSet()){
        for(auto e : v->getIncoming()){
            flow += e->getFlow();
        }
    }
    flow = 0;
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == WATER_RESERVOIR){
            for(auto e : v->getAdj()){
                print(e->getFlow() , true);
                flow += e->getFlow();
            }
            if(flow > v->getInfo().getMaxDelivery()){
                std::cout << v->getInfo().getCode() << " " << flow << " " << v->getInfo().getMaxDelivery();

            }
        }

    }

    print(flow , true);
    print("\n" , true);
    print("\n", true);
    print("\n" , true);

    std::unordered_set<Edge<DeliverySite>*> edgesSet;

    for(Vertex<DeliverySite>* v : g.getVertexSet()){
        for(Edge<DeliverySite>* e : v->getAdj()){
            edgesSet.insert(e);
        }
    }

    std::vector<Edge<DeliverySite>*> edgeVector(edgesSet.begin() , edgesSet.end());
    std::vector<Edge<DeliverySite>*> pipes = getPipes(&g);

    Metrics metrics{};

    metrics = g.calculateMetrics();

    //print(metrics.variance , true);

    int initialFlow = g.calculateFlowAcrossEdges();

    print("Initial flow : " , false);
    print(initialFlow , true);

    heuristic(&g , edgeVector);

    initialFlow = g.calculateFlowAcrossEdges();

    print("End flow : " , false);
    print(initialFlow , true);

    g.calculateMetrics();

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


    print(flow , false);

     */

    // ui.doStuff();

    return 0;
}
