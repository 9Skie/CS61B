#pragma once
#include "TETile.hpp"
namespace Tileset {

inline const TETile AVATAR = TETile("@", Color::WHITE, Color::BLACK, "you");
inline const TETile WALL = TETile("#", Color(216, 128, 128), Color::DARK_GRAY, "wall");
inline const TETile FLOOR = TETile("·", Color(128, 192, 128), Color::BLACK, "floor");
inline const TETile NOTHING = TETile(" ", Color::BLACK, Color::BLACK, "nothing");
inline const TETile GRASS = TETile("\"", Color::GREEN, Color::BLACK, "grass");
inline const TETile WATER = TETile("≈", Color::BLUE, Color::BLACK, "water");
inline const TETile FLOWER = TETile("❀", Color::MAGENTA, Color::PINK, "flower");
inline const TETile LOCKED_DOOR = TETile("█", Color::ORANGE, Color::BLACK, "locked door");
inline const TETile UNLOCKED_DOOR = TETile("▢", Color::ORANGE, Color::BLACK, "unlocked door");
inline const TETile SAND = TETile("▒", Color::YELLOW, Color::BLACK, "sand");
inline const TETile MOUNTAIN = TETile("▲", Color::GRAY, Color::BLACK, "mountain");
inline const TETile TREE = TETile("♠", Color::GREEN, Color::BLACK, "tree");
inline const TETile CELL = TETile("█", Color::WHITE, Color::BLACK, "cell");

} // namespace Tileset
