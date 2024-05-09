#ifndef RUBIKSCUBE_PARSECLI_H
#define RUBIKSCUBE_PARSECLI_H

#include <string>

class CLIParameters {
private:
    int argc;
    char** argv;

    void collect_cli_args(int argc, char** argv);
    void validate_input();

public:
    CLIParameters(int argc, char** argv);
    std::string collect_filename();
};

#endif
