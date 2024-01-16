#include "../StatisticsModule/include/StatOp.hpp"
#include "../StatisticsModule/include/DataHandler.hpp"
#include "../NumericalIntegrationModule/include/IntegrationMethods.hpp"
#include "../NumericalIntegrationModule/include/moduleCfunctions.hpp"
#include "muparserx/mpParser.h"
#include <iostream>
#include <vector>
#include <iomanip>

int main() {

    
    // File path
    const std::string input_file_path = "../data/player_data_03_22.csv";
    // Create shared pointer
    const std::shared_ptr<CSVHandler> CSVfile = std::make_shared<CSVHandler>(input_file_path);

    StatOp analysis(CSVfile);

    std::vector<std::string> headerNames = CSVfile->getHeader();

    // Create the output path outside the loop, otherwise it creates it for every cycle, overwriting the results
    CSVfile->create_output_path();

    return 0;
}