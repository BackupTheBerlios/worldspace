//	Este fichero es la clave. Aqu� es donde utilizaremos OpenGL para renderizar la escena.
//  Es el fichero m�s importante, ya que todos los otros s�lo sirven para preparar el sistema 
//para esto. Presta mucha atenci�n



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
/* Esta matriz esta en modo Vx,Vy,Vz,O, y define la posicion y orientaci�n de la c�mara */


float camara[4][4];
float auxiliar_objeto[4][4];
double matriz_proyeccion_A[4][4];

modelo *modelo_1;




GLfloat LightAmbient0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat LightPosition0[] = { 0.0f, 1.0f, 0.0f, 0.0f };




/*! Inicializaci�n propia de OpenGL

Este c�digo es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyecci�n.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas est�n m�s lejos se van haciendo m�s peque�as y tienden al centro. Esta perspectiva
har� que lo que veamos sea m�s realista. Adem�s, los dos �ltimos par�metros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que est� situado a m�s de 100 unidades de la c�mara no se ver�
*/

int inicializa_gl(void)
{


	
	/* Vamos a preparar las matrices de proyecci�n */

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);
	
	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_A[0][0]);



    /* Esto resetea la matriz de modelado y la de la camara*/


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

  /* Configuraci�n de las luces e inicializaci�n */

  glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);	
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);	
 	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);	
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
	

	
  /* Inicializaci�n de la matriz camara */

  glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
	
	camara[2][2]=1.0f;
	camara[3][2]=-1.0f;



  /* Ahora establecemos el color de fondo por defecto. Est� en formato RGBA y lo ponemos a negro */

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
	/* Estas 3 l�neas habilitan del Buffer de profundidad*/
	
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	/* Activaci�n del blending */

  glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	/* Esta funci�n sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
	hacer un buen c�lculo de la perspectiva perdiendo un poco de rendimiento*/

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


