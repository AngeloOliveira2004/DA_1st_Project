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
    //validate_input(op,'A','A');
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
            break;
            main_menu();
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
            break;
        case 'B':
            break;
        case 'C':
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

void UI::doStuff() {
    calculateMaxFlowInEntireNetwork(&g);

    heuristic(&g);

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
}

