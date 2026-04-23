#include <stdint.h>
#include <stdio.h>
#include "gaven.h"
#include "framebuffer.h"
#include "renderer.h"
#include <stdlib.h>
struct renderer{
    framebuffer * Frame_Buffer;
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
    printf("\x1b[?1049h");
    printf("\x1b[?25l");
    return Runewall;
}
void destroy_runewall(renderer* self){
    if(!self) return;
    destroy_framebuffer(self->Frame_Buffer);
    free(self);
}
void runewall_start_render_frame(renderer* self){
    framebuffer_newframe(self->Frame_Buffer);
}
void runewall_end_render_frame(renderer* self){
    printf("\x1b[H");
    framebuffer_output_data(self->Frame_Buffer);
    fflush(stdout);
}