#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "renderer.h"
typedef struct framebuffer framebuffer;
framebuffer *create_framebuffer(short Width,short Height);
void destroy_framebuffer(framebuffer* self);
void framebuffer_newframe(framebuffer* self);
void framebuffer_output_data(framebuffer* self);
void framebuffer_draw_sprite(framebuffer* self,sprite *Sprite, short X, short Y);
#endif