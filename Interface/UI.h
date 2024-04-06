#ifndef PROJETO_UI_H
#define PROJETO_UI_H

#include "../Logic/LoadingFunctions.h"
#include "../Logic/stdafx.h"
#include "../Logic/Algorithms.h"


class UI {
public:
    UI();
    void menu_start();
    static void clear_screen();
    void loading_stuff(UI &ui);
    static bool validate_input(char &op, const char lower_bound, const char upper_bound);
    void main_menu();
    void max_flow();
    void check_demand();
    void check_heuristic();
    void back_menu();
    void evaluate_resiliency();
    void redistributeWithoutMaxFlow(std::string wr);
    void redistributeWithoutMaxFlowVersion2(std::string& wr_code);
    int calculate_incoming_flow(Vertex<DeliverySite> *v);

    Graph<DeliverySite> getGraph() const;
private:
    Graph<DeliverySite> g;
    std::unordered_map<std::string, int> codeToFlow;
    int inital_max_flow;
};


#endif //PROJETO_UI_H
