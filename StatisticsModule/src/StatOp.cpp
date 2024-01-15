#include "../include/StatOp.hpp"
#include "../include/DataHandler.hpp"
#include <iostream>
#include <optional> // for std::optional
#include <variant> // for std::variant
//#include "boost/optional.hpp"
//#include "boost/variant.hpp"
//#include "boost/accumulators/accumulators.hpp"
//#include "boost/accumulators/statistics.hpp"

namespace MODULEA {

    // Constructor
    StatOp::StatOp(const std::shared_ptr<CSVHandler> CSVfile) : CSVfile(CSVfile), data(CSVfile->readData()) {};

    std::vector<std::vector<csvType>>::const_iterator StatOp::begin() {
        return data.begin();
    }

    std::vector<std::vector<csvType>>::const_iterator StatOp::end() {
        return data.end();
    }

} // end of namespace