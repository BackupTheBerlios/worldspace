/***************************************************************************
 *   Copyright (C) 2008 by tyler   *
 *   tyler@khand   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QApplication>
#include "ui_mainView.h"
#include "plugins.h"

plugin_info *plugins;


/* Flags*/

char textura_cargada;
char modelo_cargado;
char modo_dibujo;
char luces=1;
modelo *model;

GLfloat LightAmbient[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat LightDiffuse1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition1[] = { 0.0f, 1.0f, 0.0f, 0.0f };
GLfloat specular [] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat shininess [] = { 100.0 };

double matriz_proyeccion_A[4][4];
double matriz_modelview[4][4];
float quaternion[4];
float zoom=-1.0f;

int circle_subdiv;



GLuint textura;
char RUNPATH[1024];

int main(int argc, char *argv[])
{
    int i;
    char auxiliar[2048];
    char msg[1024];
    char *extension;
    int plugin_elegido = 0;

    QApplication app(argc, argv);
    QMainWindow *mWindow = new QMainWindow();
    Ui_AppMainWindow *mainView;

    /* Vamos a preparar el path de ejecución */

#ifdef W3DWIN32

    /* En Windoze, al ejecutar la aplicación se usa el PATH absoluto */
    strcpy(RUNPATH, argv[0]);
    for (int i = strlen(RUNPATH) - 1; i >= 0; i--)
        if ((RUNPATH[i] == '\\')) {
            RUNPATH[i + 1] = '\0';
            break;
        }
#endif
#ifdef LINUX
    /* En linux es habitual ejecutarlo de las dos maneras */

    if (argv[0][0] == '/') {    //Path absoluto
        printf("Path absoluto\n");
        strcpy(RUNPATH, argv[0]);
        for (i = strlen(RUNPATH) - 1; i >= 0; i--)
            if ((RUNPATH[i] == '/')) {
                RUNPATH[i + 1] = '\0';
                break;
            }
    } else {                    // Path relativo
        printf("Path relativo\n");
        strcpy(RUNPATH, argv[0]);
        for (i = strlen(RUNPATH) - 1; i >= 0; i--)
            if ((RUNPATH[i] == '/')) {
                RUNPATH[i + 1] = '\0';
                break;
            }

        getcwd(auxiliar, 2046);
        chdir(RUNPATH);         // Cambiamos al directorio del programa
        getcwd(RUNPATH, 2046);  // Almacenamos ese directorio
        strcat(RUNPATH, "/");   // Añadimos la barra
        chdir(auxiliar);
    }
#endif

    printf("RUNPATH : %s\n", RUNPATH);
    strcpy(msg,RUNPATH);
    strcat(msg,"plugins");
    if (buscar_plugins(msg,plugins)!=1) {

      printf("No se encontró ningún plugin");

    }
    if (argc > 1) {
 
        /* Hay que decidir con que plugin cargarlo */

        extension = &argv[1][strlen(argv[1]) - 3];
        printf("Extension: %s\n", extension);
        for (int i = 0; i < numero_plugins; i++)
            if (strstr(plugins[i].extension, extension) == NULL)
                continue;
            else
                plugin_elegido = i;
        if (importar_modelo(plugin_elegido, argv[1]) != 1) {
            sprintf(msg, "No pude importar %s", argv[1]);
            modelo_cargado = 0;
        } else
            modelo_cargado = 1;

    }



    mainView = new Ui_AppMainWindow();
    mainView->setupUi(mWindow);

    mWindow->show();


    return app.exec();
}
