/***************************************************************************
                          engine.c  -  description
                             -------------------
    begin                : sáb ene 18 2003
    copyright            : (C) 2003 by neuralgya
    email                : neuralgya@users.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "../opengl.h"
#include "../global.h"
#include "estructuras.h"
#include "../gfx/fuentes.h"

#include "espacio.h"
#include "texturas.h"
#include <math.h>


GLfloat LightAmbient1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition1[] = { 0.0f, 0.0f, 0.0f, 1.0f };

GLfloat LightAmbient0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightDiffuse0[] = { 0.9f, 0.9f, 0.9f, 1.0f };
GLfloat LightPosition0[] = { 0.0f, 1.0f, 0.0f, 0.0f };


double matriz_proyeccion_A[4][4];
double matriz_proyeccion_B[4][4];
double matriz_proyeccion_C[4][4];

float camara[4][4];

float intervalo;

extern GLuint *matriz_texturas;

extern float velocidad;

int id_textura_crosshair;
int id_textura_localizador;


/* Matriz de sprites de fondo del espacio */
lista_sprites_spc *sprites_spc;
unsigned int n_sprites_spc;

/* Lista de puntos de estrellas */

float *estrellas;
unsigned int n_estrellas;

/* Lista de puntos del polvo espacial */
float *polvo_espacial;          /* Nada de connotaciones pornográficas eh? */
unsigned int n_polvo_espacial;

modelo *nave;


int init_espacio(void)
{


    /* Cargamos la lista de sprites de espacio */

    if (!(carga_espacio("espacio1.txt"))) {
        _sis_msj("\t\tError cargando espacio[KO]");
        return NO;
    }
    /* Ahora se supone que en sprites_spc tenemos la lista completa
       de los sprites de espacio. */

    if (!(crea_estrellas(10000))) {
        _sis_msj("\n\t\tFallé al crear estrellas [KO]");
        return NO;
    }

    if (!(crea_polvo_espacial(50))) {
        _sis_msj("\n\t\tFallé al crear polvo_espacial [KO]");
        return NO;
    }

    nave = carga_mad("yodai.mad");


    return SI;
}


int init_engine()
{

    SDL_ShowCursor(0);
    SDL_WM_GrabInput(SDL_GRAB_ON);
    gl_basic_ini(NO);

    if (init_espacio()) {
        _sis_msj("\n[OK]\t\tEspacio inicializado");
    } else
        return NO;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat) config.SCREEN_SIZE_X /
                   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_A[0][0]);

    glLoadIdentity();
    gluPerspective(45.0f,
                   (GLfloat) config.SCREEN_SIZE_X /
                   (GLfloat) config.SCREEN_SIZE_Y, 0.01f, 100000.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_B[0][0]);

    glLoadIdentity();
    glOrtho(0, config.SCREEN_SIZE_X, 0, config.SCREEN_SIZE_Y, -100, 100);
    glGetDoublev(GL_PROJECTION_MATRIX, &matriz_proyeccion_C[0][0]);

    glLoadMatrixd(&matriz_proyeccion_A[0][0]);

    _sis_msj("\n\t\t[OK]Matrices de proyección creadas");

    glGetFloatv(GL_MODELVIEW_MATRIX, &camara[0][0]);
    camara[2][2] = 1.0f;
    camara[3][0] = ((rand() % 100) - 50);
    camara[3][1] = ((rand() % 100) - 50);
    camara[3][2] = ((rand() % 100) - 50);


    id_textura_crosshair = encola_textura("crosshair.tga", GL_RGBA);
    id_textura_localizador = encola_textura("localizador.tga", GL_RGBA);

    if (!genera_texturas(GL_LINEAR)) {
        _sis_msj("\n\t\t\tError generando texturas [KO]");
        return NO;
    } else
        _sis_msj("\n[OK]\t\t\tTexturas Generadas");

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse0);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse0);


    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);




    return SI;
}

int renderiza_escena()
{

    int aux;
    float aux2, aux3;
    float Px, Py, Pz, Vx, Vy, Vz, Ox, Oy, Oz, Gx, Gy, Gz, multiplicador,
        modulo;

    GLboolean visible;
    float viewport[4];



    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Dibujamos el fondo */

    /* Primero preparamos el estado de OpenGL */

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, config.SCREEN_SIZE_X / config.SCREEN_SIZE_Y, 0.1, 100.0);      // Do the perspective calculations. Last value = max clipping depth

    glLoadMatrixd(&matriz_proyeccion_B[0][0]);
    gluLookAt(0, 0, 0, camara[2][0], camara[2][1], camara[2][2],        // Punto al que miramos
              camara[1][0], camara[1][1], camara[1][2]);        // Orientación Y



    glDisable(GL_CULL_FACE);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glLoadIdentity();
    glDisable(GL_LIGHTING);


    /* Dibujamos Sky-Boxes */
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[0].textura]);      // Bind the Texture to the object
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.01, -1.01, 1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.005, -1.005, 1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.005, 1.005, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.005, 1.005, 1.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[1].textura]);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.005, -1.005, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.005, 1.005, -1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.005, 1.005, -1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.005, -1.005, -1.0);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[2].textura]);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.005, 1.0, -1.005);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.005, 1.0, 1.005);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.005, 1.0, 1.005);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.005, 1.0, -1.005);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[3].textura]);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.005, -1.0, -1.005);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.005, -1.0, -1.005);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.005, -1.0, 1.005);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.005, -1.0, 1.005);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[4].textura]);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.005, -1.005);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.005, -1.005);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(1.0, 1.005, 1.005);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(1.0, -1.005, 1.005);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[sprites_spc[5].textura]);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.005, -1.005);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-1.0, -1.005, 1.005);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-1.0, 1.005, 1.005);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.005, -1.005);

    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(&matriz_proyeccion_B[0][0]);

    gluLookAt(camara[3][0], camara[3][1], camara[3][2], // Posición
              camara[3][0] + camara[2][0], camara[3][1] + camara[2][1], camara[3][2] + camara[2][2],    // Punto al que miramos
              camara[1][0], camara[1][1], camara[1][2]);        // Orientación Y


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
    glPointSize(4.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    for (aux = 0; aux < n_polvo_espacial; aux += 4) {


        glRasterPos3f(polvo_espacial[aux], polvo_espacial[aux + 1],
                      polvo_espacial[aux + 2]);
        glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &visible);

        if (!visible) {
            polvo_espacial[aux] = camara[3][0] + camara[2][0] * 10;
            polvo_espacial[aux + 1] = camara[3][1] + camara[2][1] * 10;
            polvo_espacial[aux + 2] = camara[3][2] + camara[2][2] * 10;

            polvo_espacial[aux] += camara[0][0] * ((rand() % 10) - 5);
            polvo_espacial[aux + 1] += camara[0][1] * ((rand() % 10) - 5);
            polvo_espacial[aux + 2] += camara[0][2] * ((rand() % 10) - 5);

            polvo_espacial[aux] += camara[1][0] * ((rand() % 10) - 5);
            polvo_espacial[aux + 1] += camara[1][1] * ((rand() % 10) - 5);
            polvo_espacial[aux + 2] += camara[0][2] * ((rand() % 10) - 5);


        }

        glPointSize(polvo_espacial[aux + 3]);
        glBegin(GL_POINTS);
        glVertex3f(polvo_espacial[aux], polvo_espacial[aux + 1],
                   polvo_espacial[aux + 2]);
        glEnd();

    }
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glLoadIdentity();


    /* Renderizamos una nave de prueba */

    render_mad(nave);
    glLoadIdentity();
    glDisable(GL_LIGHTING);
    glRasterPos3f(nave->x, nave->y, nave->z);
    glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &visible);
    glGetFloatv(GL_CURRENT_RASTER_POSITION, &viewport);
    glLoadIdentity();





    /* Ahora vamos a cagarnos un rato. Cojemos el punto donde esta la nave liebre,
       hacemos una proyección sobre nuestro plano de visión y hallamos el punto más cercano
       en nuestro plano al punto de la nave. Así tendremos una referencia de donde cojones
       está esta.

       Nota: Ricardo ni Mariajo tuvieron güevos de sacarlo ;P */

    if (visible) {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixd(&matriz_proyeccion_C[0][0]);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,
                      matriz_texturas[id_textura_localizador]);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(viewport[0] - 16.0f, viewport[1] + 16.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(viewport[0] - 16.0f, viewport[1] - 16.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(viewport[0] + 16.0f, viewport[1] - 16.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(viewport[0] + 16.0f, viewport[1] + 16.0f);
        glEnd();
    } else {

        Px = camara[3][0];
        Py = camara[3][1];
        Pz = camara[3][2];
        Vx = camara[2][0];
        Vy = camara[2][1];
        Vz = camara[2][2];
        Ox = nave->x;
        Oy = nave->y;
        Oz = nave->z;
        multiplicador =
            (Vx * Px + Vy * Py + Vz * Pz - Ox * Vx - Oy * Vy -
             Oz * Vz) / (Vx * Vx + Vy * Vy + Vz * Vz);
        Gx = Ox + multiplicador * Vx;
        Gy = Oy + multiplicador * Vy;
        Gz = Oz + multiplicador * Vz;
        Gx = Gx - camara[3][0];
        Gy = Gy - camara[3][1];
        Gz = Gz - camara[3][2];
        modulo = sqrt(Gx * Gx + Gy * Gy + Gz * Gz) * 10;
        Gx = Gx / modulo;
        Gy = Gy / modulo;
        Gz = Gz / modulo;



        /* Establecemos la guía */
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_CULL_FACE);
        glDisable(GL_LIGHTING);
        glLoadIdentity();
        glPointSize(5.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POINTS);
        glVertex3f(camara[3][0] + camara[2][0] + Gx,
                   camara[3][1] + camara[2][1] + Gy,
                   camara[3][2] + camara[2][2] + Gz);

        glEnd();

    }
    glColor3f(1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(&matriz_proyeccion_C[0][0]);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, matriz_texturas[id_textura_crosshair]);

    /* CrossHair */
    /* Con la funcion glTexCoord2f mapeamos las coordenadas de la textura */
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(config.SCREEN_SIZE_X / 2 - 16.0f,
               config.SCREEN_SIZE_Y / 2 + 16.0f);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(config.SCREEN_SIZE_X / 2 - 16.0f,
               config.SCREEN_SIZE_Y / 2 - 16.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(config.SCREEN_SIZE_X / 2 + 16.0f,
               config.SCREEN_SIZE_Y / 2 - 16.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(config.SCREEN_SIZE_X / 2 + 16.0f,
               config.SCREEN_SIZE_Y / 2 + 16.0f);
    glEnd();



    print_p(def, IZQUIERDA, config.SCREEN_SIZE_Y, .25f,
            "Velocidad %f m/s %f,%f,%f", velocidad * 10, nave->x, nave->y,
            nave->z);


    glFlush();
    SDL_GL_SwapBuffers();

    return SI;
}


int game_loop()
{

    int done = 0;

    SDL_Event event;
    Uint8 *keys;
    static float taux, tiempo_antiguo;


    while (done == 0) {
        taux = SDL_GetTicks();
        intervalo = (taux - tiempo_antiguo) / 1000.0f;
        tiempo_antiguo = taux;


        if (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT)
                done = 1;

            keys = SDL_GetKeyState(NULL);
            if (keys[SDLK_ESCAPE])
                done = 1;

            if (keys[SDLK_F1]) {
                if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_ON) {
                    SDL_ShowCursor(1);
                    SDL_WM_GrabInput(SDL_GRAB_OFF);
                } else {
                    SDL_ShowCursor(0);
                    SDL_WM_GrabInput(SDL_GRAB_ON);
                }

            }

        }
        input_teclado();
        input_mouse();
        renderiza_escena();
        SDL_Delay(1);

    }

    return SI;
}
