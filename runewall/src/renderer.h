#ifndef RENDERER_H
#define RENDERER_H
typedef struct renderer renderer;
typedef struct sprite{
    char *Data;
    short Width;
    short Height;
} sprite;
renderer *create_runewall(short width,short height);
void set_console_size(short Width,short Height);
void destroy_runewall(renderer* self);
void runewall_start_render_frame(renderer* self);
void runewall_end_render_frame(renderer* self);
void set_renderer_offset(renderer* self,short X,short Y);

sprite create_sprite(const char* Sprite, short Width, short Height);
void draw_sprite(renderer* self,sprite Sprite, short X, short Y,short Z);
void draw_overlay_sprite(renderer* self,sprite Sprite, short X, short Y,short Z);
void destroy_sprite(sprite *s);
#endif