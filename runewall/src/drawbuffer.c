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
    sprite* Sprite_Cpy = (sprite*)malloc(sizeof(sprite));
    Sprite_Cpy->Height=Sprite.Height;
    Sprite_Cpy->Width=Sprite.Width;
    Sprite_Cpy->Data=malloc(Sprite.Width*Sprite.Height+1);
    memcpy(Sprite_Cpy->Data,Sprite.Data,Sprite.Height*Sprite.Width);
    Sprite_Cpy->Data[Sprite.Width*Sprite.Height]='\0';
    sprite_object Obj = {
        .Sprite=Sprite_Cpy,
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
    for(size_t i=0;i<self->Count;i++){
        free(self->Sprites[i].Sprite->Data);
        free(self->Sprites[i].Sprite);
    }
    free(self->Sprites);
    free(self);
}
void drawbuffer_clear(drawbuffer* self){
    for(size_t i=0;i<self->Count;i++){
        free(self->Sprites[i].Sprite->Data);
        free(self->Sprites[i].Sprite);
    }
    self->Count=0;
}