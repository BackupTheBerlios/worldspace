//	Este fichero es la clave. Aquí es donde utilizaremos OpenGL para renderizar la escena.
//  Es el fichero más importante, ya que todos los otros sólo sirven para preparar el sistema 
//para esto. Presta mucha atención



#include "opengl.h"					/*! Incluye cabeceras y definiciones de OpenGL*/
#include "sys.h"					/*! Prototipos de funciones dependientes del sistema */
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
float auxiliar_objeto[4][4];

double matriz_proyeccion_A[4][4];
double matriz_proyeccion_B[4][4];
double matriz_proyeccion_C[4][4];

unsigned char marcador[24]={"Esto es una mierda"};
unsigned int FPS=0;
extern float velocidad;

laser_struct disparo_laser;



/* Matriz de sprites de fondo del espacio */
lista_sprites_spc *sprites_spc;
unsigned int n_sprites_spc;

/* Lista de puntos de estrellas */

float *estrellas;
unsigned int n_estrellas;

/* Modelo de la nave */

modelo *nave1;


/*! Aquí almacenaremos las texturas temporalmente*/ 
char *textura_datos;				

/*! Aquí llevaremos el número de texturas*/
				
int n_texturas=6;
GLuint *textura;					

char *f_texturas[]={		"texturas/textura.tga",
											"texturas/textura2.tga",
											"texturas/planeta.tga",
											"texturas/cross.tga",
											"texturas/cross2.tga",
           									"texturas/laser.tga"};

/*! Un par de fuentes... */
FUENTE *fuentes[2];	



GLfloat LightAmbient1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat LightAmbient0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat LightPosition0[] = { 0.0f, 1.0f, 0.0f, 0.0f };




/*! Cargamos texturas, convenio: las texturas en el directorio texturas*/

int carga_texturas(void) {
    
    int tam_x,tam_y,i;

		textura=(GLuint)malloc(n_texturas*sizeof(GLuint));

    glGenTextures (n_texturas, textura);	


		for (i=0;i<n_texturas;i++) {
	    textura_datos=(char *)CargaTGA(f_texturas[i],&tam_x,&tam_y);
	    if (tam_x!=tam_y)
				return -1;
      if (textura_datos == NULL)  {
      	fprintf(logs, "Error al cargar %s\n",f_texturas[i]);
       	return -1;
  	  }
		
		glBindTexture (GL_TEXTURE_2D, textura[i]);

		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
		gluBuild2DMipmaps (GL_TEXTURE_2D, 4, tam_x, tam_y, GL_RGBA,
		     GL_UNSIGNED_BYTE, textura_datos);


		free(textura_datos);
	
    }
		
	
	return 0;
}


/* Inicializamos el espacio de fondo, y espacio de acción */

int init_espacio(void) {

	
  /* Cargamos la lista de sprites de espacio */

	if (!(carga_espacio("espacio1.txt"))) {
		fprintf(logs,"Fallé al crear del espacio\n");
		return -1;
	}
	/* Ahora se supone que en sprites_spc tenemos la lista completa
	de los sprites de espacio.*/

	if (!(crea_estrellas(10000))) {
			fprintf(logs,"Fallé al crear estrellas\n");
			return -1;
	}

	nave1=carga_mad("modelos/yodai.mad");
	if (nave1==NULL) {
			fprintf(logs,"Fallé al cargar modelos/nave.mad\n");
			return -1;
}		

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

  int i,j;
	
	/* Vamos a preparar las matrices de proyección */

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);
	
	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_A[0][0]);

	glLoadIdentity();
    gluPerspective(45.0f,
		   (GLfloat) config.SCREEN_SIZE_X /
		   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_B[0][0]);

	glLoadIdentity();
	glOrtho(0,config.SCREEN_SIZE_X,0,config.SCREEN_SIZE_Y,-100,100);					
	glGetDoublev(GL_PROJECTION_MATRIX,&matriz_proyeccion_C[0][0]);

	glLoadMatrixd(&matriz_proyeccion_A[0][0]);

	fprintf(logs,"Matrices de proyección creadas\n");



    /* Esto resetea la matriz de modelado y la de la camara*/


	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);	
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);	
   	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);	

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);	
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse0);	


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
	glEnable(GL_LIGHTING);
	

	
  /* Inicialización de la matriz camara */
  glGetFloatv(GL_MODELVIEW_MATRIX,&camara[0][0]);
	
	camara[2][2]=1.0f;
	camara[3][2]=-1.0f;


	fprintf(logs,"Camara inicializada\n");

    /* Ahora establecemos el color de fondo por defecto. Está en formato RGBA y lo ponemos a negro */

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
	/* Estas 3 líneas habilitan del Buffer de profundidad*/
	
	glClearDepth(1.0f);
    
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
	/* Esta función sirve para optimizar el renderizado, y se utiliza para muchas cosas. En este caso es para
	hacer un buen cálculo de la perspectiva perdiendo un poco de rendimiento*/

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
 	fprintf(logs,"Iniciando carga de texturas...\n");

	/* Cargamos la textura */

	glEnable(GL_TEXTURE_2D);
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	




  if (carga_texturas()!=0) {
		sys_msg("Las texturas no se ha podido cargar");
	}
	else 
		fprintf(logs,"Texturas cargadas..\n");
 

	glShadeModel(GL_FLAT);			/* SMOOTH SHADING */

  glEnable(GL_POINT_SMOOTH);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	glLineWidth(5.0f);
	glEnable(GL_LINE_SMOOTH);
	disparo_laser.ttl=0;
	
	/* Creamos un par de fuentes */

	fprintf(logs,"Cargando fuentes..\n");
	fuentes[0]=carga_fuente("fuentes/def.tga",15,-6);
	if (fuentes[0]==NULL) {
		sys_msg("Error crítico cargando fuentes!");
		exit (-1);
	}
	
    fuentes[1]=carga_fuente("fuentes/agulon.tga",16,-4);
	if (fuentes[1]==NULL) {
		sys_msg("Error crítico cargando fuentes!");
		exit (-1);
	}
   
	fprintf(logs,"Fuentes cargadas..\n");

	/* Creando el espacio de entorno */

  fprintf(logs,"Creando el espacio\n");
	if (!init_espacio()) {
		sys_msg("Error al crear espacio\n!");
		exit (-1);
	}

	fprintf(logs,"Fuentes cargadas..\n");
	
	

	fprintf(logs,"OpenGL inicializado sin errores críticos...\n");
	
				
	
	return 0;
	
}



/*! Aquí se hacer la renderización */

void gl_renderiza_escena(void) {



	static float grados=0;
	/* Auxiliar de cálculo */

	unsigned int aux,j;
	float aux2;
	float viewport[4];
	GLboolean visible;
	/* Reseteamos los buffers y la matriz de modelado */
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	
	
	
	/* Dibujamos el fondo */

	/* Primero preparamos el estado de OpenGL */
	

	
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&matriz_proyeccion_B[0][0]);
	
	gluLookAt(	camara[3][0],camara[3][1],camara[3][2],			// Posición
				camara[3][0]+camara[2][0],camara[3][1]+camara[2][1],camara[3][2]+camara[2][2],		
																// Punto al que miramos
				camara[1][0],camara[1][1],camara[1][2]);		// Orientación Y


	
	
	glMatrixMode(GL_MODELVIEW);
 	glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);

	glLoadIdentity();

	    	glDisable(GL_LIGHTING);

	for (aux=0;aux<n_estrellas;aux+=4) {
				glPointSize(estrellas[aux+3]);
		glBegin(GL_POINTS);

				glVertex3f(estrellas[aux],estrellas[aux+1],estrellas[aux+2]);
		glEnd();
	}

	glPointSize(4.0f);
  glEnable(GL_TEXTURE_2D);
  for (aux=0;aux<n_sprites_spc;aux++) {

		glLoadMatrixf(&sprites_spc[aux].matriz);
	  glBindTexture(GL_TEXTURE_2D, sprites_spc[aux].textura);
		aux2=sprites_spc[aux].tam_x;
		glBegin(GL_QUADS);
  	glTexCoord2f(1.0f, 1.0f); glVertex2f( aux2,  aux2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( aux2,  -aux2);
	  glTexCoord2f(0.0f, 0.0f); glVertex2f(-aux2,  -aux2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-aux2,  aux2);	
		glEnd();
  }

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
/* Dibujamos el laser */
    if (disparo_laser.ttl>0) {
        //glDisable(GL_TEXTURE_2D);
        memcpy(auxiliar_objeto,camara,sizeof(float)*16);
        auxiliar_objeto[3][0]=disparo_laser.posicion[0];
        auxiliar_objeto[3][1]=disparo_laser.posicion[1];
        auxiliar_objeto[3][2]=disparo_laser.posicion[2];
        glLoadMatrixf(&auxiliar_objeto);
        glBindTexture(GL_TEXTURE_2D, textura[5]);
        aux2=0.5f;
        glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex2f( aux2,  aux2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f( aux2,  -aux2);
	  glTexCoord2f(0.0f, 0.0f); glVertex2f(-aux2,  -aux2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(-aux2,  aux2);	
        glEnd();
       	glLoadIdentity();

    }

        
	

	/* Luces */	
	glEnable(GL_LIGHTING);
LightPosition1[0]=-camara[2][0];
LightPosition1[1]=-camara[2][1];
LightPosition1[2]=-camara[2][2];
LightPosition1[3]=0;
glLightfv(GL_LIGHT1, GL_POSITION, LightPosition1);	
	
	
	/* Comenzamos a dibujar la nave de marras */
  	

    glEnable(GL_TEXTURE_2D);


	auxiliar_objeto[0][0]=nave1->base[0].x;
	auxiliar_objeto[0][1]=nave1->base[0].y;
	auxiliar_objeto[0][2]=nave1->base[0].z;
	auxiliar_objeto[0][3]=0;

	auxiliar_objeto[1][0]=nave1->base[1].x;
	auxiliar_objeto[1][1]=nave1->base[1].y;
	auxiliar_objeto[1][2]=nave1->base[1].z;
	auxiliar_objeto[1][3]=0;

	auxiliar_objeto[2][0]=nave1->base[2].x;
	auxiliar_objeto[2][1]=nave1->base[2].y;
	auxiliar_objeto[2][2]=nave1->base[2].z;
	auxiliar_objeto[2][3]=0;

	auxiliar_objeto[3][0]=nave1->x;
	auxiliar_objeto[3][1]=nave1->y;
	auxiliar_objeto[3][2]=nave1->z;
	auxiliar_objeto[3][3]=1;





	glLoadMatrixf(&auxiliar_objeto);	

  glBindTexture(GL_TEXTURE_2D, nave1->n_textura);
    for (j = 0; j < nave1->n_caras; j++) {

        glBegin(GL_TRIANGLES);

        glTexCoord2f(nave1->triangulos[j].vertices[0].u,
                     nave1->triangulos[j].vertices[0].v);

        glNormal3f(nave1->triangulos[j].vertices[0].Nx,
                   nave1->triangulos[j].vertices[0].Ny,
                   nave1->triangulos[j].vertices[0].Nz);
        glVertex3f(nave1->triangulos[j].vertices[0].x,nave1->triangulos[j].vertices[0].y,nave1->triangulos[j].vertices[0].z);


        glTexCoord2f(nave1->triangulos[j].vertices[1].u,
                     nave1->triangulos[j].vertices[1].v);

        glNormal3f(nave1->triangulos[j].vertices[1].Nx,
                   nave1->triangulos[j].vertices[1].Ny,
                   nave1->triangulos[j].vertices[1].Nz);
        glVertex3f(nave1->triangulos[j].vertices[1].x,nave1->triangulos[j].vertices[1].y,nave1->triangulos[j].vertices[1].z);


        glTexCoord2f(nave1->triangulos[j].vertices[2].u,
                     nave1->triangulos[j].vertices[2].v);

        glNormal3f(nave1->triangulos[j].vertices[2].Nx,
                   nave1->triangulos[j].vertices[2].Ny,
                   nave1->triangulos[j].vertices[2].Nz);
        glVertex3f(nave1->triangulos[j].vertices[2].x,nave1->triangulos[j].vertices[2].y,nave1->triangulos[j].vertices[2].z);

        glEnd();
    }


 	glLoadIdentity();
 	glDisable(GL_LIGHTING);
  glRasterPos3f(nave1->x,nave1->y,nave1->z);
	glGetBooleanv( GL_CURRENT_RASTER_POSITION_VALID,&visible);
  glGetFloatv( GL_CURRENT_RASTER_POSITION,&viewport);
 	glLoadIdentity();


	/* Dibujado de las fuentes */
  	glDisable(GL_DEPTH_TEST);
	/* Las fuentes se dibujan en primer plano y utilizando
	el canal ALPHA */
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(&matriz_proyeccion_C[0][0]);

	glClear(GL_DEPTH_BUFFER_BIT);
glBindTexture(GL_TEXTURE_2D, textura[3]);
	

	/* CrossHair */
	/* Con la funcion glTexCoord2f mapeamos las coordenadas de la textura*/
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(config.SCREEN_SIZE_X/2-16.0f,config.SCREEN_SIZE_Y/2+16.0f);	
	glTexCoord2f(0.0f, 0.0f); glVertex2f(config.SCREEN_SIZE_X/2-16.0f,config.SCREEN_SIZE_Y/2-16.0f);	
	glTexCoord2f(1.0f, 0.0f); glVertex2f(config.SCREEN_SIZE_X/2+16.0f,config.SCREEN_SIZE_Y/2-16.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(config.SCREEN_SIZE_X/2+16.0f,config.SCREEN_SIZE_Y/2+16.0f);
	glEnd();

	/* Localizador */

if (visible) {
	glBindTexture(GL_TEXTURE_2D, textura[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(viewport[0]-16.0f,viewport[1]+16.0f);	
	glTexCoord2f(0.0f, 0.0f); glVertex2f(viewport[0]-16.0f,viewport[1]-16.0f);	
	glTexCoord2f(1.0f, 0.0f); glVertex2f(viewport[0]+16.0f,viewport[1]-16.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(viewport[0]+16.0f,viewport[1]+16.0f);
	glEnd();
}
	
	
	/* Calculamos e imprimimos los frames por segundo */


   print(fuentes[1],0.0f,config.SCREEN_SIZE_Y,.5f,"Velocidad %f",velocidad);



	/* Incrementamos el número de frames visualizados */	
  	FPS++;

	/* Llamamos a la función de intercambio de buffers*/

	
    sys_swapbuffers();

}
