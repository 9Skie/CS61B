#include "BombMain.hpp"
int main(int argc, char **argv) {
    try {
        BombMain::answers(argc > 1 ? course::parseInt(argv[1]) : 2);
    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
