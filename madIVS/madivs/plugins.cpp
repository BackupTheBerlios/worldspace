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

#include "globales.h"

#include <stdio.h>
#include <stdlib.h>



#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>


#ifdef W3DWIN32

#include <windows.h>

#define CargaDLL LoadLibrary
#define CargaFuncion GetProcAddress
#define CierraDLL while(0==1){;}
HINSTANCE hDll;
#endif
#ifdef LINUX

#include <dlfcn.h>
void *hDll;
inline void *dlopen2(char *fich) {return (void *)dlopen(fich,RTLD_LAZY);}
#define CargaDLL dlopen2
#define CargaFuncion dlsym

#define CierraDLL dlclose(hDll)
#endif

char **extensiones;


int buscar_plugins(char *dir,plugin_info *plug_tag) {


    void *libc;
    int *tmp;
    char fich_dll[1024];

    struct dirent *lista_nombres;
    DIR *dir_h;
    int n_plug_tag=0;

    /* Funciones a importar de la librería dinámica */


      char  *(*mostrar_nombre)(void);
      char  *(*mostrar_autor)(void);
      char  *(*mostrar_info)(void);
      int   *(*mostrar_fecha)(void);
      int   *(*mostrar_version)(void);
      char  *(*mostrar_extension)(void);


    /* Leemos el directorio de plug_tag */

    dir_h=opendir(dir);
    lista_nombres=readdir(dir_h);
    while (lista_nombres!=NULL) {


      strcpy(fich_dll,dir);
      strcat(fich_dll,"/");
      strcat(fich_dll,lista_nombres->d_name);
      printf("%s ",fich_dll);

      hDll=CargaDLL(fich_dll);


      if(hDll!=NULL)
      {

      mostrar_nombre=(char *(*)())CargaFuncion(hDll,"mostrar_nombre");
      printf("\n%s\n",(*mostrar_nombre)());

      mostrar_autor=(char *(*)())CargaFuncion(hDll,"mostrar_autor");
      printf("%s\n",(*mostrar_autor)());

      mostrar_info=(char *(*)())CargaFuncion(hDll,"mostrar_info");
      printf("%s\n",(*mostrar_info)());

      mostrar_version=(int *(*)())CargaFuncion(hDll,"mostrar_version");
      tmp=(*mostrar_version)();
      printf("Versión: %d.%d.%d  ",tmp[0],tmp[1],tmp[2]);

      mostrar_fecha=(int *(*)())CargaFuncion(hDll,"mostrar_fecha");
      tmp=(*mostrar_fecha)();
      printf("%d/%d/%d\n",tmp[0],tmp[1],tmp[2]);

      mostrar_extension=(char *(*)())CargaFuncion(hDll,"mostrar_extension");
      printf("Extensiones: %s\n\n",(*mostrar_extension)());

      n_plug_tag++;
      CierraDLL;
      }
    else {
      printf("No es una librería dinámica válida: ");
      //printf("%s\n",dlerror());

    }
    lista_nombres=readdir(dir_h);
    }
    closedir(dir_h);


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
      hDll = CargaDLL(fich_dll);

      if(hDll!=NULL)
      {
      mostrar_nombre=(char *(*)())CargaFuncion(hDll,"mostrar_nombre");
      strcpy(plug_tag[n_plug_tag].nombre,(*mostrar_nombre)());

      mostrar_autor=(char *(*)())CargaFuncion(hDll,"mostrar_autor");
      strcpy(plug_tag[n_plug_tag].autor,(*mostrar_autor)());

      mostrar_info=(char *(*)())CargaFuncion(hDll,"mostrar_info");
      strcpy(plug_tag[n_plug_tag].info,(*mostrar_info)());


      mostrar_version=(int *(*)())CargaFuncion(hDll,"mostrar_version");
      tmp=(*mostrar_version)();
      plug_tag[n_plug_tag].version[0]=tmp[0];
      plug_tag[n_plug_tag].version[1]=tmp[1];
      plug_tag[n_plug_tag].version[2]=tmp[2];

      mostrar_version=(int *(*)())CargaFuncion(hDll,"mostrar_fecha");
      tmp=(*mostrar_fecha)();
      plug_tag[n_plug_tag].fecha[0]=tmp[0];
      plug_tag[n_plug_tag].fecha[1]=tmp[1];
      plug_tag[n_plug_tag].fecha[2]=tmp[2];

      mostrar_extension=(char *(*)())CargaFuncion(hDll,"mostrar_extension");
      strcpy(plug_tag[n_plug_tag].extension,(*mostrar_extension)());

      strcpy(plug_tag[n_plug_tag].fich,fich_dll);

      extensiones[n_plug_tag]=(char *)malloc(strlen(plug_tag[n_plug_tag].extension));
      strcpy(extensiones[n_plug_tag],plug_tag[n_plug_tag].extension);


      n_plug_tag++;
      CierraDLL;
      }

    lista_nombres=readdir(dir_h);
    }

    extensiones[n_plug_tag]=NULL;

    closedir(dir_h);


    plugins=plug_tag;
    if (n_plug_tag==0)
        return -1;
    else
        return 1;
}

int importar_modelo(int n_plugin,char *file) {

      int (*importar_modelo_dll)(char *,void *);
      void *libc;
      void *model_tag;
      int ok;


      hDll = CargaDLL(plugins[n_plugin].fich);

      if (hDll==NULL) {
        printf("No es una librería dinámica válida: ");
        return -1;
      }


      importar_modelo_dll=(int(*)(char *,void *))CargaFuncion(hDll,"importar_modelo");


      printf("Dirección de memoria madvis %d\n",(int)&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)model_tag);
      ok=(*importar_modelo_dll)(file,&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)&model_tag);
      printf("Dirección de memoria madvis %d\n",(int)model_tag);
      CierraDLL;

      model=(modelo *)model_tag;
            
      return ok;


}

