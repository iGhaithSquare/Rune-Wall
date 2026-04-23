#ifndef RENDERER_H
#define RENDERER_H
typedef struct renderer renderer;
renderer *create_runewall(short width,short height);
void set_console_size(short Width,short Height);
void destroy_runewall(renderer* self);
#endif