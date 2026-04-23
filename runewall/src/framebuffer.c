#include "framebuffer.h"
#include <stdlib.h>
struct framebuffer{
    short Width;
    short Height;
};

framebuffer *create_framebuffer(short Width,short Height){
    framebuffer* fb = (framebuffer*)malloc(sizeof(framebuffer));
    fb->Width=Width;
    fb->Height=Height;
    return fb;
}
void destroy_framebuffer(framebuffer* self){
    free(self);
}