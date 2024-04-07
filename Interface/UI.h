#ifndef PROJETO_UI_H
#define PROJETO_UI_H

#include "../Logic/LoadingFunctions.h"
#include "../Logic/stdafx.h"
#include "../Logic/Algorithms.h"

/**
 * @brief User Interface class for managing interaction with the water distribution system.
 */
 class UI {
public:
    /**
   * @brief Default constructor for the UI class.
   */
    UI();
     /**
     * @brief Displays the main menu and handles user input.
     */
    void menu_start();
     /**
      * @brief Clears the console screen.
      */
    static void clear_screen();
     /**
     * @brief Loads necessary data and settings for the UI.
     *
     * @param ui Reference to the UI object.
     */
    void loading_stuff(UI &ui);
     /**
    * @brief Validates user input within a specified range.
    *
    * @param op Reference to the input character to be validated.
    * @param lower_bound The lower bound of the valid range.
    * @param upper_bound The upper bound of the valid range.
    * @return True if input is valid, False otherwise.
    */
    static bool validate_input(char &op, const char lower_bound, const char upper_bound);
     /**
     * @brief Displays the main menu options.
     */
    void main_menu();
     /**
     * @brief Executes the max flow algorithm.
     */
    void max_flow();
     /**
     * @brief Checks demand for water distribution.
     */
    void check_demand();
     /**
    * @brief Checks heuristic for water distribution.
    */
    void check_heuristic();
     /**
     * @brief Returns to the previous menu.
     */
    void back_menu();
     /**
    * @brief Evaluates the resiliency of the system.
    */
    void evaluate_resiliency();
     /**
     * @brief Redistributes water without using the Max Flow algorithm.
     *
     * @param wr Water reservoir code.
     */
    void redistributeWithoutMaxFlow(std::string wr);
     /**
     * @brief Redistributes water without using the Max Flow algorithm (version 2).
     *
     * @param wr_code Reference to the water reservoir code.
     */
    void redistributeWithoutMaxFlowVersion2(std::string& wr_code);
     /**
   * @brief Calculates the incoming flow for a given vertex.
   *
   * @param v Pointer to the vertex.
   * @return The total incoming flow for the vertex.
   */
    int calculate_incoming_flow(Vertex<DeliverySite> *v);

     /**
     * @brief Getter function for accessing the graph.
     *
     * @return The graph representing the water distribution network.
     */
    Graph<DeliverySite> getGraph() const;
private:
    Graph<DeliverySite> g; /**< Graph representing the water distribution network. */
    std::unordered_map<std::string, int> codeToFlow; /**< Map of site codes to flow values. */
    int inital_max_flow; /**< Initial maximum flow value. */
};


#endif //PROJETO_UI_H
