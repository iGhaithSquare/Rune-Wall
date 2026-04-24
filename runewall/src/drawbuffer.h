#ifndef DRAWBUFFER_H
#define DRAWBUFFER_H
#include "renderer.h"
#include <stddef.h>
typedef struct sprite_object{
    sprite Sprite;
    short X;
    short Y;
    short Z;
}sprite_object;
typedef struct drawbuffer{
    sprite_object *Sprites;
    size_t Count;
    size_t Cap;
}drawbuffer;
drawbuffer* create_drawbuffer(void);
void drawbuffer_submit_sprite(drawbuffer* self,sprite Sprite, short X, short Y, short Z);
void drawbuffer_clear(drawbuffer* self);
void drawbuffer_sort(drawbuffer* self);
void destroy_drawbuffer(drawbuffer* self);
#endif