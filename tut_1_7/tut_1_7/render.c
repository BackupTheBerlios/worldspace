//	Este fichero es la clave. Aquí es donde utilizaremos OpenGL para renderizar la escena.
//  Es el fichero más importante, ya que todos los otros sólo sirven para preparar el sistema 
//para esto. Presta mucha atención



#include "opengl.h"					/*! Incluye cabeceras y definiciones de OpenGL*/
#include "estructuras.h"
#include "sys_data.h"

#include <stdlib.h>


/*!         |
      			| Y+
			      |
      			|
      			|
X+	--------o
      	   /
      	  /
      	 / Z+

*/
/* Esta matriz esta en modo Vx,Vy,Vz,O, y define la posicion y orientación de la cámara */


float camara[4][4];
float auxiliar_objeto[4][4];
double matriz_proyeccion_A[4][4];

modelo *modelo_1;




GLfloat LightAmbient0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat LightPosition0[] = { 0.0f, 1.0f, 0.0f, 0.0f };




/*! Inicialización propia de OpenGL

Este código es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyección.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas estén más lejos se van haciendo más pequeñas y tienden al centro. Esta perspectiva
hará que lo que veamos sea más realista. Además, los dos últimos parámetros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que esté situado a más de 100 unidades de la cámara no se verá
*/

int inicializa_gl(void)
{


	
	/* Vamos a preparar las matrices de proyección */

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);
	
	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_A[0][0]);



    /* Esto resetea la matriz de modelado y la de la camara*/


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

  /* Configuración de las luces e inicialización */

  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);	
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);	
 	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);	
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
	

	
  /* Inicialización de la matriz camara */

  glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
	
	camara[2][2]=1.0f;
	camara[3][2]=-1.0f;



  /* Ahora establecemos el color de fondo por defecto. Está en formato RGBA y lo ponemos a negro */

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
	/* Estas 3 líneas habilitan del Buffer de profundidad*/
	
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* Activación del blending */

  glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	/* Esta función sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
	hacer un buen cálculo de la perspectiva perdiendo un poco de rendimiento*/

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    

  /* Smooth shading */
	glShadeModel(GL_SMOOTH);

  /* Puntos difusos */

  glEnable(GL_POINT_SMOOTH);

  /* Cull faces - Las caras traseras se ignoran */

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	
				
	
	return 0;
	
}


