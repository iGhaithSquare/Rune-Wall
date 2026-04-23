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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size;
    size.X=(SHORT)Width;
    size.Y=(SHORT)Height;
    SMALL_RECT rect = {0,0,Width-1,Height-1};
    GAVEN_ASSERT(SetConsoleWindowInfo(hConsole,TRUE,&rect),"Console windows size failed: %lu", GetLastError());
    GAVEN_ASSERT(SetConsoleScreenBufferSize(hConsole,size),"Screem buffer size failed: %lu", GetLastError());
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
    return Runewall;
}
void destroy_runewall(renderer* self){
    if(!self) return;
    destroy_framebuffer(self->Frame_Buffer);
    free(self);
}