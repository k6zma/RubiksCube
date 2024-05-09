#include "solver/CLIParameters.h"

CLIParameters::CLIParameters(int argc, char** argv) {
    collect_cli_args(argc, argv);
    validate_input();
}

void CLIParameters::collect_cli_args(int argc, char** argv) {
    this->argc = argc;
    this->argv = argv;
}

void CLIParameters::validate_input() {
    if (argc != 2) {
        throw std::invalid_argument(
            "Invalid number of arguments. Please provide a valid input file.");
    }

    std::string first_arg = argv[1];
    if (first_arg.empty()) {
        throw std::invalid_argument(
            "Invalid input file. Please provide a valid input file.");
    }

    if (first_arg.empty() || first_arg.find("--input_filename=") != 0) {
        throw std::invalid_argument(
            "Invalid input file. Please provide a valid input file in the "
            "format --input_filename=filename.txt");
    }

    if (first_arg.substr(first_arg.find_last_of(".") + 1) != "txt") {
        throw std::invalid_argument(
            "Invalid file format. Please provide a .txt file.");
    }
}

std::string CLIParameters::collect_filename() {
    std::string first_arg = argv[1];
    std::string input_file = first_arg.substr(first_arg.find_last_of("=") + 1);

    return input_file;
}
