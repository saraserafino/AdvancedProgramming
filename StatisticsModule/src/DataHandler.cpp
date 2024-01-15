#include "../include/DataHandler.hpp"

// Constructor
CSVHandler::CSVHandler(const std::string &input_path) : input_path(input_path), input_file_name(std::filesystem::path(input_path).stem().string()) {
  // Check if the file extension is .csv
  std::string extension = std::filesystem::path(this->input_path).extension();
  if (extension != ".csv") {
    throw std::invalid_argument("Invalid file type. Supported type: csv");
  }

  // Open input file
  input_file.open(this->input_path, std::ifstream::in);
  // Throw an error if it fails
  if (!input_file.is_open()) {
    throw std::runtime_error("Could not open the input file: " + this->input_path);
  }
};

const std::string CSVHandler::get_input_file_path() const {
    return input_path;
};

const std::string CSVHandler::get_input_file_name() const {
    return input_file_name;
};