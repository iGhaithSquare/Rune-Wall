#include <gaven.h>
#include "primitives.h"
#include <stdlib.h>
#include <string.h>
sprite create_text(const char* Text,short length){
    size_t len =strlen(Text);
    if(len>length){
        char buffer[256];
        GAVEN_ASSERT(length<255,"Length bigger than the limit 255");
        GAVEN_ASSERT(length>2,"Length smaller than size limit 3");
        memcpy(buffer,Text,length-3);
        buffer[length-3]='.';
        buffer[length-2]='.';
        buffer[length-1]='.';
        buffer[length]='\0';
        return create_sprite(buffer,length,1);//this doesnt
    }
    return create_sprite(Text,len,1); //this works normal
}