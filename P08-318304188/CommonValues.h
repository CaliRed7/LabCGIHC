#ifndef COMMONVALS
#define COMMONVALS
#include "stb_image.h"

const int MAX_POINT_LIGHTS = 3;
const int MAX_SPOT_LIGHTS = 4;
//valores que sirven para indicar cuantas luces puntuales y cuantas spotlight se van a usar (recordatorio de no usar m�s de 7 porque la octava es la luz direccional)
//como minimo 1 y m�ximo 7 (cada una)
//declararlos tambi�n en shader_light.frag
#endif