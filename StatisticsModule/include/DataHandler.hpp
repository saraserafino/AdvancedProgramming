#ifndef DATAHANDLER_HPP
#define DATAHANDLER_HPP

#include <iostream>
#include <optional>
#include <variant>

typedef std::optional<std::variant<double,std::string>> csvType;

class CSVHandler {
public:
  // Declare StatOp as a friend class of CSVHandler in order to access its private members
  friend class StatOp; //old

  // Constructor for opening the input file
  CSVHandler(const std::string &input_path); //old

  const std::string get_input_file_path() const;
  const std::string get_input_file_name() const;

  // Destructor for both files
  ~CSVHandler() { //old
    this->input_file.close();
    this->output_file.close();
  }

protected:  
  const std::string input_path; //old
  const std::string input_file_name; //old
  // Shared pointer between the two classes
  const std::shared_ptr<CSVHandler> CSVfile; //old
};

#endif