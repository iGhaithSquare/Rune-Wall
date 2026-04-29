#include "framebuffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
struct framebuffer{
    short Width;
    short Height;
    char* Frame_Data;
};

framebuffer *create_framebuffer(short Width,short Height){
    framebuffer* fb = (framebuffer*)malloc(sizeof(framebuffer));
    fb->Width=Width;
    fb->Height=Height;
    fb->Frame_Data = malloc(Width*Height);
    memset(fb->Frame_Data,' ',Width*Height);
    return fb;
}
void destroy_framebuffer(framebuffer* self){
    if(!self) return;
    free(self->Frame_Data);
    free(self);
}
void framebuffer_newframe(framebuffer* self){
    memset(self->Frame_Data,' ',self->Width*self->Height);
}
void framebuffer_output_data(framebuffer* self){
    fwrite(self->Frame_Data,1,self->Width*self->Height,stdout);
}

void framebuffer_draw_sprite(framebuffer* self, sprite *Sprite, short X, short Y){
    if ((int)X + Sprite->Width <= 0 || X >= self->Width ||
        (int)Y + Sprite->Height <= 0 || Y >= self->Height)
        return;
    short start_x = 0;
    short start_y = 0;
    short end_x = Sprite->Width;
    short end_y = Sprite->Height;
    if (X < 0)
        start_x = -X;
    if (X + Sprite->Width > self->Width)
        end_x = self->Width - X;
    if (Y < 0)
        start_y = -Y;
    if (Y + Sprite->Height > self->Height)
        end_y = self->Height - Y;
    for (short sy = start_y; sy < end_y; sy++){
        const char* src_row = Sprite->Data + sy * Sprite->Width;
        char* dst_row = self->Frame_Data + (Y + sy) * self->Width;
        for (short sx = start_x; sx < end_x; sx++){
            char c = src_row[sx];
            if (c != ' ')
                dst_row[X + sx] = c;
        }
    }
}