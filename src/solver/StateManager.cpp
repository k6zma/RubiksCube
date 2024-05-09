#include "solver/StateManager.h"
#include "solver/CubeSolver.h"

#include <iostream>

CubeInitState::CubeInitState(std::string input_file_name) {
    input_file = std::fopen(input_file_name.c_str(), "r");
}

std::vector<std::vector<std::vector<Color>>> CubeInitState::get_faces() {
    std::vector<std::vector<std::vector<Color>>> faces;
    for (int i = 0; i < 6; i++) {
        std::vector<std::vector<Color>> face;
        for (int j = 0; j < 3; j++) {
            std::vector<Color> row;
            for (int k = 0; k < 3; k++) {
                char color;
                std::fscanf(input_file, " %c", &color);
                row.push_back(static_cast<Color>(color));
            }
            face.push_back(row);
        }

        if (i == 0) {
            faces.insert(faces.begin(), face);
        } else {
            faces.push_back(face);
        }
    }
    return faces;
}
