#ifndef RUINEWALL_H
#define RUINEWALL_H
#include <gaven.h>
#include "../src/renderer.h"
#include "../src/primitives.h"
/**/
create_layer_phase(render_begin,4);
create_layer_phase(render,5);
create_layer_phase(overlay_render,7);
create_layer_phase(render_end,8);
#endif