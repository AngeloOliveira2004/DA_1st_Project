#include "DeliverySites.h"

// Constructor definition
// Constructor definition
/**
 * @brief Constructs a new DeliverySite object with complete information.
 * @param name The name of the delivery site.
 * @param municipality The municipality of the delivery site.
 * @param code The code of the delivery site.
 * @param id The identifier of the delivery site.
 * @param maxDelivery The maximum delivery of the delivery site.
 * @param demand The demand of the delivery site.
 * @param population The population of the delivery site.
 * @param nodeType The type of the delivery site.
 * @details Time Complexity: O(1)
 */
DeliverySite::DeliverySite(std::string name,
                           std::string municipality,
                           std::string code,
                           int id,
                           int maxDelivery,
                           int demand,
                           int population,
                           nodeTypes nodeType)
        : name(std::make_shared<std::string>(std::move(name))),
          municipality(std::make_shared<std::string>(std::move(municipality))),
          code(std::move(code)), id(id), maxDelivery(std::make_shared<int>(maxDelivery)), demand(std::make_shared<int>(demand)),
          population(std::make_shared<int>(population)) , type(nodeType){}

// Setter definitions
/**
 * @brief Sets the code of the delivery site.
 * @param code The code to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setCode(const std::string& code) {
    this->code = code;
}

/**
 * @brief Sets the identifier of the delivery site.
 * @param id The identifier to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setId(int id) {
    this->id = id;
}

/**
 * @brief Sets the municipality of the delivery site.
 * @param municipality The municipality to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setMunicipality(const std::string& municipality) {
    this->municipality = std::make_shared<std::string>(municipality);
}

// Setter for name
/**
 * @brief Sets the name of the delivery site.
 * @param name The name to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setName(const std::string& name) {
    this->name = std::make_shared<std::string>(name);
}

// Setter for maxDelivery
/**
 * @brief Sets the maximum delivery of the delivery site.
 * @param maxDelivery The maximum delivery to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setMaxDelivery(int maxDelivery) {
    this->maxDelivery = std::make_shared<int>(maxDelivery);
}

// Setter for demand
/**
 * @brief Sets the demand of the delivery site.
 * @param demand The demand to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setDemand(int demand) {
    this->demand = std::make_shared<int>(demand);
}

// Setter for population
/**
 * @brief Sets the population of the delivery site.
 * @param population The population to set.
 * @details Time Complexity: O(1)
 */
void DeliverySite::setPopulation(int population) {
    this->population = std::make_shared<int>(population);
}

// Getter definitions
/**
 * @brief Gets the name of the delivery site.
 * @return The name of the delivery site.
 * @details Time Complexity: O(1)
 */
std::string DeliverySite::getName() const {
    return *name;
}

/**
 * @brief Gets the municipality of the delivery site.
 * @return The municipality of the delivery site.
 * @details Time Complexity: O(1)
 */
std::string DeliverySite::getMunicipality() const {
    return *municipality;
}

/**
 * @brief Gets the code of the delivery site.
 * @return The code of the delivery site.
 * @details Time Complexity: O(1)
 */
std::string DeliverySite::getCode() const {
    return code;
}

/**
 * @brief Gets the identifier of the delivery site.
 * @return The identifier of the delivery site.
 * @details Time Complexity: O(1)
 */
[[maybe_unused]] int DeliverySite::getId() const {
    return id;
}

/**
 * @brief Gets the maximum delivery of the delivery site.
 * @return The maximum delivery of the delivery site.
 * @details Time Complexity: O(1)
 */
int DeliverySite::getMaxDelivery() const {
    return *maxDelivery;
}

/**
 * @brief Gets the demand of the delivery site.
 * @return The demand of the delivery site.
 * @details Time Complexity: O(1)
 */
int DeliverySite::getDemand() const {
    return *demand;
}

// Getter for population
/**
 * @brief Gets the population of the delivery site.
 * @return The population of the delivery site.
 * @details Time Complexity: O(1)
 */
int DeliverySite::getPopulation() const {
    return *population;
}

/**
 * @brief Prints information about the delivery site.
 * @details Time Complexity: O(1)
 */
void DeliverySite::printInfo() const {
    // Print delivery site information
    std::cout << "Name: " << *name << " ";
    std::cout << "ID: " << id << " ";
    std::cout << "Code: " << code << " ";
    std::cout << "Demand: " << *demand << " ";
    std::cout << "Population: " << *population << " ";
    std::cout << "Municipality: " << *municipality << " " ;
    std::cout << "Max Delivery: " << *maxDelivery << std::endl;
}
/**
 * @brief Gets the type of the delivery site.
 * @return The type of the delivery site.
 * @details Time Complexity: O(1)
 */
nodeTypes DeliverySite::getNodeType() const {
    return type;

}

DeliverySite::DeliverySite(std::string code)
        : code(std::move(code)),
          id(0), // Default value for id
          type(CITY), // Default value for type, adjust as needed
          name(nullptr), // Default value for name
          municipality(nullptr), // Default value for municipality
          maxDelivery(nullptr), // Default value for maxDelivery
          demand(nullptr), // Default value for demand
          population(nullptr) // Default value for population
{
}

/**
 * @brief Calculates the remaining delivery of the delivery site.
 * @param adj Adjacent edges of the delivery site.
 * @return The remaining delivery.
 * @details Time Complexity: O(n), where n is the number of adjacent edges.
 */
double DeliverySite::calculateRemainingDeliviry(const std::vector<Edge<DeliverySite> *>& adj) const {

    if(getNodeType() != WATER_RESERVOIR){
        return 0.0;
    }

    double maxDelivery_ = getMaxDelivery();

    double remainDelivery = 0;
    for(Edge<DeliverySite>* e : adj){
        remainDelivery += e->getFlow();
    }

    remainDelivery = maxDelivery_ - remainDelivery;

    return remainDelivery;
}

