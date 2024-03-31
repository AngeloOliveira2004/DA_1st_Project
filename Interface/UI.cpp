#include "UI.h"
#include "../Logic/Logic.h"
#include <thread>
#include <chrono>

UI::UI() {}

void UI::clear_screen() {
    int i = 0;
    while(i != 100) {
        std::cout << std::endl;
        i++;
    }
}

bool UI::validate_input(char &op, const char lower_bound, const char upper_bound) {
    std::string tempValue;
    while(true){
        std::cin >> tempValue;
        std::cout << "\n";
        op = tempValue[0];
        op = std::toupper(op);
        if (std::cin.fail() || tempValue.length() != 1) {
            std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        }else{
            break;
        }
    }
    while (op < lower_bound || op > upper_bound) {
        std::cout << "Introduce a valid option (" << lower_bound << "-" << upper_bound << "): ";
        std::cin.clear();
        std::cin >> op;
    }
    return true;
}

void UI::loading_stuff(UI &ui) {
    LoadFireStations();
    LoadWaterReservoirs();
    LoadPipes();
    LoadCities();
    createGraph(&g);
    std::cout << "Load Finished" << std::endl;
    std::cout << "Press A to start the program: ";
    char op;
    validate_input(op,'A','A');
    menu_start();
}

void UI::menu_start() {
    char op;
    std::cout << "######################################################################" << std::endl
         << "@ @ @  @@@@@  @@@@@  @@@@@  @@@@@           @@@@@   @@@    @@@   @    " << std::endl
         << "@ @ @  @   @    @    @@     @  @@             @    @   @  @   @  @    " << std::endl
         << "@ @ @  @@@@@    @    @@@@@  @@@@              @    @   @  @   @  @    " << std::endl
         << "@ @ @  @   @    @    @@     @@ @@             @    @   @  @   @  @    " << std::endl
         << " @@@   @   @    @    @@@@@  @@ @@             @     @@@    @@@   @@@@@" << std::endl
         << "######################################################################" << std::endl << '\n'
         << "Welcome to the Analysis Tool for Water Supply Management, what would you like to do?" << std::endl
         << "A. Proceed to the application" << std::endl
         << "B. Close the application" << std::endl
         << "Insert the letter: " ;
    validate_input(op,'A','B');
    switch(op){
        case 'A':
            main_menu();
            break;
        case 'B':
            std::cout << "Thanks for using our analysis tool for water supply management!" << std::endl << "\n"
                 << "Made by: " << std::endl
                 << "Ângelo Oliveira || 202207798" << std::endl
                 << "José Costa      || 202207871" << std::endl
                 << "Bruno Fortes    || 202209730" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Espera 2 segundos antes de fechar o terminal
            exit(0);

    }
}

void UI::main_menu(){
    clear_screen();
    char op;
   std::cout << "What would you like to know?" <<std::endl;
   std::cout << "A. Run Max Flow algorithm" <<std::endl
             << "B. Check if every city meets it's water demand" <<std::endl
             << "C. Check heuristic stats of the max flow" <<std::endl
             << "D. Evaluate network's resiliency" <<std::endl
             << "E. Exit the program"
             << "Insert your choice:";

    validate_input(op, 'A', 'E');
    switch(op){
        case 'A':
            max_flow();
            break;
        case 'B':
            check_demand();
            break;
        case 'C':
            check_heuristic();
            break;
        case 'D':
            break;
        case 'E':
           std::cout << "Thanks for using our management system app!" <<std::endl << "\n"
                 << "Made by: " <<std::endl
                 << "Ângelo Oliveira || 202207798" <<std::endl
                 << "José Costa      || 202207871" <<std::endl
                 << "Bruno Fortes    || 202209730" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Espera 2 segundos antes de fechar o terminal
            exit(0);
        default:
            std::cerr << "Error";
    }
}

Graph<DeliverySite> UI::getGraph() const {
    return g;
}

void UI::max_flow(){
    char op;
    std::cout << "What would you like to do?" << std::endl
              << "A. Calculate max flow for the entire network" << std::endl
              << "B. Calculate max flow for a specific city" << std::endl
              << "Insert your choice:";

    validate_input(op, 'A', 'B');
    switch (op) {
        case 'A': {
            char op1;
            std:: cout << "Would you like to only get the max flow result or the listing of max flows of the cities" << std::endl
                       << "A. Only the result" << std::endl
                       << "B. Listing for all cities" << std::endl
                       << "Insert your choice:" << std::endl;
            validate_input(op1, 'A', 'B');

            DeliverySite supersource = DeliverySite("SuperSource");
            DeliverySite supersink = DeliverySite("SuperSink");
            createSuperSourceSink(&g,supersource,supersink);
            double max_flow = edmondsKarp(&g,supersource,supersink);
            removeSuperSourceSink(&g,supersource,supersink);

            switch (op1) {
                case 'A': {
                    std::cout << "The max flow for the entire network is: " << max_flow << std::endl;
                    break;
                }
                case 'B': {
                    for(auto v : g.getVertexSet()){
                        if(v->getInfo().getNodeType() == CITY)
                            std::cout << "|Name: " << v->getInfo().getName() << " | Code: " <<  v->getInfo().getCode() << " | Flow : " << v->calculateIncomingFlow() << "|" << std::endl;
                    }
                    std::cout << "The max flow for the entire network is: " << max_flow << std::endl;

                    break;
                }
            }
            break;
        }
        case 'B':{
            std::string code;
            bool foundVertex = false;
            DeliverySite supersource = DeliverySite("SuperSource");

            while (!foundVertex) {
                std::cout << "Insert the code of the city: " << std::endl;
                std::cin >> code;

                DeliverySite sink = DeliverySite(code);

                if (!g.findVertex(sink)) {
                    std::cout << "Error: Vertex with code '" << code << "' not found. Please try again." << std::endl;
                } else {
                    foundVertex = true;
                }
            }
            DeliverySite sink = DeliverySite(code);

            createSuperSource(&g,supersource);
            double max_flow = edmondsKarp(&g,supersource,sink);
            removeSuperSourceSink(&g,supersource,sink);

            std::cout << "The max flow for the city " << code << " is: " << max_flow << std::endl;

            break;
        }
    }

};


void UI::check_demand(){

    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");
    createSuperSourceSink(&g,supersource,supersink);
    edmondsKarp(&g,supersource,supersink);
    removeSuperSourceSink(&g,supersource,supersink);


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
}

void UI::check_heuristic(){
    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");

    createSuperSourceSink(&g,supersource,supersink);
    edmondsKarp(&g,supersource,supersink);
    removeSuperSourceSink(&g,supersource,supersink);

    heuristic(&g);
}



void UI::doStuff() {
    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");

    createSuperSourceSink(&g,supersource,supersink);
    double max_flow = edmondsKarp(&g,supersource,supersink);
    removeSuperSourceSink(&g,supersource,supersink);


    std::cout << std::endl << "Max Flow garai: " << max_flow;

    heuristic(&g);
/*
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == CITY)
            std::cout << v->getInfo().getCode() << " flow :" << v->calculateIncomingFlow() << std::endl;
    }
*/
    double flow = 0;

    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() ==    CITY){
            for(auto e : v->getIncoming()){
                flow += e->getFlow();
            }
        }
    }

    std::cout << "\n" << "Max Flow : " << flow << "\n";


    for(auto e : g.getEdges()){
        if(e->getFlow() < 0){
            print("EITAEITAEITA" , false);
        }
    }
    auto incomingAqua = 0;
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == CITY){
            incomingAqua = 0;
            for(auto e : v->getIncoming()){
                incomingAqua += e->getFlow();
            }
            if(incomingAqua > v->getInfo().getDemand()){
                print("DEMASIADA AGUA CARALHOOOO" , true);
                print(incomingAqua , true);
                print(v->getInfo().getDemand() , true);
            }
        }
    }

    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == WATER_RESERVOIR){
            incomingAqua = 0;
            for(auto e : v->getAdj()){
                incomingAqua += e->getFlow();
            }
            auto a = v->getInfo().getMaxDelivery();
            if(incomingAqua > v->getInfo().getMaxDelivery()){
                print("TA VAZANDO AGUA DO CU" , true);
                print(incomingAqua , true);
                print(v->getInfo().getDemand() , true);
            }
        }
    }

    for(auto v : g.getVertexSet()){
        for(auto e : v->getAdj()){
            if(e->getFlow() < 0){
                print("EITAAA CARALHOOOOO" , true);
            }
        }
    }
/*
    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() != WATER_RESERVOIR)
            std::cout << v->getInfo().getCode() << " " << v->calculateIncomingFlow() << " " << v->calculateOutgoingFlow() << "\n";
    }

    for(auto v : g.getVertexSet()){
        if(v->getInfo().getNodeType() == WATER_RESERVOIR)
            std::cout << v->getInfo().getCode() << " " << v->calculateOutgoingFlow()<<" " << v->getInfo().getMaxDelivery() << "\n";
    }
*/
}

