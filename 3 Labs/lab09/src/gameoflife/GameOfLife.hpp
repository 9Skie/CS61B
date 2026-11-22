#pragma once
#include "tileengine/TERenderer.hpp"
#include "tileengine/Tileset.hpp"
#include "utils/FileUtils.hpp"
// Conway's Game of Life. Assignment by Erik Nelson, Jasmine Lin and Elana Ho.
class GameOfLife {
    static constexpr int DEFAULT_WIDTH = 50, DEFAULT_HEIGHT = 50;
    inline static const std::string SAVE_FILE = "src/save.txt";
    int64_t prevFrameTimestep = 0;
    TERenderer ter;
    course::Random random;
    World currentState;
    int width = 0, height = 0;
    static World transpose(const World &tiles) {
        World result(tiles.at(0).size(), std::vector<TETile>(tiles.size()));
        for (size_t x = 0; x < result.size(); ++x)
            for (size_t y = 0; y < tiles.size(); ++y)
                result[x][y] = tiles.at(y).at(x);
        return result;
    }
    static World flip(World tiles) {
        for (auto &column : tiles)
            std::reverse(column.begin(), column.end());
        return tiles;
    }
    TETile randomTile() {
        return random.nextInt(2) == 0 ? Tileset::CELL : Tileset::NOTHING;
    }

  public:
    explicit GameOfLife(int64_t seed, bool test = false)
        : random(seed), width(DEFAULT_WIDTH), height(DEFAULT_HEIGHT) {
        currentState = World(width, std::vector<TETile>(height));
        fillWithRandomTiles(currentState);
        if (!test)
            ter.initialize(width, height);
    }
    explicit GameOfLife(const std::string &filename, bool test = false) {
        currentState = loadBoard(filename);
        if (!test)
            ter.initialize(width, height);
    }
    GameOfLife(const World &tiles, bool test)
        : currentState(flip(transpose(tiles))), width(tiles.at(0).size()), height(tiles.size()) {}
    void runGame() {
        bool paused = false;
        int64_t evoTimestamp = course::millis(), pausedTimestamp = course::millis(),
                clickTimestamp = course::millis();
        while (Draw::isOpen()) {
            auto now = course::millis();
            if (!paused && now - evoTimestamp > 250) {
                evoTimestamp = now;
                currentState = nextGeneration(currentState);
            }
            if (now - prevFrameTimestep > 17) {
                prevFrameTimestep = now;
                int x = int(Draw::mouseX()), y = int(Draw::mouseY());
                if (x >= 0 && x < width && y >= 0 && y < height && Draw::isMousePressed() &&
                    now - clickTimestamp > 250) {
                    clickTimestamp = now;
                    currentState.at(x).at(y) = currentState.at(x).at(y) == Tileset::CELL
                                                   ? Tileset::NOTHING
                                                   : Tileset::CELL;
                }
                if (Draw::isKeyPressed(' ') && now - pausedTimestamp > 500) {
                    pausedTimestamp = now;
                    paused = !paused;
                }
                if (Draw::isKeyPressed('s')) {
                    saveBoard();
                    return;
                }
                ter.renderFrame(currentState);
            }
            Draw::pause(1);
        }
    }
    void fillWithRandomTiles(World &tiles) {
        for (auto &column : tiles)
            for (auto &tile : column)
                tile = randomTile();
    }
    void fillWithNothing(World &tiles) {
        for (auto &column : tiles)
            for (auto &tile : column)
                tile = Tileset::NOTHING;
    }
    const World &returnCurrentState() const {
        return currentState;
    }
    // Live cells survive with 2 or 3 neighbors; dead cells are born with 3.
    // Every other cell is dead in the next generation.
    World nextGeneration(const World &tiles) {
        World nextGen(width, std::vector<TETile>(height));
        fillWithNothing(nextGen);
        // TODO: Apply the rules to tiles and return nextGen.
        return {};
    }
    void saveBoard(const World &tiles) {
        currentState = flip(transpose(tiles));
        width = tiles.at(0).size();
        height = tiles.size();
        saveBoard();
    }
    void saveBoard() {
        // TODO: Write width and height separated by a space and ending with '\n'.
        // TODO: Write the current board to SAVE_FILE. Use 0 for NOTHING, 1 for CELL.
        // TODO: Keep the orientation correct and end every row with '\n'.
    }
    World loadBoard(const std::string &filename) {
        // TODO: Read the file with FileUtils and split it into lines.
        // TODO: Set width and height from the first line.
        // TODO: Allocate a World and load 0/1 cells with the correct orientation.
        // TODO: Return the loaded board.
        return {};
    }
};
