/***************************************************************************
                          plugins.cpp  -  description
                             -------------------
    begin                : jue jun 13 2002
    copyright            : (C) 2002 by neuralgya
    email                : neuralgya@mail.berlios.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/*

// Código W32
typedef struct
{
        DWORD dwARG[10];
}STACK;

typedef DWORD (*PFNDLL)(STACK);

void main()
{
        HINSTANCE hDll = LoadLibrary("MyDll.dll")
        PFDLL pfFunc = (PFDLL)GetProcAddress(hDll,"MyFunc");
        STACK args;
        char szBuf[] = "hello world";
        DWORD dwRet;

        args[0] = 10; // a dword
        args[1] = (DWORD)szBuf;

        dwRet = (pfFunc)(args);
}
*/

#include "globales.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>



#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


char **extensiones;


int buscar_plugins(char *dir,plugin_info *plug_tag) {


    void *libc;
    int *tmp;
    char fich_dll[1024];

    struct dirent *lista_nombres;
    DIR *dir_h;
    int n_plug_tag=0;

    /* Funciones a importar de la librería dinámica */

    char *(*mostrar_nombre)();
    char *(*mostrar_autor)();
    char *(*mostrar_info)();
    int  *(*mostrar_fecha)();
    int  *(*mostrar_version)();
    char *(*mostrar_extension)();


    /* Leemos el directorio de plug_tag */

    dir_h=opendir(dir);
    lista_nombres=readdir(dir_h);
    while (lista_nombres!=NULL) {


      strcpy(fich_dll,dir);
      strcat(fich_dll,"/");
      strcat(fich_dll,lista_nombres->d_name);
      printf("%s ",fich_dll);
      libc=dlopen(fich_dll,RTLD_LAZY);

      if(libc!=NULL)
      {
      mostrar_nombre=(char *(*)())dlsym(libc,"mostrar_nombre");
      printf("\n%s\n",(*mostrar_nombre)());

      mostrar_autor=(char *(*)())dlsym(libc,"mostrar_autor");
      printf("%s\n",(*mostrar_autor)());

      mostrar_info=(char *(*)())dlsym(libc,"mostrar_info");
      printf("%s\n",(*mostrar_info)());

      mostrar_version=(int *(*)())dlsym(libc,"mostrar_version");
      tmp=(*mostrar_version)();
      printf("Versión: %d.%d.%d  ",tmp[0],tmp[1],tmp[2]);

      mostrar_fecha=(int *(*)())dlsym(libc,"mostrar_fecha");
      tmp=(*mostrar_fecha)();
      printf("%d/%d/%d\n",tmp[0],tmp[1],tmp[2]);

      mostrar_extension=(char *(*)())dlsym(libc,"mostrar_extension");
      printf("Extensiones: %s\n\n",(*mostrar_extension)());

      n_plug_tag++;
      }
    else {
      printf("No es una librería dinámica válida: ");
      printf("%s\n",dlerror());

    }
    lista_nombres=readdir(dir_h);
    }
    closedir(dir_h);
    dlclose(libc);

    plug_tag=(plugin_info *)malloc(sizeof(plugin_info)*(n_plug_tag+1));

    extensiones=(char **)malloc(sizeof(char *)*(n_plug_tag+2));


   /* Leemos el directorio de plug_tag por segunda vez*/

    n_plug_tag=0;
    dir_h=opendir(dir);
    lista_nombres=readdir(dir_h);
    while (lista_nombres!=NULL) {


      strcpy(fich_dll,dir);
      strcat(fich_dll,"/");
      strcat(fich_dll,lista_nombres->d_name);
      libc=dlopen(fich_dll,RTLD_LAZY);
      if(libc!=NULL)
      {
      mostrar_nombre=(char *(*)())dlsym(libc,"mostrar_nombre");
      strcpy(plug_tag[n_plug_tag].nombre,(*mostrar_nombre)());

      mostrar_autor=(char *(*)())dlsym(libc,"mostrar_autor");
      strcpy(plug_tag[n_plug_tag].autor,(*mostrar_autor)());

      mostrar_info=(char *(*)())dlsym(libc,"mostrar_info");
      strcpy(plug_tag[n_plug_tag].info,(*mostrar_info)());


      mostrar_version=(int *(*)())dlsym(libc,"mostrar_version");
      tmp=(*mostrar_version)();
      plug_tag[n_plug_tag].version[0]=tmp[0];
      plug_tag[n_plug_tag].version[1]=tmp[1];
      plug_tag[n_plug_tag].version[2]=tmp[2];

      mostrar_version=(int *(*)())dlsym(libc,"mostrar_fecha");
      tmp=(*mostrar_fecha)();
      plug_tag[n_plug_tag].fecha[0]=tmp[0];
      plug_tag[n_plug_tag].fecha[1]=tmp[1];
      plug_tag[n_plug_tag].fecha[2]=tmp[2];

      mostrar_extension=(char *(*)())dlsym(libc,"mostrar_extension");
      strcpy(plug_tag[n_plug_tag].extension,(*mostrar_extension)());

      getcwd(plug_tag[n_plug_tag].fich,1024);
      strcat(plug_tag[n_plug_tag].fich,"/");
      strcat(plug_tag[n_plug_tag].fich,fich_dll);

      extensiones[n_plug_tag]=(char *)malloc(strlen(plug_tag[n_plug_tag].extension));
      strcpy(extensiones[n_plug_tag],plug_tag[n_plug_tag].extension);


      n_plug_tag++;
      }

    lista_nombres=readdir(dir_h);
    }

    extensiones[n_plug_tag]=NULL;

    closedir(dir_h);
    dlclose(libc);

    plugins=plug_tag;

    return 0;
}

int importar_modelo(int n_plugin,char *file) {

      int (*importar_modelo_dll)(char *,void *);
      void *libc;
      void *model_tag;



      libc=dlopen(plugins[n_plugin].fich,RTLD_LAZY);
      if (libc==NULL) {
        printf("No es una librería dinámica válida: ");
        printf("%s\n",dlerror());
      }


      importar_modelo_dll=(int(*)(char *,void *))dlsym(libc,"importar_modelo");


      printf("Dirección de memoria madvis %d\n",(int)&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)model_tag);
      (*importar_modelo_dll)(file,&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)model_tag);
      dlclose(libc);

      model=(modelo *)model_tag;
      modelo_cargado=1;

      return 0;


}
