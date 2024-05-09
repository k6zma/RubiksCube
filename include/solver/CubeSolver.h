#ifndef RUBIKSCUBE_CUBESOLVER_H
#define RUBIKSCUBE_CUBESOLVER_H

#include <vector>

enum Color {
    Green = 'G',
    Orange = 'O',
    Red = 'R',
    Blue = 'B',
    White = 'W',
    Yellow = 'Y'
};

class RubiksCube {
public:
    RubiksCube(std::vector<std::vector<std::vector<Color>>> faces);

    void solve_cube();

    void print_faces();
    void print_steps();

    std::vector<std::string> collect_steps();

    void rotate_front_face();
    void rotate_front_reverse_face();
    void rotate_front_face_twice();

    void rotate_back_face();
    void rotate_back_reverse_face();
    void rotate_back_face_twice();

    void rotate_left_face();
    void rotate_left_reverse_face();
    void rotate_left_face_twice();

    void rotate_right_face();
    void rotate_right_reverse_face();
    void rotate_right_face_twice();

    void rotate_up_face();
    void rotate_up_reverse_face();
    void rotate_up_face_twice();

    void rotate_down_face();
    void rotate_down_reverse_face();
    void rotate_down_face_twice();


private:
    std::vector<std::vector<Color>> white_face;
    std::vector<std::vector<Color>> red_face;
    std::vector<std::vector<Color>> blue_face;
    std::vector<std::vector<Color>> orange_face;
    std::vector<std::vector<Color>> green_face;
    std::vector<std::vector<Color>> yellow_face;

    std::vector<std::string> steps;
    std::string new_steps;

    void validate_init_faces();

    int color_to_index(Color color);


    bool check_first_part_of_white_cross();
    bool check_second_part_of_white_cross();

    bool check_gwr_corner();
    bool check_rwb_corner();
    bool check_bwo_corner();
    bool check_owg_corner();

    bool check_green_red_side();
    bool check_red_blue_side();
    bool check_blue_orange_side();
    bool check_orange_green_side();

    bool check_yellow_cross();
    bool check_yellow_corners();

    bool check_yellow_edges();
    bool check_yellow_colored_corners();

    void solve_first_part_of_white_cross();
    void solve_second_part_of_white_cross();

    void solve_gwr();
    void solve_rwb();
    void solve_bwo();
    void solve_owg();

    void solve_green_red_side();
    void solve_red_blue_side();
    void solve_blue_orange_side();
    void solve_orange_green_side();

    void yellow_cross_stick();
    void yellow_cross_tick();
    void yellow_cross_dot();

    int check_yellow_edges_count();
    void solve_yellow_edges();
    void solve_yellow_corners();
    void solve_yellow_colored_corners();

    void solve_white_cross();
    void solve_f2l();
    void solve_oll();
    void solve_pll();

    std::vector<std::string> optimize_steps();
};

#endif
