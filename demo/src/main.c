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
layer* create_main_layer(const char *name){
    layer* main_layer = calloc(1,sizeof(layer*));
    main_layer->Name=name;
    bind_layer_phase(main_layer,layer_phase_polling,main_layer_polling_callback,NULL);
    main_layer_data* Data = (main_layer_data*)calloc(1,sizeof(main_layer_data));
    Data->RuneWall = create_runewall(80,24);
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
    /* User Specific Code */
    GAVEN_PRINT_COLOR(GAVEN_RED,"▒a");
    /* We return the application*/
    return app;
}