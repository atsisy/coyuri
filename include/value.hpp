#ifndef VALUE_HPP
#define VALUE_HPP

#include <vector>
#include <functional>
#include <FL/Fl_PNG_Image.H>
#include "type.hpp"

extern Fl_PNG_Image *images[30];
extern std::vector<Point> (*wcm_ftable[])(Point point);
extern KOMA_TYPE main_ban[9][9];
extern Point TARGET_KOMA;
extern Fl_Box *target_ban[9][9];
extern Masu *visual_ban[9][9];
extern Fl_Box *message;
extern std::vector<KOMA_TYPE> AI_TEGOMA;
extern std::vector<KOMA_TYPE> PLAYER_TEGOMA;
extern Tegoma *player_tegomas[38];
extern Tegoma *ai_tegomas[38];
extern KOMA_TYPE UTSU;

#endif
