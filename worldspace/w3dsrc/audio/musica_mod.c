/***************************************************************************
  musica_mod.c  funciones para la carga y reproduccion de archivos mod,xm,....
                             -------------------
    begin                : Vie 11 Abril 2003
    copyright          : (C) 2003 by Grupo WorldSpace
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "w3d_base.h"
#include "globales.h"
#include "sdl_gl.h"
#include "musica_mod.h"
#include "mikmod.h"
#include "mikmod_internals.h"

#define DEFBUFSIZ         4096
#define NUM_BUFFERS_MUSIC 4

static ALuint sid[1];
static ALuint bid[NUM_BUFFERS_MUSIC];
SBYTE audiobuffer[DEFBUFSIZ];

MODULE *modulo;
SDL_Thread *threadmusica2; /* Thread de audio */
int repeticion2;

/*****************************************************************************************
Funcion       : cargar_mod ( char *fichero_mod )
*****************************************************************************************/

int cargar_mod ( char *fichero_mod ){


    FILE *fichero;
    char filename[LON_BUFF];
    ALint error;
    int i, cont;

    /* Establecemos donde estara situado el directorio para los sonidos */
    strcpy(filename, "musicas");
    strcat(filename, "/");
    strcat(filename, fichero_mod);
    log_msj("[musica_mod.c] Cargando musica %s\n", filename);

    /* Abrimos fichero para lectura */
    if ( ( fichero = abre_fichero ( filename, "rb" )) == NULL ){
	log_msj( "[KO] No se puede cargar fichero %s\n", fichero_mod );
	return NO;
    }
    /* Cargamos el modulo */
    modulo = Player_LoadFP(fichero, 255, 0);
    if (modulo == NULL) {
        log_msj("[KO] No se puede cargar fichero, razon: %s\n", MikMod_strerror(MikMod_errno));
	return NO;
    }



    /* Generamos  buffers para hacer el streaming */
    alGenBuffers ( NUM_BUFFERS_MUSIC, bid );
    if ( (error = alGetError()) != AL_NO_ERROR){
      log_msj ("[KO] Fallo al crear los buffers para la musica en cargar_mod:%s\n", alGetString(error));
      return NO;
    }

    /* Activamos el modulo */
    Player_Start(modulo);
    /* Rellenamos los buffers creados con la musica decodificada */
    for ( i=0; i < NUM_BUFFERS_MUSIC ; i++){
      cont = VC_WriteBytes (audiobuffer, DEFBUFSIZ);
      if (cont == 0){
        break;
      }else{
        alBufferData ( bid[i], AL_FORMAT_STEREO16, audiobuffer , DEFBUFSIZ , md_mixfreq );
        if ( (error = alGetError ()) != AL_NO_ERROR ){
          log_msj ("[KO] Error al asignar datos al buffer %i en cargar_mod:%s\n",i,alGetString(error));
          return NO;
        }
      }
    }

    /* Creamos la fuente y definimos sus propiedades */
    alGenSources( 1, sid );
    if ( (error = alGetError()) != AL_NO_ERROR ){
      log_msj ("[KO] Error al generar la fuente de sonido en cargar_mod: %s\n", alGetString (error));
      return NO;
    }

    /* Defino propiedades para la fuente */
    alSourcei ( sid[0], AL_SOURCE_RELATIVE, AL_TRUE ); /* Para que se mueva con el listener */
    alSourcei ( sid[0], AL_LOOPING, AL_FALSE ); /* No se repite por ella sola */
    alSourcef ( sid[0], AL_GAIN, 0.9f ); /* Para que suene menos que los sonidos */

    /* Asignamos los buffers creados a la fuente */
    alSourceQueueBuffers ( sid[0], NUM_BUFFERS_MUSIC, bid );
    if ( (error = alGetError()) != AL_NO_ERROR ){
      log_msj ("[KO] Error al asignar buffers a la fuente en cargar_mod: %s\n", alGetString (error));
      return NO;
    }

    return SI;
}


/******************************************************
Funcion       : pausar_mod (int pausa_mod)
*******************************************************/

int pausar_mod (int pausa_mod){


    ALint error;

    /* Pausamos la musica */
   if (pausa_mod == 1){
     alSourcePause(sid[0]);
      if ( (error = alGetError()) != AL_NO_ERROR ){
        log_msj ("[KO] Error al pausar la fuente de sonido: %s\n", alGetString (error));
        return NO;
      }
   }
   /* Reanudamos la musica */
   if (pausa_mod == 0){
     alSourcePlay(sid[0]);
     if ( (error = alGetError()) != AL_NO_ERROR ){
        log_msj ("[KO] Error al reanudar la reproduccion de la fuente de sonido: %s\n", alGetString (error));
        return NO;
     }
   }
   return SI;

}

/***********************************************************************************************
Funcion      : resetear_mod (  )
************************************************************************************************/

int resetear_mod (void){

     ALint error;

     /* Cuando queremos cambiar la cancion, paramos todo y borramos buffers y fuentes */
     alSourceStopv(1, sid);
     if ( (error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se pueden parar el streamsource en resetear_mod: %s\n",alGetString (error));
       return NO;
     }
     /* Matamos el thread*/
     SDL_KillThread ( threadmusica2 );
     /* Borramos buffers y sources */
     alDeleteSources(1, sid);
     if ( (error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se puede borrar el stremsource en resetear_mod: %s\n",alGetString (error));
       return NO;
     }
     alDeleteBuffers(NUM_BUFFERS_MUSIC, bid);
     if ( ( error = alGetError()) != AL_NO_ERROR){
       log_msj ("[KO] No se pueden borrar los buffers en resetear_mod: %s\n",alGetString (error));
       return NO;
     }
     /* Lo reseteamos */
     Player_Free (modulo);

     return SI;
}


/******************************************************************************************************
Funcion       : actualizar_mod (  )
******************************************************************************************************/

int  actualizar_mod ( void ){

    ALint error;
    int cont = 0,contador = 0, cancion_acabada = NO, repeticion_acabada = NO;
    ALuint buffer_intercambio;
    int buffers_vacios = 0;
    ALint estado;

    /* Aqui establacemos el primer bucle para la repeticion */
    while ( repeticion_acabada == NO ){
      /* A partir de aqui es donde realmente empieza el Streaming*/
      while ( cancion_acabada == NO ){
        /* Comprobamos estado de los buffers */
        alGetSourcei ( sid[0], AL_BUFFERS_PROCESSED, &buffers_vacios);
        /* Si algun buffer esta vacio, lo rellenamos */
        if ( buffers_vacios > 0 ){
          while ( buffers_vacios ){
            /* Desasignamos buffers para rellenarlos */
            alSourceUnqueueBuffers ( sid[0], 1, &buffer_intercambio );
            if ( (error = alGetError( )) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede desasignar buffers en actualizar_mod: %s\n",alGetString (error));
              return NO;
            }
            /* Descomprimimos datos en el buffer intermedio */
            if ( (cont = VC_WriteBytes(audiobuffer, DEFBUFSIZ)) == 0){
              cancion_acabada = SI;
              break;
            }
            /* Los  anyadimos en el buffer */
            alBufferData ( buffer_intercambio, AL_FORMAT_STEREO16, audiobuffer, DEFBUFSIZ , md_mixfreq );
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede añadir datos al buffer en actualizar_mod: %s\n",alGetString (error));
              return NO;
            }
            /* Asignamos de nuevo los buffers al streamsource */
            alSourceQueueBuffers ( sid[0], 1, &buffer_intercambio );
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede asignar buffers a la fuente en actualizar_mod: %s\n",alGetString (error));
              return NO;
            }
            buffers_vacios --;

          }
        }
        /* Si ocurre buffer underrun lo ponemos en marcha de nuevo o si esta en pausa lo paramos*/
        alGetSourcei(sid[0], AL_SOURCE_STATE, &estado);
        if (estado != AL_PLAYING){
          if (estado != AL_PAUSED){
            alSourcePlay(sid[0]);
            if ((error = alGetError()) != AL_NO_ERROR ){
              log_msj ("[KO] No se puede arreglar el buffer underrun en actualizar_mod: %s\n",alGetString (error));
              return NO;
            }
          }else{
            while (estado == AL_PAUSED){
              alGetSourcei(sid[0], AL_SOURCE_STATE, &estado);
              SDL_Delay(10);
            }
          }
        }
        /* Para sincronizar mejor la musica y que no se imponga al thread principal */
        SDL_Delay(50);

      }
      /* A partir de aqui miramos cuantas veces tiene que ser repetida la musica */
      contador = contador + 1;
      if ( (contador >= repeticion2) && (repeticion2 != -1) ){
        repeticion_acabada = SI;
      }else{
	/* Rebobinamos la musica hasta el principio */
	Player_SetPosition(0);
	cancion_acabada = NO;
      }
    }
    return SI;

}


/********************************************************
 * Funcion       : reproducir_mod ( int repetir )
 * ********************************************************/

int reproducir_mod ( int repetir ){

       /* Para la repeticion de la musica */
       repeticion2 = repetir;

       /* Creamos thread independiente para la musica */
       threadmusica2 = SDL_CreateThread ((void *)actualizar_mod, NULL);
       if (threadmusica2 == NULL) {
              log_msj ("[KO] No podemos crear el thread para la musica.\n");
              return NO;
       }
       return SI;

}


