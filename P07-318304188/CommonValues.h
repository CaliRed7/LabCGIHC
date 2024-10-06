#ifndef COMMONVALS
#define COMMONVALS
#include "stb_image.h"

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 4;
//valores que sirven para indicar cuantas luces puntuales y cuantas spotlight se van a usar (recordatorio de no usar más de 7 porque la octava es la luz direccional)
//como minimo 1 y máximo 7 (cada una)
//declararlos también en shader_light.frag
#endif