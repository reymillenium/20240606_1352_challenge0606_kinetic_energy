/**
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                       *
 *       Created by: Reinier Garcia Ramos                *
 *       reymillenium@gmail.com                          *
 *                                                       *
 *       https://www.linkedin.com/in/reiniergarcia       *
 *       https://github.com/reymillenium                 *
 *       https://www.reiniergarcia.dev                   *
 *                                                       *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 **/

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <sstream>

template<typename T>
auto get_value(const std::string &message) -> T;

std::string humanize_unsigned_integer(unsigned long long int);

std::string humanize_unsigned_double(long double, int = 2);

void scold_user_if_invalid_input(long double, double);

bool is_invalid(long double, double);

long double kinetic_energy(long double, long double);

int main() {
    bool keep_calculating = false;

    do {
        long double mass;
        long double velocity;

        do {
            mass = get_value<long double>("Enter the mass (Kg): ");
            scold_user_if_invalid_input(mass, 0);
        } while (is_invalid(mass, 0));

        do {
            velocity = get_value<long double>("Enter the velocity (m/s): ");
            scold_user_if_invalid_input(velocity, 0);
        } while (is_invalid(velocity, 0));

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "The Kinetic Energy (KE) of the object is equal to " << humanize_unsigned_double(kinetic_energy(mass, velocity)) << " joules." << std::endl;

        auto keep_calculating_str = get_value<std::string>("Would you like to keep calculating the Kinetic Energy (y/n)? ");
        keep_calculating = keep_calculating_str != "n" && keep_calculating_str != "N";
    } while (keep_calculating);

    return 0;
}

template<typename T>
auto get_value(const std::string &message) -> T {
    std::cout << message;
    T value;
    std::cin >> value;
    std::cin.ignore();
    return value;
}

std::string humanize_unsigned_integer(const unsigned long long int integer_value) {
    std::string integer_as_string = std::to_string(integer_value);
    // We insert commas into the string every three digits, fromm right to left.
    for (int j = integer_as_string.length() - 3; j > 0; j -= 3) {
        integer_as_string.insert(j, ",");
    }
    return integer_as_string;
}

std::string humanize_unsigned_double(const long double double_value, const int precision) {
    const auto integer_value = static_cast<unsigned long long int>(double_value);
    const long double decimals = double_value - integer_value;
    // Extracts into a string the decimal part, rounded to two significant digits
    std::stringstream stream;
    // Places the decimals into the stream, rounded to two significant digits (by default)
    stream << std::fixed << std::setprecision(precision) << decimals;
    // Extracts the decimals from the stream, as a string, still rounded to two significant digits (by default)
    const std::string decimals_as_string = stream.str(); // It still includeds the zero & the dot. Ex: 0.34 (the dot must be removed next)
    return humanize_unsigned_integer(integer_value) + decimals_as_string.substr(1, precision + 1);
}

bool is_invalid(const long double value, const double min_value) {
    return value < min_value;
}

void scold_user_if_invalid_input(const long double value, const double min_value) {
    if (is_invalid(value, min_value)) std::cout << "You must type a number greater or equal than " << min_value << ". Try again!" << std::endl;
}

long double kinetic_energy(const long double mass, const long double velocity) {
    return 0.5 * mass * pow(velocity, 2);
};
