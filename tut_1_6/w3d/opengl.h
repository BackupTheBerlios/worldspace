// Inclusión de cabeceras OpenGL

/*!
Este fichero se utiliza para incluir las cabeceras opengl.
Como se ve, dependiendo del sistema, las cabeceras están
en un sitio u otro
El preprocesador del lcc y el Visual C define la variable _WIN32. Entonces solo lee el código
entre ifdef _WIN32 y endif.
El makefile de Linux define la variable LINUX, leyendo el compilador de Linux la otra parte
*/

#ifdef _WIN32W3D							// Para windows
#include <windows.h>
#endif


#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>



#ifndef _OGLMAX
#define _OGLMAX

#define GL_PI 3.1415f

typedef struct XYZ_tag {
    float x;
	float y;
	float z;
} XYZ;
#endif


