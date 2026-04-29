#include "runewall.h"
#include <stdlib.h>

typedef struct main_layer_data{
    renderer* RuneWall;
}main_layer_data;
void main_layer_ondetach(layer* self){
    main_layer_data* data = (main_layer_data*)self->LayerData;
    destroy_runewall(data->RuneWall);
}
void main_layer_polling_callback(layer* self,void* ctx){
    
    /* the polling stuff */
    return;
}
/* only do this once in your application*/
void main_layer_rendering_start_callback(layer* self,void *ctx){
    main_layer_data* data = (main_layer_data*)self->LayerData;
    runewall_start_render_frame(data->RuneWall);
}
void main_layer_rendering_callback(layer* self,void *ctx){
    main_layer_data* data = (main_layer_data*)self->LayerData;
    sprite example =create_sprite("abcdefghijklmnop",4,4);
    draw_sprite(data->RuneWall,example,4,0,2);
    destroy_sprite(&example);
}
void main_layer_overlay_rendering_callback(layer* self,void *ctx){
    main_layer_data* data = (main_layer_data*)self->LayerData;
    sprite text = create_text("||||||||||||||||||||||||",16);
    draw_overlay_sprite(data->RuneWall,text,0,0,0);
    destroy_sprite(&text);
}
/* only do this once in your application*/
void main_layer_rendering_end_callback(layer* self,void *ctx){
    main_layer_data* data = (main_layer_data*)self->LayerData;
    runewall_end_render_frame(data->RuneWall);
}
layer* create_main_layer(const char *name){
    layer* main_layer = calloc(1,sizeof(layer));
    main_layer->Name=name;
    bind_layer_phase(main_layer,layer_phase_polling,main_layer_polling_callback);
    bind_layer_phase(main_layer,layer_phase_render_begin,main_layer_rendering_start_callback);
    bind_layer_phase(main_layer,layer_phase_render,main_layer_rendering_callback);
    bind_layer_phase(main_layer,layer_phase_overlay_render,main_layer_overlay_rendering_callback);
    bind_layer_phase(main_layer,layer_phase_render_end,main_layer_rendering_end_callback);
    main_layer_data* Data = (main_layer_data*)calloc(1,sizeof(main_layer_data));
    Data->RuneWall = create_runewall(80,24);
    set_renderer_offset(Data->RuneWall,20,5);
    main_layer->LayerData=Data;
    return main_layer;
}
/* Using the prebuilt Gaven Main workflow */
application* gaven_main(int argc, char** argv){
    /* We create the application*/
    application* app = create_gaven_application();
    /* Create main layer */
    layer* main_layer = create_main_layer("Main Layer");
    add_layer(app->Layer_Registry,main_layer);
    /* We return the application*/
    return app;
}