#ifndef STATOP_HPP_
#define STATOP_HPP_

#include "DataHandler.hpp" //old
#include <iostream>
#include <vector>
#include <string>

typedef std::optional<std::variant<double,std::string>> csvType; //old

namespace MODULEA {

class StatOp {
public:
    // Constructor
    StatOp(const std::shared_ptr<CSVHandler> CSVfile); //old

    double calculateMean(const std::vector<std::optional<std::variant<double, std::string>>> &data); //old
    std::variant<double, std::string> calculateMedian(const std::vector<std::optional<std::variant<double, std::string>>> &data); //old

    const std::vector<std::optional<std::variant<double, std::string>>>& getColumn(const std::string columnName) const; //old
    
    std::vector<std::vector<csvType>>::const_iterator begin(); //old
    std::vector<std::vector<csvType>>::const_iterator end(); //old

    // Destructor
    ~StatOp() {};
private:
    const std::shared_ptr<CSVHandler> CSVfile; //old
    const std::vector<std::vector<csvType>> data; //old
    const std::string targetColumn; //old
};
} // end of namespace

#endif // STATOP_HPP_