
#ifndef __UI_SDLGL_H
#define __UI_SDLGL_H

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include "mxml.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_thread.h"
#include "SDL_opengl.h"
#include "SDL_joystick.h"

#include "dreamchess.h"
#include "history.h"
#include "ui.h"
#include "dir.h"
#include "credits.h"
#include "ui_sdlgl_3d.h"
#include "fen.h"
#include <gamegui.h>

#define GAME_TYPE_HUMAN_VS_CPU      0
#define GAME_TYPE_CPU_VS_HUMAN      1
#define GAME_TYPE_HUMAN_VS_HUMAN    2

#define MOVE_SPEED                  (60 / get_fps())

#define LEFT (1 << 0)
#define RIGHT (1 << 1)
#define UP (1 << 2)
#define DOWN (1 << 3)

/* Define our booleans */
#define TRUE  1
#define FALSE 0

#define FADE_SPEED  0.5f
#define FADE_OUT    0
#define FADE_IN     1

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/** Desired frames per second. */
#define FPS 9999

/* Speed that text types, characters per second. */
#define STRING_TYPE_SPEED 20

/** Bouncy text amplitude. */
#define BOUNCE_AMP 2
/** Bouncy text wave length in characters. */
#define BOUNCE_LEN 10
/** Bouncy text speed in bounces per second. */
#define BOUNCE_SPEED 3

/** Focussed image scale value. */
#define IMAGE_SCALE -0.3f
/** Focussed image enlargement speed in enlargements per second. */
#define IMAGE_SPEED 2.0f

#ifdef _arch_dreamcast
#define AXIS_CURSOR_DISABLED
#define AXIS_VIEW_X 0
#define AXIS_VIEW_Y 1
#else
#define AXIS_CURSOR_X 0
#define AXIS_CURSOR_Y 1
#define AXIS_VIEW_X 2
#define AXIS_VIEW_Y 3
#endif

#define DC_PI 3.14159265358979323846

#define GUI_PIECE_PAWN     0
#define GUI_PIECE_ROOK     3
#define GUI_PIECE_BISHOP   2
#define GUI_PIECE_KNIGHT   1
#define GUI_PIECE_QUEEN    4
#define GUI_PIECE_KING     5
#define GUI_PIECE_AVATAR   6

typedef struct theme
{
    char name[25];
    char style[25];
    char pieces[25];
    char board[25];
    char white_name[25];
    char black_name[25];
    char piece_tex_spin;
    int piece_tex_spin_speed;
    char lighting;
}
theme;

/** Describes a texture. The OpenGL texture ID is paired with texture
 *  coordinates to allow for only a small portion of the image to be used.
 */
typedef struct texture
{
    /** OpenGL Texture ID. */
    GLuint id;

    /** Upper-left u-coordinate. Ranges from 0.0f to 1.0f. */
    float u1;

    /** Upper-left v-coordinate. Ranges from 0.0f to 1.0f. */
    float v1;

    /** Lower-right u-coordinate. Ranges from 0.0f to 1.0f. */
    float u2;

    /** Lower-right v-coordinate. Ranges from 0.0f to 1.0f. */
    float v2;

    /** Width of texture in pixels. */
    int width;

    /** Height of texture in pixels. */
    int height;
}
texture_t;

/* dialogs */
gg_dialog_t *dialog_saveload_create(gg_dialog_t *parent, int saving);
gg_dialog_t *dialog_system_create();
gg_dialog_t *dialog_quit_create(gg_dialog_t *parent);
gg_dialog_t *dialog_ingame_create(gg_dialog_t *parent);
gg_dialog_t *dialog_message_create(char *message);
gg_dialog_t *dialog_promote_create(int colour);
gg_dialog_t *dialog_victory_create(result_t *result);

/* title_dialog.c */
void set_selected_player_layout( int set );
void set_selected_difficulty( int set );
gg_dialog_t *dialog_title_root_create();
gg_dialog_t *dialog_title_create(gg_dialog_t *parent);
gg_dialog_t *dialog_title_custom_create(gg_dialog_t *parent);
int get_cur_style();
int get_pieces_list_cur();
int get_board_list_cur();
void open_title_root_dialog();

/* transitions.c */
void set_fade_start( float start );

/* xmlsavefile.c */
void load_save_xml( int slot, char *desc, int *player_layout, int *difficulty );
void write_save_xml( int slot, char *desc );
int get_slots();
void set_slots( int slots );
char *get_time_save( int index );
config_t *get_config_save( int index );
board_t *get_saved_board( int index );

/* gamegui_driver.c */
gg_event_t convert_event(SDL_Event *event);
gg_driver_t *get_gg_driver_sdlgl();

/* ui_sdlgl_3d.h */
void start_piece_move( int source, int dest );
int get_piece_moving_done();

/* load_data.c */
void load_pieces();
void load_border(texture_t border[9], char *filename);
void unload_border(texture_t border[9]);

/* get_move.c */
int get_move();

/* transitions.c */
int get_fading_out();
int draw_fade( int inout );

/* ingame_ui.c */
void draw_name_dialog( float xpos, float ypos, char* name, int left, int white );
void draw_move_list( gg_colour_t *col_normal, gg_colour_t *col_high );
void draw_capture_list(gg_colour_t *col);
void draw_health_bars();
void draw_backdrop();

/* theme.c */
theme *get_theme( int index );
void load_theme(char* style, char* pieces, char *board);
texture_t *get_white_pieces();
texture_t *get_black_pieces();
texture_t *get_white_piece( int index );
texture_t *get_black_piece( int index );
texture_t *get_backdrop();
char *get_white_name();
char *get_black_name();
texture_t *get_mouse_cursor();
void load_theme_xml( char *xmlfile );
texture_t *get_menu_border();
texture_t *get_border();
void unload_theme();
void load_opaque(mxml_node_t *top, char *name, char *dest);
void set_selected_theme( int index );
int get_selected_theme();
int get_theme_count();
void set_theme_count( int count );

/* draw_scene.c */
void draw_scene( board_t *b );
float get_mouse_square();

/* credits.c */
void draw_credits(int init);

/* ui_driver.c */
int get_turn_counter();
gg_dialog_style_t *get_ingame_style();
gg_dialog_style_t *get_menu_style();
int get_white_in_check();
int get_black_in_check();
void set_switch_to_menu(int sw);
board_t *get_board();
int get_fading_out();
config_t *get_config();
void set_pgn_slot( int slot );
void set_quit_to_menu( int menu );
void set_set_loading( int set );
void set_title_process_retval( int ret );
void set_dialog_promote_piece( int piece );
int get_dialog_promote_piece();
int get_num_style();
char *get_themelist( int index );
char *get_stylelist( int index );
char *get_pieces_list( int index );
char *get_board_list( int index );
int get_pieces_list_total();
int get_board_list_total();

/* vkeyboard.c*/
gg_dialog_t *dialog_vkeyboard_create();
void toggle_vkeyboard_enabled();
int get_vkeyboard_enabled();
void populate_key_table();

/* system.c */
void go_3d(int width, int height);
void resize_window( int width, int height );
void set_mouse_pos( int x, int y );
int get_mouse_x();
int get_mouse_y();
float get_zerodepth();
void gl_swap();
void toggle_show_fps();
void init_gl();
float get_fps();
void update_fps_time();
int power_of_two(int input);
float get_dc_z();
void reset_dc_z();

/* texture.c */
texture_t SDL_GL_LoadTexture(SDL_Surface *surface, SDL_Rect *area, int alpha);
void draw_texture_uv( texture_t *texture, float xpos, float ypos, float width, float height, 
    float zpos, gg_colour_t *col, float u1, float v1, float u2, float v2, GLenum mode_h, GLenum mode_v);
void draw_texture( texture_t *texture, float xpos,float ypos, float width, float height, 
    float zpos, gg_colour_t *col );
void load_texture_png( texture_t *texture, char *filename, int alpha );

/* draw_shape.c */
void draw_rect(int x, int y, int w, int h, gg_colour_t *col);
void draw_rect_fill_gradient(int x, int y, int w, int h, gg_colour_t *top_left, gg_colour_t *top_right,
    gg_colour_t *bottom_left, gg_colour_t *bottom_right);
void draw_rect_fill(int x, int y, int w, int h, gg_colour_t *col);
void draw_tri(int x1, int y1, int x2, int y2, int x3, int y3, gg_colour_t *col);

/* text.c */
int text_draw_char( float xpos, float ypos, float scale, int character, gg_colour_t *col );
void text_draw_string( float xpos, float ypos, char *text, float scale, gg_colour_t *col);
void text_draw_string_right( float xpos, float ypos, char *text, float scale, gg_colour_t *col);
void text_draw_string_bouncy( float xpos, float ypos, char *text, float scale, gg_colour_t *col);
texture_t *get_text_character( int index );
void generate_text_chars();
int text_width(char *text);
int text_height();

/* colours.c */
#define COL_BLACK   0
#define COL_WHITE   1
#define COL_RED     2
#define COL_YELLOW  3

gg_colour_t *get_col( int colour );

#define SAVEGAME_SLOTS 15

#endif /* __UI_SDLGL_H */
