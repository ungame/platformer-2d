#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>

const int LEVEL_HEIGHT = 11;
const int TILE_SIZE = 64;
const char* WINDOW_TITLE = "PLATFORMER 2D";

const std::string LEVEL_MAP[LEVEL_HEIGHT] = {
"                                      ",
"                                      ",
"   P                                  ",
"                                      ",
"                                      ",
"                                      ",
"                                      ",
"                                      ",
"   TTT       T                        ",
"            TT      T                T",
" TTTTTTTTTTTTT TTTTTTTTTTT TTTTTTTTT  "
};

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = sizeof(LEVEL_MAP) / sizeof(LEVEL_MAP[0]) * TILE_SIZE;

#endif