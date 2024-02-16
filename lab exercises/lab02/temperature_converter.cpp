#include <iostream>
#include <string>

int main()
{
    double temperature;
    std::string unit;

    std::cout << "Enter a temperature: ";
    std::cin >> temperature;
    std::cout << "Specify if the unit of temperature is Celsius (C) or Fahrenheit (F): ";
    std::cin >> unit;

    // perform the conversion based on the provided unit
    double temperature_converted;
    if (unit == "C" || unit == "celsius" || unit == "Celsius") {
        temperature_converted = (9.0 / 5.0) * temperature + 32;
        std::cout << "The temperature " << temperature << "°C is " << temperature_converted << "°F" << std::endl;

    }
    else if (unit == "F" || unit == "fahrenheit" || unit == "Fahrenheit") {
        temperature_converted = (5.0 / 9.0 ) * (temperature - 32);
        std::cout << "The temperature " << temperature << "°F is " << temperature_converted << "°C" << std::endl;

    }
    else {
        std::cout << "You typed neither Celsius nor Fahrenheit." << std::endl;
        return 1; // we exit due to the error
    }
    return 0;
}