#include "tileengine/TERenderer.hpp"
#include "tileengine/Tileset.hpp"
int main() {
    TERenderer ter;
    ter.initialize(60, 30);
    World world(60, std::vector<TETile>(30, Tileset::NOTHING));
    for (int x = 20; x < 35; ++x)
        for (int y = 5; y < 10; ++y)
            world[x][y] = Tileset::WALL;
    ter.renderFrame(world);
    Draw::waitUntilClosed();
}
