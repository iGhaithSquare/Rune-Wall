#ifndef RENDERER_H
#define RENDERER_H
typedef struct renderer renderer;
typedef struct sprite{
    char *Data;
    short Width;
    short Height;
} sprite;

#ifndef RUNEWALL_API
#ifdef _WIN32
    #ifdef RUNEWALL_BUILD_DLL
        #define RUNEWALL_API __declspec(dllexport)
    #else
        #define RUNEWALL_API __declspec(dllimport)
    #endif
#else
    #define RUNEWALL_API __attribute__((visibility("default")))
#endif
#endif
RUNEWALL_API renderer *create_runewall(short width,short height);
RUNEWALL_API void set_console_size(short Width,short Height);
RUNEWALL_API void destroy_runewall(renderer* self);
RUNEWALL_API void runewall_start_render_frame(renderer* self);
RUNEWALL_API void runewall_end_render_frame(renderer* self);
RUNEWALL_API void set_renderer_offset(renderer* self,short X,short Y);

RUNEWALL_API sprite create_sprite(const char* Sprite, short Width, short Height);
RUNEWALL_API void draw_sprite(renderer* self,sprite Sprite, short X, short Y,short Z);
RUNEWALL_API void draw_overlay_sprite(renderer* self,sprite Sprite, short X, short Y,short Z);
RUNEWALL_API void destroy_sprite(sprite *s);
#endif