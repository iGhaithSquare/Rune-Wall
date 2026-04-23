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
    for(int y =0;y<self->Height;y++){
        fwrite(&self->Frame_Data[y*self->Width],1,self->Width,stdout);
        putchar('\n');
    }
}