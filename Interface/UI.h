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
    void evalute_resiliency();
    void doStuff();

    Graph<DeliverySite> getGraph() const;
private:
    Graph<DeliverySite> g;


};


#endif //PROJETO_UI_H
