#include <stdint.h>
#include <stdio.h>
#include "gaven.h"
#include "framebuffer.h"
#include "renderer.h"
#include <stdlib.h>
#include "drawbuffer.h"
struct renderer{
    framebuffer *Frame_Buffer;
    drawbuffer *Draw_Buffer;
    drawbuffer *Draw_Overlay_Buffer;
};
#ifdef _WIN32
#include <windows.h>
#endif
void set_console_size(short Width,short Height){
    #ifdef _WIN32
    HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hIN = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modeOut,modeIn;
    modeOut=modeIn=0;
    COORD size;
    size.X=(SHORT)Width;
    size.Y=(SHORT)Height;
    SMALL_RECT rect = {0,0,Width-1,Height-1};
    GAVEN_ASSERT(SetConsoleWindowInfo(hOUT,TRUE,&rect),"Console windows size failed: %lu", GetLastError());
    GAVEN_ASSERT(SetConsoleScreenBufferSize(hOUT,size),"Screen buffer size failed: %lu", GetLastError());
    GetConsoleMode(hOUT,&modeOut);
    modeOut|=ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    GAVEN_ASSERT(SetConsoleMode(hOUT,modeOut),"Set console mode failed: %lu", GetLastError());
    GetConsoleMode(hIN,&modeIn);
    modeIn|=ENABLE_EXTENDED_FLAGS;
    modeIn&=~ENABLE_QUICK_EDIT_MODE;
    GAVEN_ASSERT(SetConsoleMode(hIN,modeIn),"Set console mode failed: %lu", GetLastError());

    #else
    printf("\033[8;%d;%dt",Height,Width);
    fflush(stdout);
    #endif
}
renderer *create_runewall(short width,short height){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    #endif
    set_console_size(width,height);
    renderer* Runewall = (renderer*)calloc(1,sizeof(renderer));
    Runewall->Frame_Buffer = create_framebuffer(width,height);
    Runewall->Draw_Buffer = create_drawbuffer();
    Runewall->Draw_Overlay_Buffer = create_drawbuffer();
    printf("\x1b[?1049h");
    printf("\x1b[?25l");
    return Runewall;
}
void destroy_runewall(renderer* self){
    if(!self) return;
    destroy_framebuffer(self->Frame_Buffer);
    destroy_drawbuffer(self->Draw_Buffer);
    destroy_drawbuffer(self->Draw_Overlay_Buffer);
    free(self);
}
void runewall_start_render_frame(renderer* self){
    framebuffer_newframe(self->Frame_Buffer);
    drawbuffer_clear(self->Draw_Buffer);
    drawbuffer_clear(self->Draw_Overlay_Buffer);
}
void runewall_end_render_frame(renderer* self){
    drawbuffer_sort(self->Draw_Buffer);
    drawbuffer_sort(self->Draw_Overlay_Buffer);
    for(size_t i=0;i<self->Draw_Buffer->Count;i++){
        sprite_object Sprite= self->Draw_Buffer->Sprites[i];
        framebuffer_draw_sprite(self->Frame_Buffer,Sprite.Sprite,Sprite.X,Sprite.Y);
    }
    for(size_t i=0;i<self->Draw_Overlay_Buffer->Count;i++){
        sprite_object Sprite= self->Draw_Overlay_Buffer->Sprites[i];
        framebuffer_draw_sprite(self->Frame_Buffer,Sprite.Sprite,Sprite.X,Sprite.Y);
    }
    printf("\x1b[H");
    framebuffer_output_data(self->Frame_Buffer);
    fflush(stdout);
}

sprite create_sprite(const char* Sprite, short Width, short Height){
    char *buffer = malloc(Width*Height+1);
    GAVEN_ASSERT(buffer,"Couldnt allocate memory for sprite text");
    memcpy(buffer,Sprite,Width*Height);
    buffer[Width*Height]='\0';
    sprite S = {
        .Data = buffer,
        .Width = Width,
        .Height = Height
    };
    return S;
}
void destroy_sprite(sprite *s){
    if(!s->Data) return;
    free(s->Data);
}

void draw_sprite(renderer* self,sprite Sprite, short X, short Y,short Z){
    drawbuffer_submit_sprite(self->Draw_Buffer,Sprite,X,Y,Z);
}
void draw_overlay_sprite(renderer* self,sprite Sprite, short X, short Y,short Z){
    drawbuffer_submit_sprite(self->Draw_Overlay_Buffer,Sprite,X,Y,Z);
}