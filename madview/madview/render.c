//      Este fichero es la clave. Aquí es donde utilizaremos OpenGL para renderizar la escena.
//  Es el fichero más importante, ya que todos los otros sólo sirven para preparar el sistema 
//para esto. Presta mucha atención



#include "opengl.h"             /*! Incluye cabeceras y definiciones de OpenGL */

#include "sys.h"                /*! Prototipos de funciones dependientes del sistema */

#include "init_sys.h"

#include "carga_tga.h"

#include "fuentes.h"

#include "timer.h"



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

double matriz_proyeccion_A[4][4];
double matriz_proyeccion_B[4][4];
double matriz_proyeccion_C[4][4];


unsigned int FPS = 0;



/*! Aquí almacenaremos las texturas temporalmente*/
char *textura_datos;

/*! Aquí llevaremos el número de texturas*/
GLuint textura;

/*! Un par de fuentes... */
FUENTE *fuentes[2];



/*! Cargamos texturas, convenio: las texturas en el directorio texturas*/

int carga_texturas(char *fichero)
{

    int tam_x, tam_y;

    glGenTextures(0, &textura);


    /* Carga textura 1 */
    textura_datos = (char *) CargaTGA(fichero, &tam_x, &tam_y);
    if (tam_x != tam_y)
        return -1;

    if (textura_datos == NULL) {
				
        return -1;
    }


    glBindTexture(GL_TEXTURE_2D, textura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,
                      GL_UNSIGNED_BYTE, textura_datos);
    free(textura_datos);

    return 0;
}

/*! Inicialización propia de OpenGL

Este código es un poco complejo...glMatrixMode srive para indicar que vamos a modificar la matriz de proyección.
glLoadIndentity() la resetea. Con gluPerspective lo que hacemos es indicar a OpenGL que vamos a utilizar perspectiva.
Esto hace que a medida que las cosas estén más lejos se van haciendo más pequeñas y tienden al centro. Esta perspectiva
hará que lo que veamos sea más realista. Además, los dos últimos parámetros sirven para indicar que el rango de visivilidad
va desde .1 a 100. Es decir, lo que esté situado a más de 100 unidades de la cámara no se verá
*/

int init_gl(void)
{

    /* Un poco de luz*/ 
    
    GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat LightPosition1[] = { 0.0f, 5.0f, 0.0f, 1.0f };
    
    /* Vamos a preparar las matrices de proyección */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat) config.SCREEN_SIZE_X /
                   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_A[0][0]);

    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat) config.SCREEN_SIZE_X /
                   (GLfloat) config.SCREEN_SIZE_Y, 0.0001f, 100000.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_B[0][0]);

    glLoadIdentity();
    glOrtho(0, config.SCREEN_SIZE_X, 0, config.SCREEN_SIZE_Y, -100, 100);
    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_C[0][0]);

    glLoadMatrixd(&matriz_proyeccion_A[0][0]);


    /* Ahora establecemos el color de fondo por defecto. Está en formato RGBA y lo ponemos a negro */

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    /* Estas 3 líneas habilitan del Buffer de profundidad */

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  	glEnable(GL_ALPHA_TEST);

    /* Esta función sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
       hacer un buen cálculo de la perspectiva perdiendo un poco de rendimiento */

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    /* Cargamos la textura */

    glEnable(GL_TEXTURE_2D);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    if (carga_texturas(&model->id_textura) != 0) {
        sys_msg("Las texturas no se ha podido cargar");
    } else
        fprintf(logs, "Texturas ok..\n");


    glShadeModel(GL_SMOOTH);    /* SMOOTH SHADING */

    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glLineWidth(6);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse1);	
    //glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);





    /* Creamos un par de fuentes */

    fuentes[0] = carga_fuente("fuentes/def.tga", 15, -6);
    if (fuentes[0] == NULL) {
        sys_msg("Error crítico cargando fuentes!");
        exit(-1);
    }

    fuentes[1] = carga_fuente("fuentes/agulon.tga", 16, -4);
    if (fuentes[1] == NULL) {
        sys_msg("Error crítico cargando fuentes!");
        exit(-1);
    }

    fprintf(logs, "Fuentes ok..\n");
    fprintf(logs, "OpenGL inicializado sin errores..\n");

    return 0;

}



/*! Aquí se hacer la renderización */

void gl_renderiza_escena(void)
{


    static float grados = 0;
    static float grados2 = 0;
    int j = 0;
    float view_x1, view_x2, view_x3, view_y1, view_y2, view_y3, view_z1,
        view_z2, view_z3;
    /* Auxiliar de cálculo */
    grados += 0.25f;
    grados2 += 0.5f;
    /* Reseteamos los buffers y la matriz de modelado */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Primero preparamos el estado de OpenGL */


    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(&matriz_proyeccion_A[0][0]);

//      gluLookAt(      camara[0][3],camara[1][3],camara[2][3],                 // Posición
//                              camara[0][3]+camara[0][2],camara[1][3]+camara[1][2],camara[2][3]+camara[2][2],          
//                                                                                                                              // Punto al que miramos
//                              camara[0][1],camara[1][1],camara[2][1]);                // Orientación Y

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -0.5f);
    glRotatef(grados, 0.0f, 1.0f, 0.0f);
    glRotatef(grados2, 1.0f, 0.0f, 0.0f);

	glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		glBegin(GL_LINES);
					glColor3f(1.0f,0.0f,0.0f);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(0.1f,0.0f,0.0f);
	
		glColor3f(0.0f,1.0f,0.0f);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(0.0f,0.1f,0.0f);

		glColor3f(0.0f,0.0f,1.0f);
			 glVertex3f(0.0f,0.0f,0.0f);
			 glVertex3f(0.0f,0.0f,10.1f);
	glEnd();
				glColor3f(1.0f,1.0f,1.0f);
	glEnable(GL_LIGHTING);	
  	glEnable(GL_TEXTURE_2D);


		

    glBindTexture(GL_TEXTURE_2D, textura);
    for (j = 0; j < model->n_caras; j++) {
        view_x1 = model->triangulos[j].vertices[0].x;
        view_y1 = model->triangulos[j].vertices[0].y;
        view_z1 = model->triangulos[j].vertices[0].z;

        view_x2 = model->triangulos[j].vertices[1].x;
        view_y2 = model->triangulos[j].vertices[1].y;
        view_z2 = model->triangulos[j].vertices[1].z;

        view_x3 = model->triangulos[j].vertices[2].x;
        view_y3 = model->triangulos[j].vertices[2].y;
        view_z3 = model->triangulos[j].vertices[2].z;


        glBegin(GL_TRIANGLES);

        glTexCoord2f(model->triangulos[j].vertices[0].u,
                     model->triangulos[j].vertices[0].v);

        glNormal3f(model->triangulos[j].vertices[0].Nx,
                   model->triangulos[j].vertices[0].Ny,
                   model->triangulos[j].vertices[0].Nz);
        glVertex3f(view_x1, view_y1, view_z1);


        glTexCoord2f(model->triangulos[j].vertices[1].u,
                     model->triangulos[j].vertices[1].v);

        glNormal3f(model->triangulos[j].vertices[1].Nx,
                   model->triangulos[j].vertices[1].Ny,
                   model->triangulos[j].vertices[1].Nz);
        glVertex3f(view_x2, view_y2, view_z2);


        glTexCoord2f(model->triangulos[j].vertices[2].u,
                     model->triangulos[j].vertices[2].v);

        glNormal3f(model->triangulos[j].vertices[2].Nx,
                   model->triangulos[j].vertices[2].Ny,
                   model->triangulos[j].vertices[2].Nz);
        glVertex3f(view_x3, view_y3, view_z3);

        glEnd();
    }



    /* Dibujado de las fuentes */

    /* Las fuentes se dibujan en primer plano y utilizando
       el canal ALPHA */

   	glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(&matriz_proyeccion_C[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_DEPTH_BUFFER_BIT);


    print(fuentes[1], 0.0f, config.SCREEN_SIZE_Y, .5f, "Rojo - Eje X     Verde-Eje Y   Azul-Eje Z");

    glLoadIdentity();

    FPS++;

    /* Llamamos a la función de intercambio de buffers */

    sys_swapbuffers();

}
