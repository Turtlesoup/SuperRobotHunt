#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

//texture atlas
extern const std::string TEXTURE_ATLAS_SPRITES;

//sprites
extern const std::string SPRITE_PLAYER;
extern const std::string SPRITE_CIRCLE_FLASH;
extern const std::string SPRITE_GAUSSIAN;
extern const std::string SPRITE_TILES;
extern const std::string SPRITE_EXPLOSION;

extern const std::string SPRITE_COLLECTABLE_1;
extern const std::string SPRITE_COLLECTABLE_2;
extern const std::string SPRITE_COLLECTABLE_3;
extern const std::string SPRITE_COLLECTABLE_4;

extern const std::string SPRITE_MENU_BACKGROUND;

//gui
extern const std::string GUI_JSON_OPTIONS_POPUP;
extern const std::string GUI_JSON_MENU_POPUP;
extern const std::string GUI_JSON_ARE_YOU_SURE_POPUP;
extern const std::string GUI_JSON_GAME_OVER_PANEL;
extern const std::string GUI_JSON_TITLE_PANEL;

//gui widgets
extern const std::string SPRITE_BACKGROUND_PANEL;
extern const std::string SPRITE_BUTTON;
extern const std::string SPRITE_HEALTH_BAR_SEGMENT;
extern const std::string SPRITE_HEALTH_BAR_SEGMENT_EMPTY;

//fonts
extern const std::string FONT_PNG;
extern const std::string FONT_FNT;

//data
extern const std::string ENEMY_TYPES_DATA;
extern const std::string WAVE_DATA;
extern const std::string MAP_DATA;
extern const std::string BULLET_TYPES_DATA;

//sounds
extern const std::string AUDIO_BUTTON_RELEASED;

extern const std::string AUDIO_COLLECT_HEALTH;
extern const std::string AUDIO_COLLECT_SMALL_GEM;
extern const std::string AUDIO_COLLECT_GEM;
extern const std::string AUDIO_COLLECT_WEAPON;

extern const std::string AUDIO_PLAYER_HIT;

extern const std::string AUDIO_GAME_START;
extern const std::string AUDIO_GAME_OVER;
extern const std::string AUDIO_GAME_PAUSED;

//music

extern const std::string MUSIC_GAME;
extern const std::string MUSIC_MENU;

#endif