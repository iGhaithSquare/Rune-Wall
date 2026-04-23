#ifndef RENDERER_H
#define RENDERER_H
typedef struct renderer renderer;
renderer *create_runewall(short width,short height);
void set_console_size(short Width,short Height);
void destroy_runewall(renderer* self);
void runewall_start_render_frame(renderer* self);
void runewall_end_render_frame(renderer* self);
#endif