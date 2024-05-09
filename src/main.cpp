#include "solver/CLIParameters.h"
#include "solver/CubeSolver.h"
#include "solver/StateManager.h"
#include "visual/CubeRenderer.h"

#include <string>
#include <vector>

CubeRenderer* globalRenderer;

void globalSpincube() { globalRenderer->spincube(); }

void globalMyreshape(int w, int h) { globalRenderer->myreshape(w, h); }

void globalMouse(int btn, int state, int x, int y) {
    globalRenderer->mouse(btn, state, x, y);
}

void globalMotion(int x, int y) { globalRenderer->motion(x, y); }

void globalDisplay() { globalRenderer->display(); }

void keyboard(unsigned char key, int x, int y) {
    if (key == 'a' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 1;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 1;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'q' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 1;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -1;
        glutIdleFunc(globalSpincube);
    }
    if (key == 's' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 2;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 2;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'w' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 2;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -2;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'd' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 3;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 3;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'e' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 3;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -3;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'f' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 4;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 4;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'r' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 4;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -4;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'g' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 5;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 5;
        glutIdleFunc(globalSpincube);
    }
    if (key == 't' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 5;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -5;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'h' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 6;
        globalRenderer->inverse = 0;
        globalRenderer->solve[++globalRenderer->count] = 6;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'y' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        globalRenderer->rotation = 6;
        globalRenderer->inverse = 1;
        globalRenderer->solve[++globalRenderer->count] = -6;
        glutIdleFunc(globalSpincube);
    }
    if (key == '2' && globalRenderer->rotation_complete == 1) {
        globalRenderer->p = globalRenderer->p + 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '8' && globalRenderer->rotation_complete == 1) {
        globalRenderer->p = globalRenderer->p - 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '6' && globalRenderer->rotation_complete == 1) {
        globalRenderer->q = globalRenderer->q + 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '4' && globalRenderer->rotation_complete == 1) {
        globalRenderer->q = globalRenderer->q - 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '9' && globalRenderer->rotation_complete == 1) {
        globalRenderer->r = globalRenderer->r + 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '1' && globalRenderer->rotation_complete == 1) {
        globalRenderer->r = globalRenderer->r - 2.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == '5' && globalRenderer->rotation_complete == 1) {
        globalRenderer->p = 0.0;
        globalRenderer->q = 0.0;
        globalRenderer->r = 0.0;
        glutIdleFunc(globalSpincube);
    }
    if (key == 'm' && globalRenderer->rotation_complete == 1) {
        if (globalRenderer->speed <= 1.3) {
            globalRenderer->speed = globalRenderer->speed + 0.3;
        }
        glutPostRedisplay();
    }
    if (key == 'm' && globalRenderer->rotation_complete == 1) {
        if (globalRenderer->speed > 1.3) {
            if (globalRenderer->speed <= 2.9) {
                globalRenderer->speed = globalRenderer->speed + 0.3;
            }
        }
        glutPostRedisplay();
    }
    if (key == 'm' && globalRenderer->rotation_complete == 1) {
        if (globalRenderer->speed > 2.9) {
            if (globalRenderer->speed <= 4.2) {
                globalRenderer->speed = globalRenderer->speed + 0.3;
            }
        }
        glutPostRedisplay();
    }
    if (key == 'n' && globalRenderer->rotation_complete == 1) {
        if (globalRenderer->speed >= 0.3) {
            globalRenderer->speed = globalRenderer->speed - 0.3;
        }
        glutPostRedisplay();
    }
    if (key == 'o' && globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        if (globalRenderer->count >= 0) {
            if (globalRenderer->solve[globalRenderer->count] < 0) {
                globalRenderer->rotation =
                    -1 * globalRenderer->solve[globalRenderer->count];
                globalRenderer->inverse = 0;
                glutIdleFunc(globalSpincube);
            }
            if (globalRenderer->solve[globalRenderer->count] > 0) {
                globalRenderer->rotation =
                    globalRenderer->solve[globalRenderer->count];
                globalRenderer->inverse = 1;
                glutIdleFunc(globalSpincube);
            }
            globalRenderer->count--;
        }
        glutIdleFunc(globalSpincube);
    }
    if (key == 27) {
        if (globalRenderer->rotation_complete == 1) {
            globalRenderer->rotation_complete = 0;
            globalRenderer->processNextStep();
        }
    }
}

void mymenu(int id) {
    if (globalRenderer->rotation_complete == 1) {
        globalRenderer->rotation_complete = 0;
        switch (id) {
            case 0:
                glutIdleFunc(globalSpincube);
                break;

            case 1:
                globalRenderer->rotation = 1;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 1;
                glutIdleFunc(globalSpincube);
                break;

            case 2:
                globalRenderer->rotation = 1;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -1;
                glutIdleFunc(globalSpincube);
                break;

            case 3:
                globalRenderer->rotation = 2;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 2;
                glutIdleFunc(globalSpincube);
                break;

            case 4:
                globalRenderer->rotation = 2;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -2;
                glutIdleFunc(globalSpincube);
                break;

            case 5:
                globalRenderer->rotation = 3;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 3;
                glutIdleFunc(globalSpincube);
                break;

            case 6:
                globalRenderer->rotation = 3;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -3;
                glutIdleFunc(globalSpincube);
                break;

            case 7:
                globalRenderer->rotation = 4;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 4;
                glutIdleFunc(globalSpincube);
                break;

            case 8:
                globalRenderer->rotation = 4;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -4;
                glutIdleFunc(globalSpincube);
                break;

            case 9:
                globalRenderer->rotation = 5;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 5;
                glutIdleFunc(globalSpincube);
                break;

            case 10:
                globalRenderer->rotation = 5;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -5;
                glutIdleFunc(globalSpincube);
                break;

            case 11:
                globalRenderer->rotation = 6;
                globalRenderer->inverse = 0;
                globalRenderer->solve[++globalRenderer->count] = 6;
                glutIdleFunc(globalSpincube);
                break;

            case 12:
                globalRenderer->rotation = 6;
                globalRenderer->inverse = 1;
                globalRenderer->solve[++globalRenderer->count] = -6;
                glutIdleFunc(globalSpincube);
                break;

            case 13:
                exit(0);
                break;
        }
    }
}

void CubeRenderer::processNextStep() {
    if (solveQueue.empty()) return;

    std::string step = solveQueue.front();
    solveQueue.pop_front();

    if (step == "F") {
        rotation = 3;
        inverse = 0;
    } else if (step == "F'") {
        rotation = 3;
        inverse = 1;
    } else if (step == "B") {
        rotation = 5;
        inverse = 0;
    } else if (step == "B'") {
        rotation = 5;
        inverse = 1;
    } else if (step == "U") {
        rotation = 1;
        inverse = 0;
    } else if (step == "U'") {
        rotation = 1;
        inverse = 1;
    } else if (step == "D") {
        rotation = 6;
        inverse = 0;
    } else if (step == "D'") {
        rotation = 6;
        inverse = 1;
    } else if (step == "L") {
        rotation = 4;
        inverse = 0;
    } else if (step == "L'") {
        rotation = 4;
        inverse = 1;
    } else if (step == "R") {
        rotation = 2;
        inverse = 0;
    } else if (step == "R'") {
        rotation = 2;
        inverse = 1;
    } else if (step == "F2") {
        rotation = 3;
        inverse = 0;
        solveQueue.push_front("F");
    } else if (step == "B2") {
        rotation = 5;
        inverse = 0;
        solveQueue.push_front("B");
    } else if (step == "U2") {
        rotation = 1;
        inverse = 0;
        solveQueue.push_front("U");
    } else if (step == "D2") {
        rotation = 6;
        inverse = 0;
        solveQueue.push_front("D");
    } else if (step == "L2") {
        rotation = 4;
        inverse = 0;
        solveQueue.push_front("L");
    } else if (step == "R2") {
        rotation = 2;
        inverse = 0;
        solveQueue.push_front("R");
    }

    rotation_complete = 0;
    glutIdleFunc(globalSpincube);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("RUBIK'S CUBE");

    CubeRenderer cubeRenderer;
    globalRenderer = &cubeRenderer;

    CLIParameters cli_parameters(argc, argv);
    std::string input_file = cli_parameters.collect_filename();

    CubeInitState cube_init_state(input_file);
    std::vector<std::vector<std::vector<Color>>> faces =
        cube_init_state.get_faces();

    RubiksCube cube_solver(faces);
    cube_solver.solve_cube();

    std::vector<std::string> steps = cube_solver.collect_steps();

    cubeRenderer.loadCubeState(faces);
    cubeRenderer.loadSteps(steps);

    glutReshapeFunc(globalMyreshape);
    glutIdleFunc(globalSpincube);
    glutMouseFunc(globalMouse);
    glutMotionFunc(globalMotion);
    glutCreateMenu(mymenu);

    glutAddMenuEntry("Orientation:", 0);
    glutAddMenuEntry("Top                   :a", 1);
    glutAddMenuEntry("Top Inverted    :q", 2);
    glutAddMenuEntry("Right                 :s", 3);
    glutAddMenuEntry("Right Inverted  :w", 4);
    glutAddMenuEntry("Front                 :d", 5);
    glutAddMenuEntry("Front Inverted  :e", 6);
    glutAddMenuEntry("Left                   :f", 7);
    glutAddMenuEntry("Left Inverted    :r", 8);
    glutAddMenuEntry("Back                  :g", 9);
    glutAddMenuEntry("Back Inverted   :t", 10);
    glutAddMenuEntry("Bottom              :h", 11);
    glutAddMenuEntry("Bottom Inverted :y", 12);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("Rotation Speed:", 0);
    glutAddMenuEntry("Increase	 :m", 0);
    glutAddMenuEntry("Decrease	 :n", 0);
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("Next Step        :ESC", 14);
    glutAddMenuEntry("Exit", 13);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(globalDisplay);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}