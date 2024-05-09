#include "solver/CubeSolver.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

RubiksCube::RubiksCube(std::vector<std::vector<std::vector<Color>>> faces) {
    // Initialize the faces
    green_face = faces[0];
    orange_face = faces[1];
    red_face = faces[2];
    blue_face = faces[3];
    white_face = faces[4];
    yellow_face = faces[5];

    validate_init_faces();
}

int RubiksCube::color_to_index(Color color) {
    // Convert color to index
    switch (color) {
        case Green:
            return 0;
        case Orange:
            return 1;
        case Red:
            return 2;
        case Blue:
            return 3;
        case White:
            return 4;
        case Yellow:
            return 5;
        default:
            throw std::runtime_error("Invalid color");
    }
}

void RubiksCube::validate_init_faces() {
    /* Input validation:
     1. Each color must appear exactly 9 times
     2. Each face must have the correct center color
     3. Each face must have the correct colors (Green, Orange, Red, Blue, White,
     Yellow)
     */

    // Check if the center colors are correct
    if (green_face[1][1] != Green) {
        std::cout << green_face[1][1] << "\n";
        throw std::runtime_error("Green face center is not green");
    }
    if (orange_face[1][1] != Orange) {
        throw std::runtime_error("Orange face center is not orange");
    }
    if (red_face[1][1] != Red) {
        throw std::runtime_error("Red face center is not red");
    }
    if (blue_face[1][1] != Blue) {
        throw std::runtime_error("Blue face center is not blue");
    }
    if (white_face[1][1] != White) {
        throw std::runtime_error("White face center is not white");
    }
    if (yellow_face[1][1] != Yellow) {
        throw std::runtime_error("Yellow face center is not yellow");
    }

    // Check if each color appears exactly 9 times
    int color_counts[6] = {0, 0, 0, 0, 0, 0};
    std::vector<std::vector<std::vector<Color>>> faces = {
        green_face, orange_face, red_face, blue_face, white_face, yellow_face};
    for (auto &face : faces) {
        for (auto &row : face) {
            for (auto &color : row) {
                if (color != Green && color != Orange && color != Red &&
                    color != Blue && color != White && color != Yellow) {
                    throw std::runtime_error("Invalid color on face");
                }

                color_counts[color_to_index(color)]++;
            }
        }
    }
    if (color_counts[0] != 9) {
        std::cout << color_counts[0] << "\n";
        throw std::runtime_error("Green face has incorrect number of colors");
    }
    if (color_counts[1] != 9) {
        throw std::runtime_error("Orange face has incorrect number of colors");
    }
    if (color_counts[2] != 9) {
        throw std::runtime_error("Red face has incorrect number of colors");
    }
    if (color_counts[3] != 9) {
        throw std::runtime_error("Blue face has incorrect number of colors");
    }
    if (color_counts[4] != 9) {
        throw std::runtime_error("White face has incorrect number of colors");
    }
    if (color_counts[5] != 9) {
        throw std::runtime_error("Yellow face has incorrect number of colors");
    }
}

// Front face rotations
void RubiksCube::rotate_front_face() {
    /* Rotate the front face clockwise
     1. Rotate the front face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_green_face = green_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            green_face[i][j] = temp_green_face[2 - j][i];
        }
    }

    std::vector<Color> temp_bottom_white = {white_face[2][0], white_face[2][1],
                                            white_face[2][2]};
    std::vector<Color> temp_left_red = {red_face[2][0], red_face[1][0],
                                        red_face[0][0]};
    std::vector<Color> temp_top_yellow = {yellow_face[0][0], yellow_face[0][1],
                                          yellow_face[0][2]};
    std::vector<Color> temp_right_orange = {
        orange_face[2][2], orange_face[1][2], orange_face[0][2]};

    for (int i = 0; i < 3; ++i) {
        white_face[2][i] = temp_right_orange[i];
        red_face[i][0] = temp_bottom_white[i];
        yellow_face[0][i] = temp_left_red[i];
        orange_face[i][2] = temp_top_yellow[i];
    }
}

void RubiksCube::rotate_front_reverse_face() {
    /* Rotate the front face counterclockwise
     1. Rotate the front face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_green_face = green_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            green_face[i][j] = temp_green_face[j][2 - i];
        }
    }

    std::vector<Color> temp_bottom_white = {white_face[2][0], white_face[2][1],
                                            white_face[2][2]};
    std::vector<Color> temp_left_red = {red_face[2][0], red_face[1][0],
                                        red_face[0][0]};
    std::vector<Color> temp_top_yellow = {yellow_face[0][0], yellow_face[0][1],
                                          yellow_face[0][2]};
    std::vector<Color> temp_right_orange = {
        orange_face[2][2], orange_face[1][2], orange_face[0][2]};

    for (int i = 0; i < 3; ++i) {
        white_face[2][i] = temp_left_red[2 - i];
        red_face[i][0] = temp_top_yellow[2 - i];
        yellow_face[0][i] = temp_right_orange[2 - i];
        orange_face[i][2] = temp_bottom_white[2 - i];
    }
}

void RubiksCube::rotate_front_face_twice() {
    // Rotate the front face twice
    rotate_front_face();
    rotate_front_face();
}

// Back face rotations
void RubiksCube::rotate_back_face() {
    /* Rotate the back face clockwise
     1. Rotate the back face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_blue_face = blue_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            blue_face[i][j] = temp_blue_face[2 - j][i];
        }
    }

    std::vector<Color> temp_top_white = {white_face[0][2], white_face[0][1],
                                         white_face[0][0]};
    std::vector<Color> temp_right_red = {red_face[0][2], red_face[1][2],
                                         red_face[2][2]};
    std::vector<Color> temp_bottom_yellow = {
        yellow_face[2][2], yellow_face[2][1], yellow_face[2][0]};
    std::vector<Color> temp_left_orange = {orange_face[0][0], orange_face[1][0],
                                           orange_face[2][0]};

    for (int i = 0; i < 3; ++i) {
        white_face[0][i] = temp_right_red[i];
        red_face[i][2] = temp_bottom_yellow[i];
        yellow_face[2][i] = temp_left_orange[i];
        orange_face[i][0] = temp_top_white[i];
    }
}

void RubiksCube::rotate_back_reverse_face() {
    /* Rotate the back face counterclockwise
     1. Rotate the back face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_blue_face = blue_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            blue_face[i][j] = temp_blue_face[j][2 - i];
        }
    }

    std::vector<Color> temp_top_white = {white_face[0][2], white_face[0][1],
                                         white_face[0][0]};
    std::vector<Color> temp_right_red = {red_face[0][2], red_face[1][2],
                                         red_face[2][2]};
    std::vector<Color> temp_bottom_yellow = {
        yellow_face[2][2], yellow_face[2][1], yellow_face[2][0]};
    std::vector<Color> temp_left_orange = {orange_face[0][0], orange_face[1][0],
                                           orange_face[2][0]};

    for (int i = 0; i < 3; ++i) {
        white_face[0][i] = temp_left_orange[2 - i];
        red_face[i][2] = temp_top_white[2 - i];
        yellow_face[2][i] = temp_right_red[2 - i];
        orange_face[i][0] = temp_bottom_yellow[2 - i];
    }
}

void RubiksCube::rotate_back_face_twice() {
    // Rotate the back face twice
    rotate_back_face();
    rotate_back_face();
}

// Left face rotations
void RubiksCube::rotate_left_face() {
    /* Rotate the left face clockwise
     1. Rotate the left face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_orange_face = orange_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            orange_face[i][j] = temp_orange_face[2 - j][i];
        }
    }

    std::vector<Color> temp_left_white = {white_face[0][0], white_face[1][0],
                                          white_face[2][0]};
    std::vector<Color> temp_right_blue = {blue_face[2][2], blue_face[1][2],
                                          blue_face[0][2]};
    std::vector<Color> temp_left_yellow = {yellow_face[2][0], yellow_face[1][0],
                                           yellow_face[0][0]};
    std::vector<Color> temp_left_green = {green_face[0][0], green_face[1][0],
                                          green_face[2][0]};

    for (int i = 0; i < 3; ++i) {
        white_face[i][0] = temp_right_blue[i];
        blue_face[i][2] = temp_left_yellow[i];
        yellow_face[i][0] = temp_left_green[i];
        green_face[i][0] = temp_left_white[i];
    }
}

void RubiksCube::rotate_left_reverse_face() {
    /* Rotate the left face counterclockwise
     1. Rotate the left face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_orange_face = orange_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            orange_face[i][j] = temp_orange_face[j][2 - i];
        }
    }

    std::vector<Color> temp_left_white = {white_face[2][0], white_face[1][0],
                                          white_face[0][0]};
    std::vector<Color> temp_right_blue = {blue_face[2][2], blue_face[1][2],
                                          blue_face[0][2]};
    std::vector<Color> temp_left_yellow = {yellow_face[0][0], yellow_face[1][0],
                                           yellow_face[2][0]};
    std::vector<Color> temp_left_green = {green_face[0][0], green_face[1][0],
                                          green_face[2][0]};

    for (int i = 0; i < 3; ++i) {
        white_face[i][0] = temp_left_green[i];
        blue_face[i][2] = temp_left_white[i];
        yellow_face[i][0] = temp_right_blue[i];
        green_face[i][0] = temp_left_yellow[i];
    }
}

void RubiksCube::rotate_left_face_twice() {
    // Rotate the left face twice
    rotate_left_face();
    rotate_left_face();
}

// Right face rotations
void RubiksCube::rotate_right_face() {
    /* Rotate the right face clockwise
     1. Rotate the right face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_red_face = red_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            red_face[i][j] = temp_red_face[2 - j][i];
        }
    }

    std::vector<Color> temp_right_white = {white_face[2][2], white_face[1][2],
                                           white_face[0][2]};
    std::vector<Color> temp_left_blue = {blue_face[2][0], blue_face[1][0],
                                         blue_face[0][0]};
    std::vector<Color> temp_right_yellow = {
        yellow_face[0][2], yellow_face[1][2], yellow_face[2][2]};
    std::vector<Color> temp_right_green = {green_face[0][2], green_face[1][2],
                                           green_face[2][2]};

    for (int i = 0; i < 3; ++i) {
        white_face[i][2] = temp_right_green[i];
        blue_face[i][0] = temp_right_white[i];
        yellow_face[i][2] = temp_left_blue[i];
        green_face[i][2] = temp_right_yellow[i];
    }
}

void RubiksCube::rotate_right_reverse_face() {
    /* Rotate the right face counterclockwise
     1. Rotate the right face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_red_face = red_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            red_face[i][j] = temp_red_face[j][2 - i];
        }
    }

    std::vector<Color> temp_right_white = {white_face[0][2], white_face[1][2],
                                           white_face[2][2]};
    std::vector<Color> temp_left_blue = {blue_face[2][0], blue_face[1][0],
                                         blue_face[0][0]};
    std::vector<Color> temp_right_yellow = {
        yellow_face[2][2], yellow_face[1][2], yellow_face[0][2]};
    std::vector<Color> temp_right_green = {green_face[0][2], green_face[1][2],
                                           green_face[2][2]};

    for (int i = 0; i < 3; ++i) {
        white_face[i][2] = temp_left_blue[i];
        blue_face[i][0] = temp_right_yellow[i];
        yellow_face[i][2] = temp_right_green[i];
        green_face[i][2] = temp_right_white[i];
    }
}

void RubiksCube::rotate_right_face_twice() {
    // Rotate the right face twice
    rotate_right_face();
    rotate_right_face();
}

// Up face rotations
void RubiksCube::rotate_up_face() {
    /* Rotate the up face clockwise
     1. Rotate the up face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_white_face = white_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            white_face[i][j] = temp_white_face[2 - j][i];
        }
    }

    std::vector<Color> temp_top_green = {green_face[0][0], green_face[0][1],
                                         green_face[0][2]};
    std::vector<Color> temp_top_red = {red_face[0][0], red_face[0][1],
                                       red_face[0][2]};
    std::vector<Color> temp_top_blue = {blue_face[0][0], blue_face[0][1],
                                        blue_face[0][2]};
    std::vector<Color> temp_top_orange = {orange_face[0][0], orange_face[0][1],
                                          orange_face[0][2]};

    for (int i = 0; i < 3; ++i) {
        green_face[0][i] = temp_top_red[i];
        red_face[0][i] = temp_top_blue[i];
        blue_face[0][i] = temp_top_orange[i];
        orange_face[0][i] = temp_top_green[i];
    }
}

void RubiksCube::rotate_up_reverse_face() {
    /* Rotate the up face counterclockwise
     1. Rotate the up face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_white_face = white_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            white_face[i][j] = temp_white_face[j][2 - i];
        }
    }

    std::vector<Color> temp_top_green = {green_face[0][0], green_face[0][1],
                                         green_face[0][2]};
    std::vector<Color> temp_top_red = {red_face[0][0], red_face[0][1],
                                       red_face[0][2]};
    std::vector<Color> temp_top_blue = {blue_face[0][0], blue_face[0][1],
                                        blue_face[0][2]};
    std::vector<Color> temp_top_orange = {orange_face[0][0], orange_face[0][1],
                                          orange_face[0][2]};

    for (int i = 0; i < 3; ++i) {
        green_face[0][i] = temp_top_orange[i];
        red_face[0][i] = temp_top_green[i];
        blue_face[0][i] = temp_top_red[i];
        orange_face[0][i] = temp_top_blue[i];
    }
}

void RubiksCube::rotate_up_face_twice() {
    // Rotate the up face twice
    rotate_up_face();
    rotate_up_face();
}

// Down face rotations
void RubiksCube::rotate_down_face() {
    /* Rotate the down face clockwise
     1. Rotate the down face clockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_yellow_face = yellow_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            yellow_face[i][j] = temp_yellow_face[2 - j][i];
        }
    }

    std::vector<Color> temp_bottom_green = {green_face[2][0], green_face[2][1],
                                            green_face[2][2]};
    std::vector<Color> temp_bottom_red = {red_face[2][0], red_face[2][1],
                                          red_face[2][2]};
    std::vector<Color> temp_bottom_blue = {blue_face[2][0], blue_face[2][1],
                                           blue_face[2][2]};
    std::vector<Color> temp_bottom_orange = {
        orange_face[2][0], orange_face[2][1], orange_face[2][2]};

    for (int i = 0; i < 3; ++i) {
        green_face[2][i] = temp_bottom_orange[i];
        red_face[2][i] = temp_bottom_green[i];
        blue_face[2][i] = temp_bottom_red[i];
        orange_face[2][i] = temp_bottom_blue[i];
    }
}

void RubiksCube::rotate_down_reverse_face() {
    /* Rotate the down face counterclockwise
     1. Rotate the down face counterclockwise
     2. Update the adjacent faces
    */

    std::vector<std::vector<Color>> temp_yellow_face = yellow_face;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            yellow_face[i][j] = temp_yellow_face[j][2 - i];
        }
    }

    std::vector<Color> temp_bottom_green = {green_face[2][0], green_face[2][1],
                                            green_face[2][2]};
    std::vector<Color> temp_bottom_red = {red_face[2][0], red_face[2][1],
                                          red_face[2][2]};
    std::vector<Color> temp_bottom_blue = {blue_face[2][0], blue_face[2][1],
                                           blue_face[2][2]};
    std::vector<Color> temp_bottom_orange = {
        orange_face[2][0], orange_face[2][1], orange_face[2][2]};

    for (int i = 0; i < 3; ++i) {
        green_face[2][i] = temp_bottom_red[i];
        red_face[2][i] = temp_bottom_blue[i];
        blue_face[2][i] = temp_bottom_orange[i];
        orange_face[2][i] = temp_bottom_green[i];
    }
}

void RubiksCube::rotate_down_face_twice() {
    // Rotate the down face twice
    rotate_down_face();
    rotate_down_face();
}

// Validators
bool RubiksCube::check_first_part_of_white_cross() {
    /* Check if the first part of the white cross is solved
     1. Check if the white cross has been solved (white edge pieces on the white
     face)
    */

    if (white_face[0][1] == White && white_face[1][0] == White &&
        white_face[1][2] == White && white_face[2][1] == White) {
        return true;
    }

    return false;
}

bool RubiksCube::check_second_part_of_white_cross() {
    /* Check if the second part of the white cross is solved
     1. Check if the second part of the white cross is solved (white edge pieces
     on the white face)
    */
    if (green_face[0][1] == Green && orange_face[0][1] == Orange &&
        red_face[0][1] == Red && blue_face[0][1] == Blue) {
        return true;
    }

    return false;
}

bool RubiksCube::check_gwr_corner() {
    /* Check if the green, white, red corner is solved
     1. Check if the green, white, red corner is solved (green, white, red
     corner pieces on the green, white, red faces)
    */
    if (green_face[0][2] == Green && red_face[0][0] == Red &&
        white_face[2][2] == White) {
        return true;
    }

    return false;
}

bool RubiksCube::check_rwb_corner() {
    /* Check if the red, white, blue corner is solved
     1. Check if the red, white, blue corner is solved (red, white, blue corner
     pieces on the red, white, blue faces)
    */
    if (red_face[0][2] == Red && blue_face[0][0] == Blue &&
        white_face[0][2] == White) {
        return true;
    }

    return false;
}

bool RubiksCube::check_bwo_corner() {
    /* Check if the blue, white, orange corner is solved
     1. Check if the blue, white, orange corner is solved (blue, white, orange
     corner pieces on the blue, white, orange faces)
    */
    if (blue_face[0][2] == Blue && orange_face[0][0] == Orange &&
        white_face[0][0] == White) {
        return true;
    }

    return false;
}

bool RubiksCube::check_owg_corner() {
    /* Check if the orange, white, green corner is solved
     1. Check if the orange, white, green corner is solved (orange, white, green
     corner pieces on the orange, white, green faces)
    */
    if (orange_face[0][2] == Orange && green_face[0][0] == Green &&
        white_face[2][0] == White) {
        return true;
    }

    return false;
}

bool RubiksCube::check_green_red_side() {
    /* Check if the green, red side is solved
     1. Check if the green, red side is solved (green, red side pieces on the
     green, red faces)
    */
    if (green_face[1][2] == Green && red_face[1][0] == Red) {
        return true;
    }

    return false;
}

bool RubiksCube::check_red_blue_side() {
    /* Check if the red, blue side is solved
     1. Check if the red, blue side is solved (red, blue side pieces on the red,
     blue faces)
    */
    if (red_face[1][2] == Red && blue_face[1][0] == Blue) {
        return true;
    }

    return false;
}

bool RubiksCube::check_blue_orange_side() {
    /* Check if the blue, orange side is solved
     1. Check if the blue, orange side is solved (blue, orange side pieces on
     the blue, orange faces)
    */
    if (blue_face[1][2] == Blue && orange_face[1][0] == Orange) {
        return true;
    }

    return false;
}

bool RubiksCube::check_orange_green_side() {
    /* Check if the orange, green side is solved
     1. Check if the orange, green side is solved (orange, green side pieces on
     the orange, green faces)
    */
    if (orange_face[1][2] == Orange && green_face[1][0] == Green) {
        return true;
    }

    return false;
}

bool RubiksCube::check_yellow_cross() {
    /* Check if the yellow cross from stick is solved
     1. Check if the yellow cross stick is solved (yellow cross stick pieces on
     the yellow face)
    */
    if (yellow_face[0][1] == Yellow && yellow_face[1][0] == Yellow &&
        yellow_face[1][2] == Yellow && yellow_face[2][1] == Yellow) {
        return true;
    }

    return false;
}

bool RubiksCube::check_yellow_corners() {
    /* Check if the yellow corners are solved
     1. Check if the yellow corners are solved (yellow corner pieces on the
     yellow face)
    */
    if (yellow_face[0][0] == Yellow && yellow_face[0][2] == Yellow &&
        yellow_face[2][0] == Yellow && yellow_face[2][2] == Yellow) {
        return true;
    }

    return false;
}

bool RubiksCube::check_yellow_edges() {
    /* Check if the yellow edges are solved
     1. Check if the yellow edges are solved (yellow edge pieces on the yellow
     face)
    */
    if (green_face[2][1] == Green && red_face[2][1] == Red &&
        blue_face[2][1] == Blue && orange_face[2][1] == Orange) {
        return true;
    }

    return false;
}

bool RubiksCube::check_yellow_colored_corners() {
    /* Check if the yellow colored corners are solved
     1. Check if the yellow colored corners are solved (yellow colored corner
     pieces on the yellow face)
    */
    if (green_face[2][0] == Green && green_face[2][2] == Green &&
        red_face[2][0] == Red && red_face[2][2] == Red &&
        blue_face[2][0] == Blue && blue_face[2][2] == Blue &&
        orange_face[2][0] == Orange && orange_face[2][2] == Orange) {
        return true;
    }

    return false;
}

void RubiksCube::solve_first_part_of_white_cross() {
    if (check_first_part_of_white_cross()) {
        return;
    }

    int max_attempts = 50;
    while (!check_first_part_of_white_cross() && max_attempts-- > 0) {
        for (int face = 0; face < 6; ++face) {
            switch (face) {
                case 0:
                    if (green_face[1][2] == White &&
                        white_face[1][2] != White) {
                        rotate_right_face();
                        steps.emplace_back("R");
                    } else if (green_face[1][0] == White &&
                               white_face[1][0] != White) {
                        rotate_left_reverse_face();
                        steps.emplace_back("L'");
                    } else if (green_face[0][1] == White &&
                               white_face[0][1] != White) {
                        rotate_up_reverse_face();
                        rotate_front_reverse_face();
                        rotate_up_face();
                        steps.emplace_back("U'");
                        steps.emplace_back("F'");
                        steps.emplace_back("U");
                    } else if (green_face[2][1] == White &&
                               white_face[2][1] != White) {
                        rotate_down_face();
                        rotate_front_face();
                        rotate_down_reverse_face();
                        steps.emplace_back("D");
                        steps.emplace_back("F");
                        steps.emplace_back("D'");
                    }
                    break;
                case 1:
                    if (red_face[1][2] == White && white_face[1][2] != White) {
                        rotate_right_reverse_face();
                        rotate_back_reverse_face();
                        rotate_right_face();
                        steps.emplace_back("R'");
                        steps.emplace_back("B'");
                        steps.emplace_back("R");
                    } else if (red_face[1][0] == White &&
                               white_face[1][0] != White) {
                        rotate_left_face();
                        rotate_back_face();
                        rotate_left_reverse_face();
                        steps.emplace_back("L");
                        steps.emplace_back("B");
                        steps.emplace_back("L'");
                    } else if (red_face[0][1] == White &&
                               white_face[0][1] != White) {
                        rotate_up_reverse_face();
                        rotate_back_reverse_face();
                        rotate_up_face();
                        steps.emplace_back("U'");
                        steps.emplace_back("B'");
                        steps.emplace_back("U");
                    } else if (red_face[2][1] == White &&
                               white_face[2][1] != White) {
                        rotate_down_face();
                        rotate_back_face();
                        rotate_down_reverse_face();
                        steps.emplace_back("D");
                        steps.emplace_back("B");
                        steps.emplace_back("D'");
                    }
                    break;
                case 2:
                    if (blue_face[1][2] == White && white_face[1][0] != White) {
                        rotate_left_reverse_face();
                        rotate_right_reverse_face();
                        steps.emplace_back("L'");
                        steps.emplace_back("R'");
                    } else if (blue_face[1][0] == White &&
                               white_face[1][2] != White) {
                        rotate_left_face();
                        rotate_right_face();
                        steps.emplace_back("L");
                        steps.emplace_back("R");
                    } else if (blue_face[0][1] == White &&
                               white_face[0][1] != White) {
                        rotate_up_reverse_face();
                        rotate_back_face();
                        rotate_up_face();
                        steps.emplace_back("U'");
                        steps.emplace_back("B");
                        steps.emplace_back("U");
                    } else if (blue_face[2][1] == White &&
                               white_face[2][1] != White) {
                        rotate_down_face();
                        rotate_back_reverse_face();
                        rotate_down_reverse_face();
                        steps.emplace_back("D");
                        steps.emplace_back("B'");
                        steps.emplace_back("D'");
                    }
                    break;
                case 3:
                    if (orange_face[1][2] == White &&
                        white_face[2][1] != White) {
                        rotate_right_face();
                        rotate_left_face();
                        steps.emplace_back("R");
                        steps.emplace_back("L");
                    } else if (orange_face[1][0] == White &&
                               white_face[0][1] != White) {
                        rotate_right_reverse_face();
                        rotate_left_reverse_face();
                        steps.emplace_back("R'");
                        steps.emplace_back("L'");
                    } else if (orange_face[0][1] == White &&
                               white_face[1][2] != White) {
                        rotate_up_reverse_face();
                        rotate_left_face();
                        rotate_up_face();
                        steps.emplace_back("U'");
                        steps.emplace_back("L");
                        steps.emplace_back("U");
                    } else if (orange_face[2][1] == White &&
                               white_face[1][0] != White) {
                        rotate_down_face();
                        rotate_left_reverse_face();
                        rotate_down_reverse_face();
                        steps.emplace_back("D");
                        steps.emplace_back("L'");
                        steps.emplace_back("D'");
                    }
                    break;
                case 4:
                    for (int i = 0; i < 3; ++i) {
                        if (yellow_face[i][0] == White &&
                            white_face[1][0] != White) {
                            rotate_left_face_twice();
                            steps.emplace_back("L2");
                        } else if (yellow_face[i][2] == White &&
                                   white_face[1][2] != White) {
                            rotate_right_face_twice();
                            steps.emplace_back("R2");
                        } else if (yellow_face[0][i] == White &&
                                   white_face[2][1] != White) {
                            rotate_front_face_twice();
                            steps.emplace_back("F2");
                        } else if (yellow_face[2][i] == White &&
                                   white_face[0][1] != White) {
                            rotate_back_face_twice();
                            steps.emplace_back("B2");
                        }
                    }
                    break;
            }
        }

        rotate_up_face();
        steps.emplace_back("U");
    }

    if (!check_first_part_of_white_cross()) {
        throw std::runtime_error("Failed to solve white cross");
    }
}

void RubiksCube::solve_second_part_of_white_cross() {
    // Solve the second part of the white cross
    if (check_second_part_of_white_cross()) {
        return;
    }

    /*
     1. Initialize a counter for color matches.
     2. Check each face's top edge color against its center color.
     3. If a match is found, increment the counter.
     4. If less than 2 matches are found, rotate the up face.
     5. Repeat until at least 2 matches are found.
    */
    int color_matches = 0;
    do {
        color_matches = 0;

        if (green_face[0][1] == Green) {
            color_matches++;
        }
        if (orange_face[0][1] == Orange) {
            color_matches++;
        }
        if (red_face[0][1] == Red) {
            color_matches++;
        }
        if (blue_face[0][1] == Blue) {
            color_matches++;
        }

        if (color_matches < 2) {
            rotate_up_face();
            steps.emplace_back("U");
        }
    } while (color_matches < 2);

    /*
     1. This code is part of the Rubik's cube solving algorithm,
        specifically aimed at positioning the edges with two colors (one of
     which is white).
     2. The goal is to align the non-white color of the edge
        with the color of the face where the colored part of this edge is
     located.
     3. Each if statement checks a specific condition of the cube's state
        and performs a series of rotations to correct the position of the edges
     if the condition is met.
    */
    if (green_face[0][1] == Green && orange_face[0][1] == Red &&
        red_face[0][1] == Orange && blue_face[0][1] == Blue) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_up_face_twice();
        steps.emplace_back("U2");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_back_face();
        steps.emplace_back("B");
    }

    if (green_face[0][1] == Blue && orange_face[0][1] == Orange &&
        red_face[0][1] == Red && blue_face[0][1] == Green) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_up_face_twice();
        steps.emplace_back("U2");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_right_face();
        steps.emplace_back("R");
    }

    if (green_face[0][1] == Green && orange_face[0][1] == Orange &&
        red_face[0][1] == Blue && blue_face[0][1] == Red) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_up_face();
        steps.emplace_back("U");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_up_reverse_face();
        steps.emplace_back("U'");

        rotate_right_face();
        steps.emplace_back("R");
    }

    if (orange_face[0][1] == Orange && blue_face[0][1] == Blue &&
        red_face[0][1] == Green && green_face[0][1] == Red) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_up_face();
        steps.emplace_back("U");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_up_reverse_face();
        steps.emplace_back("U'");

        rotate_front_face();
        steps.emplace_back("F");
    }

    if (blue_face[0][1] == Blue && red_face[0][1] == Red &&
        green_face[0][1] == Orange && orange_face[0][1] == Green) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_up_face();
        steps.emplace_back("U");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_up_reverse_face();
        steps.emplace_back("U'");

        rotate_left_face();
        steps.emplace_back("L");
    }

    if (red_face[0][1] == Red && green_face[0][1] == Green &&
        orange_face[0][1] == Blue && blue_face[0][1] == Orange) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_up_face();
        steps.emplace_back("U");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_up_reverse_face();
        steps.emplace_back("U'");

        rotate_back_face();
        steps.emplace_back("B");
    }

    // If the second part of the white cross is not solved, throw an error
    if (!check_second_part_of_white_cross()) {
        throw std::runtime_error("Failed to solve second part of white cross");
    }
}

void RubiksCube::solve_gwr() {
    /* Solve the green, white, and red corner piece
     1. Check if the green, white, and red corner piece is solved
     2. If not, solve the green, white, and red corner piece
    */

    if (check_gwr_corner()) {
        return;
    }

    /* Checking the situation when the green, white, and red corner is out of
       place in the bottom layer We solve this with the usual bang bang, then
       this corner will go to the top layer
    */

    if ((green_face[0][0] == Red && orange_face[0][2] == Green &&
         white_face[2][0] == White) ||
        (green_face[0][0] == Green && orange_face[0][2] == Red &&
         white_face[2][0] == Green) ||
        (green_face[0][0] == Green && orange_face[0][2] == White &&
         white_face[2][0] == Red)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((orange_face[0][0] == Red && blue_face[0][2] == Green &&
         white_face[0][0] == White) ||
        (orange_face[0][0] == White && blue_face[0][2] == Red &&
         white_face[0][0] == Green) ||
        (orange_face[0][0] == Green && blue_face[0][2] == White &&
         white_face[0][0] == Red)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((blue_face[0][0] == Red && red_face[0][2] == Green &&
         white_face[0][2] == White) ||
        (blue_face[0][0] == White && red_face[0][2] == Red &&
         white_face[0][2] == Green) ||
        (blue_face[0][0] == Green && red_face[0][2] == White &&
         white_face[0][2] == Red)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* Checking the situation when the green, white, and red corner is in the
       top layer but not in the right place: We solve this with the yellow face
       rotation, then this corner will go to right place on top layer.
    */
    if ((green_face[2][0] == White && orange_face[2][2] == Green &&
         yellow_face[0][0] == Red) ||
        (green_face[2][0] == Green && orange_face[2][2] == Red &&
         yellow_face[0][0] == White) ||
        (green_face[2][0] == Red && orange_face[2][2] == White &&
         yellow_face[0][0] == Green)) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((orange_face[2][0] == White && blue_face[2][2] == Green &&
         yellow_face[2][0] == Red) ||
        (orange_face[2][0] == Green && blue_face[2][2] == Red &&
         yellow_face[2][0] == White) ||
        (orange_face[2][0] == Red && blue_face[2][2] == White &&
         yellow_face[2][0] == Green)) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if ((blue_face[2][0] == White && red_face[2][2] == Green &&
         yellow_face[2][2] == Red) ||
        (blue_face[2][0] == Green && red_face[2][2] == Red &&
         yellow_face[2][2] == White) ||
        (blue_face[2][0] == Red && red_face[2][2] == White &&
         yellow_face[2][2] == Green)) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* When the corner is in the desired position, depending on its rotation,
       we make a certain number of puff puffs
    */
    if (green_face[2][2] == Green && red_face[2][0] == White &&
        yellow_face[0][2] == Red) {
        for (int i = 0; i < 5; i++) {
            rotate_front_face();
            steps.emplace_back("F");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_reverse_face();
            steps.emplace_back("F'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[2][2] == Red && red_face[2][0] == Green &&
        yellow_face[0][2] == White) {
        for (int i = 0; i < 3; i++) {
            rotate_front_face();
            steps.emplace_back("F");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_reverse_face();
            steps.emplace_back("F'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[2][2] == White && red_face[2][0] == Red &&
        yellow_face[0][2] == Green) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (green_face[0][2] == Red && red_face[0][0] == White &&
        white_face[2][2] == Green) {
        for (int i = 0; i < 4; i++) {
            rotate_front_face();
            steps.emplace_back("F");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_reverse_face();
            steps.emplace_back("F'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[0][2] == White && red_face[0][0] == Green &&
        white_face[2][2] == Red) {
        for (int i = 0; i < 2; i++) {
            rotate_front_face();
            steps.emplace_back("F");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_reverse_face();
            steps.emplace_back("F'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (!check_gwr_corner()) {
        throw std::runtime_error("Failed to solve green, white, red corner");
    }
}

void RubiksCube::solve_rwb() {
    /* Solve the red, white, and blue corner piece
     1. Check if the red, white, and blue corner piece is solved
     2. If not, solve the red, white, and blue corner piece
    */

    if (check_rwb_corner()) {
        return;
    }

    /* Checking the situation when the red, white, and blue corner is out of
       place in the bottom layer We solve this with the usual bang bang, then
       this corner will go to the top layer
    */
    if ((red_face[0][0] == Blue && green_face[0][2] == Red &&
         white_face[2][2] == White) ||
        (red_face[0][0] == White && green_face[0][2] == Blue &&
         white_face[2][2] == Red) ||
        (red_face[0][0] == Red && green_face[0][2] == White &&
         white_face[2][2] == Blue)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((green_face[0][0] == Blue && orange_face[0][2] == Red &&
         white_face[2][0] == White) ||
        (green_face[0][0] == White && orange_face[0][2] == Blue &&
         white_face[2][0] == Red) ||
        (green_face[0][0] == Red && orange_face[0][2] == Blue &&
         white_face[2][0] == Blue)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((orange_face[0][0] == Blue && blue_face[0][2] == Red &&
         white_face[0][0] == White) ||
        (orange_face[0][0] == White && blue_face[0][2] == Blue &&
         white_face[0][0] == Red) ||
        (orange_face[0][0] == Red && blue_face[0][2] == White &&
         white_face[0][0] == Blue)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* Checking the situation when the green, white, and red corner is in the
       top layer but not in the right place: We solve this with the yellow face
       rotation, then this corner will go to right place on top layer.
    */
    if ((red_face[2][0] == White && green_face[2][2] == Red &&
         yellow_face[0][2] == Blue) ||
        (red_face[2][0] == Red && green_face[2][2] == Blue &&
         yellow_face[0][2] == White) ||
        (red_face[2][0] == Blue && green_face[2][2] == White &&
         yellow_face[0][2] == Red)) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((green_face[2][0] == White && orange_face[2][2] == Red &&
         yellow_face[0][0] == Blue) ||
        (green_face[2][0] == Red && orange_face[2][2] == Blue &&
         yellow_face[0][0] == White) ||
        (green_face[2][0] == Blue && orange_face[2][2] == Blue &&
         yellow_face[0][0] == Red)) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if ((orange_face[2][0] == White && blue_face[2][2] == Red &&
         yellow_face[2][0] == Blue) ||
        (orange_face[2][0] == Red && blue_face[2][2] == Blue &&
         yellow_face[2][0] == White) ||
        (orange_face[2][0] == Blue && blue_face[2][2] == White &&
         yellow_face[2][0] == Red)) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* When the corner is in the desired position, depending on its rotation,
       we make a certain number of puff puffs
    */
    if ((red_face[2][2] == Red && blue_face[2][0] == White &&
         yellow_face[2][2] == Blue)) {
        for (int i = 0; i < 5; i++) {
            rotate_right_face();
            steps.emplace_back("R");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_reverse_face();
            steps.emplace_back("R'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if ((red_face[2][2] == Blue && blue_face[2][0] == Red &&
         yellow_face[2][2] == White)) {
        for (int i = 0; i < 3; i++) {
            rotate_right_face();
            steps.emplace_back("R");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_reverse_face();
            steps.emplace_back("R'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if ((red_face[2][2] == White && blue_face[2][0] == Blue &&
         yellow_face[2][2] == Red)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((red_face[0][2] == Blue && blue_face[0][0] == White &&
         white_face[0][2] == Red)) {
        for (int i = 0; i < 4; i++) {
            rotate_right_face();
            steps.emplace_back("R");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_reverse_face();
            steps.emplace_back("R'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if ((red_face[0][2] == White && blue_face[0][0] == Red &&
         white_face[0][2] == Blue)) {
        for (int i = 0; i < 2; i++) {
            rotate_right_face();
            steps.emplace_back("R");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_reverse_face();
            steps.emplace_back("R'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (!check_rwb_corner()) {
        throw std::runtime_error("Failed to solve red, white, blue corner");
    }
}

void RubiksCube::solve_bwo() {
    /* Solve the blue, white, and orange corner piece
     1. Check if the blue, white, and orange corner piece is solved
     2. If not, solve the blue, white, and orange corner piece
    */

    if (check_bwo_corner()) {
        return;
    }

    /* Checking the situation when the blue, white, and orange corner is out of
       place in the bottom layer We solve this with the usual bang bang, then
       this corner will go to the top layer
    */
    if ((blue_face[0][0] == White && red_face[0][2] == Orange &&
         white_face[0][2] == Blue) ||
        (blue_face[0][0] == Blue && red_face[0][2] == White &&
         white_face[0][2] == Orange) ||
        (blue_face[0][0] == Orange && red_face[0][2] == Blue &&
         white_face[0][2] == White)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((red_face[0][0] == White && green_face[0][2] == Orange &&
         white_face[2][2] == Blue) ||
        (red_face[0][0] == Blue && green_face[0][2] == White &&
         white_face[2][2] == Orange) ||
        (red_face[0][0] == Orange && green_face[0][2] == Blue &&
         white_face[2][2] == White)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((green_face[0][0] == White && orange_face[0][2] == Orange &&
         white_face[2][0] == Blue) ||
        (green_face[0][0] == Blue && orange_face[0][2] == White &&
         white_face[2][0] == Orange) ||
        (green_face[0][0] == Orange && orange_face[0][2] == Blue &&
         white_face[2][0] == White)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* Checking the situation when the blue, white, and orange corner is in the
       top layer but not in the right place: We solve this with the yellow face
       rotation, then this corner will go to right place on top layer.
    */
    if ((blue_face[2][0] == White && red_face[2][2] == Blue &&
         yellow_face[2][2] == Orange) ||
        (blue_face[2][0] == Blue && red_face[2][2] == Orange &&
         yellow_face[2][2] == White) ||
        (blue_face[2][0] == Orange && red_face[2][2] == White &&
         yellow_face[2][2] == Blue)) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((red_face[2][0] == White && green_face[2][2] == Blue &&
         yellow_face[0][2] == Orange) ||
        (red_face[2][0] == Blue && green_face[2][2] == Orange &&
         yellow_face[0][2] == White) ||
        (red_face[2][0] == Orange && green_face[2][2] == White &&
         yellow_face[0][2] == Blue)) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if ((green_face[2][0] == White && orange_face[2][2] == Blue &&
         yellow_face[0][0] == Orange) ||
        (green_face[2][0] == Blue && orange_face[2][2] == Orange &&
         yellow_face[0][0] == White) ||
        (green_face[2][0] == Orange && orange_face[2][2] == White &&
         yellow_face[0][0] == Blue)) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* When the corner is in the desired position, depending on its rotation,
       we make a certain number of puff puffs
    */
    if (orange_face[2][0] == White && blue_face[2][2] == Blue &&
        yellow_face[2][0] == Orange) {
        for (int i = 0; i < 5; i++) {
            rotate_back_face();
            steps.emplace_back("B");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_reverse_face();
            steps.emplace_back("B'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (orange_face[2][0] == Blue && blue_face[2][2] == Orange &&
        yellow_face[2][0] == White) {
        for (int i = 0; i < 3; i++) {
            rotate_back_face();
            steps.emplace_back("B");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_reverse_face();
            steps.emplace_back("B'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (orange_face[2][0] == Orange && blue_face[2][2] == White &&
        yellow_face[2][0] == Blue) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (orange_face[0][0] == White && blue_face[0][2] == Orange &&
        white_face[0][0] == Blue) {
        for (int i = 0; i < 4; i++) {
            rotate_back_face();
            steps.emplace_back("B");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_reverse_face();
            steps.emplace_back("B'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (orange_face[0][0] == Blue && blue_face[0][2] == White &&
        white_face[0][0] == Orange) {
        for (int i = 0; i < 2; i++) {
            rotate_back_face();
            steps.emplace_back("B");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_reverse_face();
            steps.emplace_back("B'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (!check_bwo_corner()) {
        throw std::runtime_error("Failed to solve blue, white, orange corner");
    }
}

void RubiksCube::solve_owg() {
    /* Solve the orange, white, and green corner piece
     1. Check if the orange, white, and green corner piece is solved
     2. If not, solve the orange, white, and green corner piece
    */

    if (check_owg_corner()) {
        return;
    }

    /* Checking the situation when the orange, white, and green corner is out of
       place in the bottom layer We solve this with the usual bang bang, then
       this corner will go to the top layer
    */
    if ((orange_face[0][0] == White && blue_face[0][2] == Green &&
         white_face[0][0] == Orange) ||
        (orange_face[0][0] == Orange && blue_face[0][2] == White &&
         white_face[0][0] == Green) ||
        (orange_face[0][0] == Green && blue_face[0][2] == Orange &&
         white_face[0][0] == White)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((blue_face[0][0] == White && red_face[0][2] == Green &&
         white_face[0][2] == Orange) ||
        (blue_face[0][0] == Orange && red_face[0][2] == White &&
         white_face[0][2] == Green) ||
        (blue_face[0][0] == Green && red_face[0][2] == Orange &&
         white_face[0][2] == White)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if ((red_face[0][0] == White && green_face[0][2] == Green &&
         white_face[2][2] == Orange) ||
        (red_face[0][0] == Orange && green_face[0][2] == White &&
         white_face[2][2] == Green) ||
        (red_face[0][0] == Green && green_face[0][2] == Orange &&
         white_face[2][2] == White)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* Checking the situation when the orange, white, and green corner is in the
       top layer but not in the right place: We solve this with the yellow face
       rotation, then this corner will go to right place on top layer.
    */
    if ((orange_face[2][0] == White && blue_face[2][2] == Orange &&
         yellow_face[2][0] == Green) ||
        (orange_face[2][0] == Orange && blue_face[2][2] == Green &&
         yellow_face[2][0] == White) ||
        (orange_face[2][0] == Green && blue_face[2][2] == White &&
         yellow_face[2][0] == Orange)) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((blue_face[2][0] == White && red_face[2][2] == Orange &&
         yellow_face[2][2] == Green) ||
        (blue_face[2][0] == Orange && red_face[2][2] == Green &&
         yellow_face[2][2] == White) ||
        (blue_face[2][0] == Green && red_face[2][2] == White &&
         yellow_face[2][2] == Orange)) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if ((red_face[2][0] == White && green_face[2][2] == Orange &&
         yellow_face[0][2] == Green) ||
        (red_face[2][0] == Orange && green_face[2][2] == Green &&
         yellow_face[0][2] == White) ||
        (red_face[2][0] == Green && green_face[2][2] == White &&
         yellow_face[0][2] == Orange)) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    /* When the corner is in the desired position, depending on its rotation,
       we make a certain number of puff puffs
    */
    if (green_face[2][0] == White && orange_face[2][2] == Orange &&
        yellow_face[0][0] == Green) {
        for (int i = 0; i < 5; i++) {
            rotate_left_face();
            steps.emplace_back("L");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_reverse_face();
            steps.emplace_back("L'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[2][0] == Orange && orange_face[2][2] == Green &&
        yellow_face[0][0] == White) {
        for (int i = 0; i < 3; i++) {
            rotate_left_face();
            steps.emplace_back("L");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_reverse_face();
            steps.emplace_back("L'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[2][0] == Green && orange_face[2][2] == White &&
        yellow_face[0][0] == Orange) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (green_face[0][0] == White && orange_face[0][2] == Green &&
        white_face[2][0] == Orange) {
        for (int i = 0; i < 4; i++) {
            rotate_left_face();
            steps.emplace_back("L");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_reverse_face();
            steps.emplace_back("L'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (green_face[0][0] == Orange && orange_face[0][2] == White &&
        white_face[2][0] == Green) {
        for (int i = 0; i < 2; i++) {
            rotate_left_face();
            steps.emplace_back("L");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_reverse_face();
            steps.emplace_back("L'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }
    }

    if (!check_owg_corner()) {
        throw std::runtime_error("Failed to solve orange, white, green corner");
    }
}

void RubiksCube::solve_green_red_side() {
    /* Solve the green-red side
     1. Check if the green-red side is solved
     2. If not, solve the green-red side
    */

    if (check_green_red_side()) {
        return;
    }

    /* Checking the situation when a green-red edge is between the wrong two
       faces or inverted: We do a left bang-bang interception a left bang-bang.
    */

    if (green_face[1][2] == Red && red_face[1][0] == Green) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((green_face[1][0] == Green && orange_face[1][2] == Red) ||
        (green_face[1][0] == Red && orange_face[1][2] == Green)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((orange_face[1][0] == Red && blue_face[1][2] == Green) ||
        (orange_face[1][0] == Green && blue_face[1][2] == Red)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((blue_face[1][0] == Red && red_face[1][2] == Green) ||
        (blue_face[1][0] == Green && red_face[1][2] == Red)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");
    }

    /* We rearrange this edge to the desired position if it is not on it:
       we do this by turning the yellow side
    */

    if (orange_face[2][1] == Green && yellow_face[1][0] == Red) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (blue_face[2][1] == Green && yellow_face[2][1] == Red) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (red_face[2][1] == Green && yellow_face[1][2] == Red) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (green_face[2][1] == Red && yellow_face[0][1] == Green) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (orange_face[2][1] == Red && yellow_face[1][0] == Green) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (blue_face[2][1] == Red && yellow_face[2][1] == Green) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    // We place this edge if it is in the right place for the algorithm to run
    // correctly.
    if (green_face[2][1] == Green && yellow_face[0][1] == Red) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (red_face[2][1] == Red && yellow_face[1][2] == Green) {
        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if (!check_green_red_side()) {
        throw std::runtime_error("Failed to solve green, red side");
    }
}

void RubiksCube::solve_red_blue_side() {
    /* Solve the red-blue side
     1. Check if the red-blue side is solved
     2. If not, solve the red-blue side
    */

    if (check_red_blue_side()) {
        return;
    }

    /* Checking the situation when a red-blue edge is between the wrong two
       faces or inverted: We do a right bang-bang, interception, a left
       bang-bang.
    */

    if (blue_face[1][0] == Red && red_face[1][2] == Blue) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((blue_face[1][2] == Blue && orange_face[1][0] == Red) ||
        (blue_face[1][2] == Red && orange_face[1][0] == Blue)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((orange_face[1][2] == Blue && green_face[1][0] == Red) ||
        (orange_face[1][2] == Red && green_face[1][0] == Blue)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((green_face[1][2] == Red && red_face[1][0] == Blue) ||
        (green_face[1][2] == Blue && red_face[1][0] == Red)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");
    }

    /* We rearrange this edge to the desired position if it is not on it:
       we do this by turning the yellow side
    */

    if (red_face[2][1] == Blue && yellow_face[1][2] == Red) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (green_face[2][1] == Blue && yellow_face[0][1] == Red) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (orange_face[2][1] == Blue && yellow_face[1][0] == Red) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (green_face[2][1] == Red && yellow_face[0][1] == Blue) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (orange_face[2][1] == Red && yellow_face[1][0] == Blue) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (blue_face[2][1] == Red && yellow_face[2][1] == Blue) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    // We place this edge if it is in the right place for the algorithm to run
    // correctly.
    if (blue_face[2][1] == Blue && yellow_face[2][1] == Red) {
        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if (red_face[2][1] == Red && yellow_face[1][2] == Blue) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (!check_red_blue_side()) {
        throw std::runtime_error("Failed to solve red, blue side");
    }
}

void RubiksCube::solve_blue_orange_side() {
    /* Solve the blue-orange side
     1. Check if the blue-orange side is solved
     2. If not, solve the blue-orange side
    */

    if (check_blue_orange_side()) {
        return;
    }

    /* Checking the situation when a blue-orange edge is between the wrong two
       faces or inverted: We do a right bang-bang, interception, a left
       bang-bang.
    */

    if (orange_face[1][0] == Blue && blue_face[1][2] == Orange) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");
    }

    if ((blue_face[1][0] == Orange && red_face[1][2] == Blue) ||
        (blue_face[1][0] == Blue && red_face[1][2] == Orange)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((red_face[1][0] == Blue && green_face[1][2] == Orange) ||
        (red_face[1][0] == Orange && green_face[1][2] == Blue)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((green_face[1][0] == Orange && orange_face[1][2] == Blue) ||
        (green_face[1][0] == Blue && orange_face[1][2] == Orange)) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");
    }

    /* We rearrange this edge to the desired position if it is not on it:
       we do this by turning the yellow side
    */

    if (red_face[2][1] == Blue && yellow_face[1][2] == Orange) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (green_face[2][1] == Blue && yellow_face[0][1] == Orange) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (orange_face[2][1] == Blue && yellow_face[1][0] == Orange) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (blue_face[2][1] == Orange && yellow_face[2][1] == Blue) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (red_face[2][1] == Orange && yellow_face[1][2] == Blue) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (green_face[2][1] == Orange && yellow_face[0][1] == Blue) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    // We place this edge if it is in the right place for the algorithm to run
    // correctly.
    if (orange_face[2][1] == Orange && yellow_face[1][0] == Blue) {
        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if (blue_face[2][1] == Blue && yellow_face[2][1] == Orange) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (!check_blue_orange_side()) {
        throw std::runtime_error("Failed to solve blue, orange side");
    }
}

void RubiksCube::solve_orange_green_side() {
    /* Solve the orange-green side
     1. Check if the orange-green side is solved
     2. If not, solve the orange-green side
    */

    if (check_orange_green_side()) {
        return;
    }

    /* Checking the situation when a orange-green edge is between the wrong two
       faces or inverted: We do a right bang-bang, interception, a left
       bang-bang.
    */

    if (green_face[1][0] == Orange && orange_face[1][2] == Green) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((orange_face[1][0] == Green && blue_face[1][2] == Orange) ||
        (orange_face[1][0] == Orange && blue_face[1][2] == Green)) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((blue_face[1][0] == Orange && red_face[1][2] == Green) ||
        (blue_face[1][0] == Green && red_face[1][2] == Orange)) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if ((red_face[1][0] == Green && green_face[1][2] == Orange) ||
        (red_face[1][0] == Orange && green_face[1][2] == Green)) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");
    }

    /* We rearrange this edge to the desired position if it is not on it:
       we do this by turning the yellow side
    */

    if (blue_face[2][1] == Orange && yellow_face[2][1] == Green) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (red_face[2][1] == Orange && yellow_face[1][2] == Green) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (green_face[2][1] == Orange && yellow_face[0][1] == Green) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (orange_face[2][1] == Green && yellow_face[1][0] == Orange) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (blue_face[2][1] == Green && yellow_face[2][1] == Orange) {
        rotate_down_face_twice();
        steps.emplace_back("D2");
    }

    if (red_face[2][1] == Green && yellow_face[1][2] == Orange) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    // We place this edge if it is in the right place for the algorithm to run
    // correctly.
    if (green_face[2][1] == Green && yellow_face[0][1] == Green) {
        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");
    }

    if (orange_face[2][1] == Orange && yellow_face[1][0] == Green) {
        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }
}

void RubiksCube::yellow_cross_stick() {
    // Check if the yellow cross is solved
    if (check_yellow_cross()) {
        return;
    }

    if (yellow_face[1][0] == Yellow && yellow_face[1][2] == Yellow) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        return;
    }

    if (yellow_face[0][1] == Yellow && yellow_face[2][1] == Yellow) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        return;
    }
}

void RubiksCube::yellow_cross_tick() {
    // Check if the yellow cross is solved
    if (check_yellow_cross()) {
        return;
    }

    if (yellow_face[0][1] == Yellow && yellow_face[1][0] == Yellow) {
        rotate_back_face();
        steps.emplace_back("B");

        for (int i = 0; i < 2; i++) {
            rotate_right_face();
            steps.emplace_back("R");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_reverse_face();
            steps.emplace_back("R'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        return;
    }

    if (yellow_face[0][1] == Yellow && yellow_face[1][2] == Yellow) {
        rotate_left_face();
        steps.emplace_back("L");

        for (int i = 0; i < 2; i++) {
            rotate_back_face();
            steps.emplace_back("B");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_reverse_face();
            steps.emplace_back("B'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        return;
    }

    if (yellow_face[2][1] == Yellow && yellow_face[1][2] == Yellow) {
        rotate_front_face();
        steps.emplace_back("F");

        for (int i = 0; i < 2; i++) {
            rotate_left_face();
            steps.emplace_back("L");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_reverse_face();
            steps.emplace_back("L'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        return;
    }

    if (yellow_face[2][1] == Yellow && yellow_face[1][0] == Yellow) {
        rotate_right_face();
        steps.emplace_back("R");

        for (int i = 0; i < 2; i++) {
            rotate_front_face();
            steps.emplace_back("F");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_reverse_face();
            steps.emplace_back("F'");

            rotate_down_reverse_face();
            steps.emplace_back("D'");
        }

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        return;
    }
}

void RubiksCube::yellow_cross_dot() {
    // Check if the yellow cross is solved
    if (check_yellow_cross()) {
        return;
    }

    rotate_front_face();
    steps.emplace_back("F");

    rotate_left_face();
    steps.emplace_back("L");

    rotate_down_face();
    steps.emplace_back("D");

    rotate_left_reverse_face();
    steps.emplace_back("L'");

    rotate_down_reverse_face();
    steps.emplace_back("D'");

    rotate_front_reverse_face();
    steps.emplace_back("F'");

    yellow_cross_tick();
}

void RubiksCube::solve_yellow_corners() {
    /* Solve the yellow corners on the top face of the cube in cases:
        1. When the yellow corners are in the right place
        2. When the yellow corners are in the wrong place
    */

    // Check if the yellow corners are in the right place
    if (check_yellow_corners()) {
        return;
    }

    // Solve the yellow corners
    for (int i = 0; i < 4; i++) {
        if (green_face[2][0] == Yellow) {
            for (int j = 0; j < 4; j++) {
                rotate_up_face();
                steps.emplace_back("U");

                rotate_front_face();
                steps.emplace_back("F");

                rotate_up_reverse_face();
                steps.emplace_back("U'");

                rotate_front_reverse_face();
                steps.emplace_back("F'");
            }
        } else if (orange_face[2][2] == Yellow) {
            for (int j = 0; j < 2; j++) {
                rotate_up_face();
                steps.emplace_back("U");

                rotate_front_face();
                steps.emplace_back("F");

                rotate_up_reverse_face();
                steps.emplace_back("U'");

                rotate_front_reverse_face();
                steps.emplace_back("F'");
            }
        }

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (!check_yellow_corners()) {
        throw std::runtime_error("Failed to solve yellow corners");
    }
}

int RubiksCube::check_yellow_edges_count() {
    int count = 0;

    if (green_face[2][1] == Green) {
        count++;
    }

    if (orange_face[2][1] == Orange) {
        count++;
    }

    if (blue_face[2][1] == Blue) {
        count++;
    }

    if (red_face[2][1] == Red) {
        count++;
    }

    return count;
}

void RubiksCube::solve_yellow_edges() {
    /* Solve the yellow edges on the top face of the cube in cases:
        1. When the yellow edges are in the right place
        2. When the yellow edges are in the wrong place
    */

    // Check if the yellow edges are in the right place
    if (check_yellow_edges()) {
        return;
    }

    // Solve the yellow edges
    while (check_yellow_edges_count() < 2) {
        rotate_down_face();
        steps.emplace_back("D");
    }

    if (check_yellow_edges()) {
        return;
    }

    if (green_face[2][1] == Green && red_face[2][1] == Red) {
        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_back_face_twice();
        steps.emplace_back("B2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        return;
    } else if (green_face[2][1] == Green && orange_face[2][1] == Orange) {
        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_back_reverse_face();
        steps.emplace_back("B'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_back_face();
        steps.emplace_back("B");

        rotate_right_face_twice();
        steps.emplace_back("R2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        return;
    } else if (orange_face[2][1] == Orange && blue_face[2][1] == Blue) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_front_face_twice();
        steps.emplace_back("F2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        return;
    } else if (blue_face[2][1] == Blue && red_face[2][1] == Red) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_left_face_twice();
        steps.emplace_back("L2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        return;
    }

    if (red_face[2][1] == Red && orange_face[2][1] == Orange) {
        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_front_face_twice();
        steps.emplace_back("F2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_down_face_twice();
        steps.emplace_back("D2");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_reverse_face();
        steps.emplace_back("R'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_right_face();
        steps.emplace_back("R");

        rotate_front_face_twice();
        steps.emplace_back("F2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    } else if (green_face[2][1] == Green && blue_face[2][1] == Blue) {
        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_left_face_twice();
        steps.emplace_back("L2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_down_face_twice();
        steps.emplace_back("D2");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_reverse_face();
        steps.emplace_back("F'");

        rotate_left_face();
        steps.emplace_back("L");

        rotate_down_face();
        steps.emplace_back("D");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_front_face();
        steps.emplace_back("F");

        rotate_left_face_twice();
        steps.emplace_back("L2");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_left_reverse_face();
        steps.emplace_back("L'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");

        rotate_down_reverse_face();
        steps.emplace_back("D'");
    }

    if (!check_yellow_edges()) {
        throw std::runtime_error("Failed to solve yellow edges");
    }
}

void RubiksCube::solve_yellow_colored_corners() {
    /* Solve the yellow colored corners on the top face of the cube in cases:
        1. When the yellow colored corners are in the right place
        2. When the yellow colored corners are in the wrong place
    */

    // Check if the yellow colored corners are in the right place
    if (check_yellow_colored_corners()) {
        return;
    }

    // Solve the yellow colored corners
    while (!check_yellow_colored_corners()) {
        if (green_face[2][2] == Green && red_face[2][0] == Red &&
            yellow_face[0][2] == Yellow) {
            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_up_face();
            steps.emplace_back("U");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_up_reverse_face();
            steps.emplace_back("U'");

            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_down_reverse_face();
            steps.emplace_back("D'");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_face_twice();
            steps.emplace_back("L2");
        } else if (blue_face[2][2] == Blue && orange_face[2][0] == Orange &&
                   yellow_face[2][0] == Yellow) {
            rotate_front_face_twice();
            steps.emplace_back("F2");

            rotate_up_face();
            steps.emplace_back("U");

            rotate_front_face_twice();
            steps.emplace_back("F2");

            rotate_up_reverse_face();
            steps.emplace_back("U'");

            rotate_right_face_twice();
            steps.emplace_back("R2");

            rotate_front_face_twice();
            steps.emplace_back("F2");

            rotate_down_reverse_face();
            steps.emplace_back("D'");

            rotate_front_face_twice();
            steps.emplace_back("F2");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_right_face_twice();
            steps.emplace_back("R2");
        } else if (red_face[2][2] == Red && blue_face[2][0] == Blue &&
                   yellow_face[2][2] == Yellow) {
            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_up_face();
            steps.emplace_back("U");

            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_up_reverse_face();
            steps.emplace_back("U'");

            rotate_front_face_twice();
            steps.emplace_back("F2");

            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_down_reverse_face();
            steps.emplace_back("D'");

            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_front_face_twice();
            steps.emplace_back("F2");
        } else if (orange_face[2][2] == Orange && green_face[2][0] == Green &&
                   yellow_face[0][0] == Yellow) {
            rotate_right_face_twice();
            steps.emplace_back("R2");

            rotate_up_face();
            steps.emplace_back("U");

            rotate_right_face_twice();
            steps.emplace_back("R2");

            rotate_up_reverse_face();
            steps.emplace_back("U'");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_right_face_twice();
            steps.emplace_back("R2");

            rotate_down_reverse_face();
            steps.emplace_back("D'");

            rotate_right_face_twice();
            steps.emplace_back("R2");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_back_face_twice();
            steps.emplace_back("B2");
        } else {
            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_up_face();
            steps.emplace_back("U");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_up_reverse_face();
            steps.emplace_back("U'");

            rotate_left_face_twice();
            steps.emplace_back("L2");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_down_reverse_face();
            steps.emplace_back("D'");

            rotate_back_face_twice();
            steps.emplace_back("B2");

            rotate_down_face();
            steps.emplace_back("D");

            rotate_left_face_twice();
            steps.emplace_back("L2");
        }
    }

    if (!check_yellow_colored_corners()) {
        throw std::runtime_error("Failed to solve yellow colored corners");
    }
}

void RubiksCube::solve_white_cross() {
    // Solve the white cross
    solve_first_part_of_white_cross();

    // Solve the paths near the centers of the faces
    solve_second_part_of_white_cross();
}

void RubiksCube::solve_f2l() {
    // Solve corners
    solve_gwr();
    solve_rwb();
    solve_bwo();
    solve_owg();

    // Solve edges
    solve_green_red_side();
    solve_red_blue_side();
    solve_blue_orange_side();
    solve_orange_green_side();
}

void RubiksCube::solve_oll() {
    /* Solve the yellow cross on the top face of the cube in cases:
        1. When the yellow cross is a stick
        2. When the yellow cross is a tick
        3. When the yellow cross is a dot
    */
    yellow_cross_stick();
    yellow_cross_tick();
    yellow_cross_dot();

    // Solve the yellow corners
    solve_yellow_corners();
}

void RubiksCube::solve_pll() {
    // Solve the yellow edges
    solve_yellow_edges();

    // Solve the yellow colored corners
    solve_yellow_corners();

    // Solve the yellow colored corners
    solve_yellow_colored_corners();
}

void RubiksCube::solve_cube() {
    // Solve the white cross
    solve_white_cross();

    // Solve the first two layers
    solve_f2l();

    // Solve the yellow cross
    solve_oll();

    // Solve the yellow corners and edges
    solve_pll();
}

void RubiksCube::print_faces() {
    // Print White face
    for (int i = 0; i < 3; i++) {
        std::cout << "        ";
        for (int j = 0; j < 3; j++) {
            std::cout << static_cast<char>(white_face[i][j]) << " ";
        }
        std::cout << "\n";
    }

    // Print Orange, Green, Red, Blue faces
    for (int i = 0; i < 3; i++) {
        std::cout << static_cast<char>(orange_face[i][0]) << " ";
        std::cout << static_cast<char>(orange_face[i][1]) << " ";
        std::cout << static_cast<char>(orange_face[i][2]) << "   ";

        std::cout << static_cast<char>(green_face[i][0]) << " ";
        std::cout << static_cast<char>(green_face[i][1]) << " ";
        std::cout << static_cast<char>(green_face[i][2]) << "   ";

        std::cout << static_cast<char>(red_face[i][0]) << " ";
        std::cout << static_cast<char>(red_face[i][1]) << " ";
        std::cout << static_cast<char>(red_face[i][2]) << "   ";

        std::cout << static_cast<char>(blue_face[i][0]) << " ";
        std::cout << static_cast<char>(blue_face[i][1]) << " ";
        std::cout << static_cast<char>(blue_face[i][2]) << "\n";
    }

    // Print Yellow face
    for (int i = 0; i < 3; i++) {
        std::cout << "        ";
        for (int j = 0; j < 3; j++) {
            std::cout << static_cast<char>(yellow_face[i][j]) << " ";
        }
        std::cout << "\n";
    }
}

void RubiksCube::print_steps() {
    for (auto &step : steps) {
        std::cout << step << " ";
    }

    std::cout << "\n";
}

std::vector<std::string> RubiksCube::collect_steps() { return steps; }