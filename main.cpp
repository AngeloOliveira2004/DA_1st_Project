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

    DeliverySite cityToTest = DeliverySite("C_5");

    calculateMaxFlow(&g , cityToTest);

    return 0;
}
