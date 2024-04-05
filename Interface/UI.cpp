#include "UI.h"
#include "../Logic/Logic.h"
#include <thread>
#include <chrono>
#include <iomanip>

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

    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");
    DeliverySite dummy = DeliverySite("Empty");
    createSuperSourceSink(&g,supersource,supersink);
    inital_max_flow = edmondsKarp(&g,supersource,supersink, dummy);
    removeSuperSourceSink(&g,supersource,supersink);

    for(Vertex<DeliverySite>* v: g.getVertexSet()){

        int sumFlow = calculate_incoming_flow(v);
        v->setIncomingFlow(sumFlow);

        if(v->getInfo().getNodeType() == CITY){
            codeToFlow[v->getInfo().getCode()] = sumFlow;
        }
    }


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
             << "E. Exit the program" << std::endl
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
            evaluate_resiliency();
            break;
        case 'E':
           std::cout << "Thanks for using our water management tool!" <<std::endl << "\n"
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
            DeliverySite dummy = DeliverySite("Empty");
            createSuperSourceSink(&g,supersource,supersink);
            double max_flow = edmondsKarp(&g,supersource,supersink, dummy);
            removeSuperSourceSink(&g,supersource,supersink);

            switch (op1) {
                case 'A': {
                    std::cout << "The max flow for the entire network is: " << max_flow << std::endl;
                    break;
                }
                case 'B': {
                    std::cout << std::left << std::setw(20) << "City Name"
                              << std::setw(20) << "City Code"
                              << std::setw(20) << "Flow" << std::endl;

                    for(auto v : g.getVertexSet()){
                        if(v->getInfo().getNodeType() == CITY){
                            std::cout << std::left << std::setw(20) << v->getInfo().getName()
                                      << std::setw(20) << v->getInfo().getCode()
                                      << std::setw(20) << v->calculateIncomingFlow() << std::endl;
                        }

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
                    std::cout << "Error: City with code '" << code << "' not found. Please try again." << std::endl;
                } else {
                    foundVertex = true;
                }
            }
            DeliverySite sink = DeliverySite(code);

            createSuperSource(&g,supersource);
            DeliverySite dummy = DeliverySite("Empty");
            double max_flow = edmondsKarp(&g,supersource,sink,dummy);
            removeSuperSource(&g,supersource);

            std::cout << "The max flow for the city " << code << " is: " << max_flow << std::endl;

            break;
        }
    }
    back_menu();
};


void UI::check_demand(){

    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");
    DeliverySite dummy = DeliverySite("Empty");
    createSuperSourceSink(&g,supersource,supersink);
    edmondsKarp(&g,supersource,supersink,dummy);
    removeSuperSourceSink(&g,supersource,supersink);

    std::cout << std::left << std::left << std::setw(20) << "City Name"
              << std::setw(20) << "City Code"
              << std::setw(20) << "Demand"
              << std::setw(20) << "Flow"
              << std::setw(20) << "Defecit" << std::endl;


    std::cout << "The following cities don't receive enough water : " << std::endl;
    for(Vertex<DeliverySite>* ds: g.getVertexSet()){
        int sumFlow = calculate_incoming_flow(ds);
        ds->setIncomingFlow(sumFlow);

        int difference = ds->getInfo().getDemand() - ds->getIncomingFlow();

        if(ds->getInfo().getNodeType() == CITY && difference > 0 ){
            std::cout << std::left << std::setw(20) << ds->getInfo().getName()
                      << std::setw(20) << ds->getInfo().getCode()
                      << std::setw(20) << ds->getInfo().getDemand()
                      << std::setw(20) << ds->getIncomingFlow()
                      << std::setw(20) << abs(difference) << std::endl;
        }
    }
    std::cout << std::endl;
    back_menu();
}

void UI::check_heuristic(){
    DeliverySite supersource = DeliverySite("SuperSource");
    DeliverySite supersink = DeliverySite("SuperSink");
    DeliverySite dummy = DeliverySite("Empty");

    createSuperSourceSink(&g,supersource,supersink);
    edmondsKarp(&g,supersource,supersink,dummy);
    removeSuperSourceSink(&g,supersource,supersink);

    heuristic(&g);
    std::cout << std::endl;
    back_menu();
}

void UI::back_menu(){
    char op;
    std::cout << "Press A to go back to the menu: ";
    validate_input(op,'A','A');
    main_menu();
}

void UI::evaluate_resiliency() {
    char op;
    std:: cout << "How would you like to evaluate the resiliency?" << std::endl
               << "A. Water Reservoir out of comission" << std::endl
               << "B. Pumping Station out of comission /in maintenance" << std::endl
               << "C. Pipeline/s out of comission / ruptured" << std::endl
               << "Insert your choice:" << std::endl;
    validate_input(op, 'A', 'C');
    switch(op){
        case 'A':{
            std::string code;
            bool foundVertex = false;

            while (!foundVertex) {
                std::cout << "Insert the code of the water reservoir: " << std::endl;
                std::cin >> code;

                DeliverySite water_reservoir = DeliverySite(code);

                if (!g.findVertex(water_reservoir)) {
                    std::cout << "Error: Water Reservoir with code '" << code << "' not found. Please try again." << std::endl;
                } else {
                    foundVertex = true;
                }
            }

            std::cout << "Would you like to try the balancing algorithm without the whole network?" << std::endl
                      << "A. Yes" << std::endl
                      << "B. No" << std::endl
                      << "Insert your choice:" << std::endl;
            validate_input(op, 'A', 'B');

            switch(op){
                case 'A':
                    redistributeWithoutMaxFlow(code,true);
                    break;
                case 'B':
                    redistributeWithoutMaxFlow(code,false);
                    break;

            }
            break;
        }
        case 'B':{
            std::string code;
            bool foundVertex = false;

            while (!foundVertex) {
                std::cout << "Insert the code of the pumping station: " << std::endl;
                std::cin >> code;

                DeliverySite pump_station = DeliverySite(code);

                if (!g.findVertex(pump_station)) {
                    std::cout << "Error: Pumping Station with code '" << code << "' not found. Please try again." << std::endl;
                } else {
                    foundVertex = true;
                }
            }

            DeliverySite supersource = DeliverySite("SuperSource");
            DeliverySite supersink = DeliverySite("SuperSink");
            DeliverySite pump_station = DeliverySite(code);
            createSuperSourceSink(&g,supersource,supersink);
            double max_flow = edmondsKarp(&g,supersource,supersink,pump_station);
            removeSuperSourceSink(&g,supersource,supersink);

            std::cout << "The max flow of the network removing " << code << " is: " << max_flow << std::endl;

            std::cout << std::left << std::setw(20) << "City Name"
                      << std::setw(20) << "City Code"
                      << std::setw(20) << "Required Units"
                      << std::setw(20) << "New Flow"
                      << std::setw(20) << "Old Flow" << std::endl;

            for(Vertex<DeliverySite>* v: g.getVertexSet()){
                if(v->getInfo().getNodeType() == CITY){

                    int sumFlow = calculate_incoming_flow(v);

                    v->setIncomingFlow(sumFlow);
                    int result = v->getIncomingFlow() - codeToFlow[v->getInfo().getCode()];
                    if(result < 0){
                        std::cout << std::left << std::setw(20) << v->getInfo().getName()
                                  << std::setw(20) << v->getInfo().getCode()
                                  << std::setw(20) << abs(result)
                                  << std::setw(20) << v->getIncomingFlow()
                                  << std::setw(20) << codeToFlow[v->getInfo().getCode()] << std::endl;
                    }
                }
            }

            break;
        }
        case 'C':{
            std::string code1;
            std::string code2;
            bool foundEdge = false;
            std::vector<Edge<DeliverySite>*> pointerVector;

            while (!foundEdge) {
                Edge<DeliverySite>* edgeFound = nullptr;
                std::cout << "Insert the code of the first delivery site: " << std::endl;
                std::cin >> code1;

                std::cout << "Insert the code of the second delivery site: " << std::endl;
                std::cin >> code2;

                DeliverySite ds1 = DeliverySite(code1);

                DeliverySite ds2 = DeliverySite(code2);

                if (!g.findVertex(ds1) && !g.findVertex(ds2)) {
                    std::cout << "Error: Delivery Sites not found. Please try again." << std::endl;
                }

                for(auto edge: g.getEdges()){
                    if(edge->getOrig()->getInfo().getCode() == ds1.getCode() && edge->getDest()->getInfo().getCode() == ds2.getCode()){
                        foundEdge = true;
                        edgeFound = edge;
                        break;
                    }
                }

                if(!foundEdge){
                    std::cout << "Error: Pipe not found. Please try again." << std::endl;
                }else{
                    if(edgeFound->getReverse() != nullptr){
                        pointerVector.push_back(edgeFound->getReverse());
                    }
                    pointerVector.push_back(edgeFound);
                    std::cout << "Do you want to add another pipeline to the out of comission/ruptured list ?" << std::endl
                              << "A. Yes" << std::endl
                              << "B. No" << std::endl;
                    char op1;
                    validate_input(op1,'A','B');
                    if(op1 == 'A'){
                        foundEdge = false;
                    }
                }
            }

            DeliverySite supersource = DeliverySite("SuperSource");
            DeliverySite supersink = DeliverySite("SuperSink");
            createSuperSourceSink(&g,supersource,supersink);
            double max_flow = edmondsKarpPipe(&g,supersource,supersink,pointerVector);
            removeSuperSourceSink(&g,supersource,supersink);

            std::cout << "The max flow of the network is " << max_flow << " removing the pipes: " << std::endl;
            for(auto pipe: pointerVector){
                std::cout << pipe->getOrig()->getInfo().getCode() << "-" << pipe->getDest()->getInfo().getCode() << std::endl;
            }
            std::cout << std::endl;

            std::cout << std::left << std::setw(20) << "City Name"
                      << std::setw(20) << "City Code"
                      << std::setw(20) << "Required Units"
                      << std::setw(20) << "New Flow"
                      << std::setw(20) << "Old Flow" << std::endl;


            for(Vertex<DeliverySite>* v: g.getVertexSet()){
                if(v->getInfo().getNodeType() == CITY){

                    int sumFlow = calculate_incoming_flow(v);

                    v->setIncomingFlow(sumFlow);
                    int result = v->getIncomingFlow() - codeToFlow[v->getInfo().getCode()];
                    if(result < 0){
                        std::cout << std::left << std::setw(20) << v->getInfo().getName()
                                  << std::setw(20) << v->getInfo().getCode()
                                  << std::setw(20) << abs(result)
                                  << std::setw(20) << v->getIncomingFlow()
                                  << std::setw(20) << codeToFlow[v->getInfo().getCode()] << std::endl;
                    }
                }
            }
            std::cout << std::endl;
        }

        break;
    }

    back_menu();
}



void UI::redistributeWithoutMaxFlow(std::string wr,bool is_algo) {

    DeliverySite reservoir_ds = DeliverySite(wr);

    if(is_algo){
        redistributeWithoutMaxFlowAlgorithm(&g, g.findVertex(reservoir_ds));
    }else{
        DeliverySite supersource = DeliverySite("SuperSource");
        DeliverySite supersink = DeliverySite("SuperSink");
        DeliverySite water_reservoir = DeliverySite(wr);
        createSuperSourceSink(&g,supersource,supersink);
        double max_flow = edmondsKarp(&g,supersource,supersink,water_reservoir);
        removeSuperSourceSink(&g,supersource,supersink);

        std::cout << "The max flow of the network removing " << wr << " is: " << max_flow << std::endl;

    }

    std::cout << std::left << std::setw(20) << "City Name"
              << std::setw(20) << "City Code"
              << std::setw(20) << "Required Units"
              << std::setw(20) << "New Flow"
              << std::setw(20) << "Old Flow" << std::endl;

    for (Vertex<DeliverySite> *v: g.getVertexSet()) {
        if (v->getInfo().getNodeType() == CITY) {
            int sumFlow = calculate_incoming_flow(v);

            v->setIncomingFlow(sumFlow);

            int result = v->getIncomingFlow() - codeToFlow[v->getInfo().getCode()];
            if (result < 0) {
                std::cout << std::left << std::setw(20) << v->getInfo().getName()
                          << std::setw(20) << v->getInfo().getCode()
                          << std::setw(20) << abs(result)
                          << std::setw(20) << v->getIncomingFlow()
                          << std::setw(20) << codeToFlow[v->getInfo().getCode()] << std::endl;
            }
        }
    }
}


int UI::calculate_incoming_flow(Vertex<DeliverySite>* v){
    int sumFlow = 0;
    for(Edge<DeliverySite>* p : v->getIncoming()){
        if(!p->isSelected()) {
            sumFlow += p->getFlow();
        }
    }
    return sumFlow;
}
