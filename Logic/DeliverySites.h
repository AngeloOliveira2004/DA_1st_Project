/**
 * @file DeliverySites.h
 * @brief Declaration of DeliverySite class.
 */

#ifndef PROJETO_DELIVERYSITES_H
#define PROJETO_DELIVERYSITES_H

#include "stdafx.h"
#include "optional"

enum nodeTypes{
    FIRE_STATION,
    CITY,
    WATER_RESERVOIR
};

/**
 * @class DeliverySite
 * @brief Represents a delivery site.
 */
class DeliverySite {
private:
    nodeTypes type; /**< Type of the delivery site. */
    // Mandatory
    int id; /**< Identifier of the delivery site. */
    std::string code; /**< Code of the delivery site. */

    // Optional
    std::shared_ptr<std::string> name; /**< Name of the delivery site. */
    std::shared_ptr<std::string> municipality; /**< Municipality of the delivery site. */
    std::shared_ptr<int> maxDelivery; /**< Maximum delivery of the delivery site. */
    std::shared_ptr<int> demand; /**< Demand of the delivery site. */
    std::shared_ptr<int> population; /**< Population of the delivery site. */

public:
    /**
     * @brief Constructs a new DeliverySite object with complete information.
     * @param name The name of the delivery site.
     * @param municipality The municipality of the delivery site.
     * @param code The code of the delivery site.
     * @param id The identifier of the delivery site.
     * @param maxDelivery The maximum delivery of the delivery site.
     * @param demand The demand of the delivery site.
     * @param population The population of the delivery site.
     * @param type The type of the delivery site.
     */
    DeliverySite(std::string  name,
                 std::string  municipality,
                 std::string  code,
                 int id,
                 int maxDelivery,
                 int demand,
                 int population,
                 nodeTypes type);
    /**
     * @brief Constructs a new DeliverySite object with minimal information.
     * @param code The code of the delivery site.
     */
    explicit DeliverySite(std::string  code);

    // Getters
    [[nodiscard]] std::string getName() const; /**< Get the name of the delivery site. */
    [[nodiscard]] std::string getMunicipality() const; /**< Get the municipality of the delivery site. */
    [[nodiscard]] std::string getCode() const; /**< Get the code of the delivery site. */
    [[nodiscard]] int getId() const; /**< Get the identifier of the delivery site. */
    [[nodiscard]] int getMaxDelivery() const; /**< Get the maximum delivery of the delivery site. */
    [[nodiscard]] int getDemand() const; /**< Get the demand of the delivery site. */
    [[nodiscard]] int getPopulation() const; /**< Get the population of the delivery site. */
    [[nodiscard]] nodeTypes getNodeType() const; /**< Get the type of the delivery site. */

    // Setters
    void setCode(const std::string& code); /**< Set the code of the delivery site. */
    void setMunicipality(const std::string& municipality); /**< Set the municipality of the delivery site. */
    void setName(const std::string& name); /**< Set the name of the delivery site. */
    void setId(int id); /**< Set the identifier of the delivery site. */
    void setMaxDelivery(int maxDelivery); /**< Set the maximum delivery of the delivery site. */
    void setDemand(int demand); /**< Set the demand of the delivery site. */
    void setPopulation(int population); /**< Set the population of the delivery site. */

    /**
     * @brief Prints information about the delivery site.
     * @details Time Complexity: O(1)
     */
    void printInfo() const;

    /**
     * @brief Calculates the remaining delivery of the delivery site.
     * @param adj Adjacent edges of the delivery site.
     * @return The remaining delivery.
     */
    double calculateRemainingDelivery(const std::vector<Edge<DeliverySite> *>& adj) const;

    /**
    * @brief Overloaded equality operator.
    * @param other The other DeliverySite to compare.
    * @return True if the delivery sites are equal, false otherwise.
    */
    bool operator==(const DeliverySite& other) const {
        return code == other.code;
    }
};

namespace std {
    template <>
    struct hash<DeliverySite> {
        /**
         * @brief Hash function for DeliverySite.
         * @param deliverySite The DeliverySite object.
         * @return The hash value.
         */
        size_t operator()(const DeliverySite& deliverySite) const {
            // Use hash of the city code for hashing
            return hash<string>{}(deliverySite.getCode());
        }
    };

    template<>
    struct equal_to<DeliverySite> {
        /**
         * @brief Equality comparison for DeliverySite.
         * @param deliverySite1 The first DeliverySite object.
         * @param deliverySite2 The second DeliverySite object.
         * @return True if equal, false otherwise.
         */
        bool operator()(const DeliverySite& deliverySite1, const DeliverySite& deliverySite2) const {
            // Compare only the city codes for equality
            return deliverySite1.getCode() == deliverySite2.getCode();
        }
    };
}

#endif //PROJETO_DELIVERYSITES_H
