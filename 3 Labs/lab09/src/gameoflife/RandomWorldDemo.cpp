#include "tileengine/TERenderer.hpp"
#include "tileengine/Tileset.hpp"
namespace {
course::Random randomTiles(2873123);
TETile randomTile() {
    int n = randomTiles.nextInt(3);
    return n == 0 ? Tileset::WALL : n == 1 ? Tileset::FLOWER : Tileset::NOTHING;
}
} // namespace
void fillWithRandomTiles(World &tiles) {
    for (auto &column : tiles)
        for (auto &tile : column)
            tile = randomTile();
}
int main() {
    TERenderer ter;
    ter.initialize(50, 50);
    World world(50, std::vector<TETile>(50));
    fillWithRandomTiles(world);
    ter.renderFrame(world);
    Draw::waitUntilClosed();
}
