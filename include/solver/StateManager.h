#ifndef RUBIKSCUBE_STATEMANAGER_H
#define RUBIKSCUBE_STATEMANAGER_H

#include <iostream>
#include <string>
#include "solver/CubeSolver.h"

class CubeInitState {
private:
    FILE *input_file;

public:
    CubeInitState(std::string input_file_name);
    std::vector<std::vector<std::vector<Color>>> get_faces();
};

#endif
