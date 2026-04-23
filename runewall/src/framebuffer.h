#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
typedef struct framebuffer framebuffer;
framebuffer *create_framebuffer(short Width,short Height);
void destroy_framebuffer(framebuffer* self);
#endif