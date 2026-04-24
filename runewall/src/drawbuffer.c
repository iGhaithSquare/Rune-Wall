#include "drawbuffer.h"
#include <stdlib.h>
#include <string.h>

drawbuffer* create_drawbuffer(void){
    drawbuffer* Buffer = (drawbuffer*)malloc(sizeof(drawbuffer));
    Buffer->Cap=0;
    Buffer->Count=0;
    Buffer->Sprites=NULL;
    return Buffer;
}
void drawbuffer_submit_sprite(drawbuffer* self,sprite Sprite, short X, short Y, short Z){
    if(self->Count>=self->Cap){
        self->Cap=(self->Cap)?self->Cap*2:256;
        sprite_object* temp = (sprite_object*)realloc(self->Sprites,sizeof(sprite_object)*self->Cap);
        self->Sprites=temp;
    }
    sprite_object Obj = {
        .Sprite=Sprite,
        .X=X,
        .Y=Y,
        .Z=Z
    };
    self->Sprites[self->Count++]=Obj;
}
int compare_z(const void* A,const void* B){
    const sprite_object* a =A;
    const sprite_object* b =B;
    return (a->Z>b->Z)-(a->Z<b->Z);
}
void drawbuffer_sort(drawbuffer* self){
    qsort(self->Sprites,self->Count,sizeof(sprite_object),compare_z);
}

void destroy_drawbuffer(drawbuffer* self){
    if(!self) return;
    free(self->Sprites);
    free(self);
}
void drawbuffer_clear(drawbuffer* self){
    self->Count=0;
}