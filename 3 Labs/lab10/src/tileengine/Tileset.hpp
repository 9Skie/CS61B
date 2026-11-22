#pragma once
#include "TETile.hpp"
namespace Tileset {

inline const TETile AVATAR = TETile("@", Color::WHITE, Color::BLACK, "you", 0);
inline const TETile WALL = TETile("#", Color(216, 128, 128), Color::DARK_GRAY, "wall", 1);
inline const TETile FLOOR = TETile("·", Color(128, 192, 128), Color::BLACK, "floor", 2);
inline const TETile NOTHING = TETile(" ", Color::BLACK, Color::BLACK, "nothing", 3);
inline const TETile GRASS = TETile("\"", Color::GREEN, Color::BLACK, "grass", 4);
inline const TETile WATER = TETile("≈", Color::BLUE, Color::BLACK, "water", 5);
inline const TETile FLOWER = TETile("❀", Color::MAGENTA, Color::PINK, "flower", 6);
inline const TETile LOCKED_DOOR = TETile("█", Color::ORANGE, Color::BLACK, "locked door", 7);
inline const TETile UNLOCKED_DOOR = TETile("▢", Color::ORANGE, Color::BLACK, "unlocked door", 8);
inline const TETile SAND = TETile("▒", Color::YELLOW, Color::BLACK, "sand", 9);
inline const TETile MOUNTAIN = TETile("▲", Color::GRAY, Color::BLACK, "mountain", 10);
inline const TETile TREE = TETile("♠", Color::GREEN, Color::BLACK, "tree", 11);

} // namespace Tileset
