/* Fichero donde se definen todas las funciones relativas al audio */
/* version 0.7 */

/* Cabeceras normales*/
#include <stdio.h>
#include <stdlib.h>
#include "init_sys.h"
#include "teclado.h"
#include "render.h"
#include "opengl.h"

/* Cabeceras necesarias para decodificar ficheros OGG Vorbis */
#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

/* Cabeceras necesarias para utilizar API OpenAL */
#ifdef _LINUX
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>
#include <AL/alext.h>
#endif
#ifdef _WIN32
#include <al\al.h>
#include <al\alc.h>
#include <al\alut.h>
#include <eax.h>
#endif

/* Aqui definimos el nº de sonidos, musicas, entornos y listeners que vamos a utilizar */

#define NUM_SONIDOS     1
#define NUM_MUSICAS     1
#define NUM_ENTORNOS    1
#define NUM_LISTENER    1

/* Definimos estructura del listener y lo creamos */
typedef struct {
	ALfloat    Posicion[3];
	ALfloat    Velocidad[3];
	ALfloat    Orientacion[6];
}LISTENER;
LISTENER Listener[NUM_LISTENER]; 

/* Aqui definimos nuestras variables globales */
ALCdevice *Device = NULL;   /* Dispositivo de sonido */
#ifdef _LINUX
ALvoid     *Context = NULL;   /* Contexto para Linux */
#endif
#ifdef _WIN32
ALCcontext *Context = NULL;  /* Contexto para Windows */
#endif
ALuint frecuencia; /* Utilizados en la carga de archivos OGG */
ALuint bitrate; /* Utilizados en la carga de archivos OGG */
ALenum formato; /* Utilizado en la carga de archivos OGG */
int tamanyo_cancion; /* Utilizado en la carga de archivos OGG */

int NUM_BUFFER_MUSICA;

ALuint streamvacios;
static ALuint estado;
static ALuint buffer[NUM_SONIDOS];
static ALuint source[NUM_SONIDOS];
static ALuint entornos[NUM_ENTORNOS];

int BUFFER_MUSICA;
OggVorbis_File buff;
SDL_Thread *threadmusica = NULL; /* Thread de audio */
int audio_on = 0;
int musica_on =0;
int musica_decodificada = 0;
int buffers_vacios = 0;
int current_section = -1;
int numero_total=0;
int streambuffer_vacio = 0 ;

vorbis_info *informacion = NULL;
/* A partir de aqui pondremos nuestras funciones */


/********************************************************************************
Funcion      : InicializarAudio ( )
Objetivo     : Esta funcion mira los dispositivos/drivers disponibles y
                   asigna un contexto para que funcione OpenAL
Parametros : No hay que pasarle ningun parametro
********************************************************************************/

int InicializarAudio(){

	/* Asignamos el mejor dispositivo de audio disponible */
#ifdef _LINUX

	if (( Device = alcOpenDevice ((ALubyte* ) "waveOut" )) == NULL){
		fprintf ( logs,"No existe WaveOut Backend\n");
		if (( Device = alcOpenDevice (( ALubyte* ) "SDL" )) == NULL ){
			fprintf ( logs,"No existe SDL Backend\n");
			if (( Device = alcOpenDevice (( ALubyte* ) "arts" )) == NULL ){
				fprintf ( logs,"No existe arts Backend\n");
				if (( Device = alcOpenDevice ( NULL )) == NULL ){
					fprintf ( logs,"No hay disponible ningun dispositivo de audio\n");
					return -1;
				}
			}
		}
	}
#endif
#ifdef _WIN32
	if (( Device = alcOpenDevice ((ALubyte* ) "DirectSound3D" )) == NULL ){
		fprintf ( logs,"No existe DirectSound3D Backend\n");
		if (( Device = alcOpenDevice (( ALubyte* ) "DirectSound" )) == NULL ){
			fprintf ( logs,"No existe DirectSound Backend\n");
			if (( Device = alcOpenDevice (( ALubyte* ) "WaveOut" )) == NULL ){
				fprintf ( logs,"No existe WaveOut Backend\n");
				if (( Device = alcOpenDevice ( NULL )) == NULL ){
					fprintf ( logs,"No hay disponible ningun dispositivo de audio\n");
					return -1;
				}
			}
		}
	}
#endif

	/* Creamos un contexto y lo asignamos (comprobando si hay errores)*/
	if ( Device != NULL ){
		Context = alcCreateContext ( Device , NULL ); /* Creamos */
	    if ( alcGetError ( Device ) != ALC_NO_ERROR ){
			fprintf ( logs, "No se puede crear un contexto para el sistema de audio\n");
			return -1;
		}

		alcMakeContextCurrent ( Context ); /* Asignamos */
	    if ( alcGetError ( Device ) != ALC_NO_ERROR ){
			fprintf ( logs, "No se puede asignar el contexto para el sistema de audio\n");
			return -1;
		}
	}
  audio_on = 1;
  return 0;
}

/***********************************************************************************
Funcion       : FinalizarAudio ( )
Objetivo      : Esta funcion destruye el contexto creado y desconecta
                    del dispositivo de audio
Parametros : No hay que pasarle ningun parametro
***********************************************************************************/

void FinalizarAudio ( ){
	alcMakeContextCurrent ( NULL ); /* Desactivamos el contexto */
	alcDestroyContext ( Context ); /* Destruimos el contexto */
	alcCloseDevice ( Device ); /* Cerramos el dispositivo */
}

/****************************************************************************************************
Funcion       : ActualizarListener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                           ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
                           ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
                           ALfloat y_fro, ALfloat z_fro )
Objetivo       : Esta funcion actualiza los parametros del listener y
                     facilita la posibilidad de pasarle los datos de
                     posicion, velocidad y orientacion del player
Parametros : Hay que pasarle 13 parametros

ALuint  num --> El numero del listener
ALfloat x_pos --> La posicion en el eje x del listener/player
ALfloat y_pos --> La posicion en el eje y del listener/player
ALfloat z_pos --> La posicion en el eje z del listener/player
ALfloat x_vel --> La velocidad en el eje x del listener/player

ALfloat y_vel --> La velocidad en el eje y del listener/player
ALfloat z_vel --> La velocidad en el eje z del listener/player
ALfloat x_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en x
ALfloat y_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en y
ALfloat z_sup --> Direccion vector saliente perpendicular a la cabeza (hacia arriba) en z
ALfloat x_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en x
ALfloat y_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en y
ALfloat z_fro --> Direccion vector saliente perpendicular a los ojos (hacia delante) en z
********************************************************************************************************/

void ActualizarListener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                      ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
			    ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
			    ALfloat y_fro, ALfloat z_fro ) {

	/* Asignamos valores a los posibles listener */
	Listener[num].Posicion[0] = x_pos;
	Listener[num].Posicion[1] = y_pos;
	Listener[num].Posicion[2] = z_pos;
	Listener[num].Velocidad[0] = x_vel;
	Listener[num].Velocidad[1] = y_vel;
	Listener[num].Velocidad[2] = z_vel;
	Listener[num].Orientacion[0] = x_sup;
	Listener[num].Orientacion[1] = y_sup;
	Listener[num].Orientacion[2] = z_sup;
	Listener[num].Orientacion[3] = x_fro;
	Listener[num].Orientacion[4] = y_fro;
	Listener[num].Orientacion[5] = z_fro;

	/* Actualizamos el valor de la posicion, velocidad y orientacion */



	alListenerfv ( AL_POSITION, Listener[num].Posicion );
	alListenerfv ( AL_VELOCITY, Listener[num].Velocidad );
	alListenerfv ( AL_ORIENTATION, Listener[num].Orientacion );
}


/*****************************************************************************************
Funcion       : CargaSonido ( char *fichero_wav, ALuint identificador )
Objetivo      : Esta funcion carga un fichero WAVE en memoria y lo asigna
                    a una fuente (source)
Parametros : Hay que pasarle 2 parametros



char *fichero_wav --> Nombre del archivo de sonido que queremos cargar
ALuint identificador --> Para indicar que sonido hemos cargado
*****************************************************************************************/

void  CargaSonido (  char *fichero_wav, int identificador ){

	/* Variables locales */
	ALsizei size = NULL, freq = NULL, bits = NULL, format = NULL;
	ALenum format1 = NULL;
	static void *data = NULL;
	ALboolean loop = AL_FALSE;

	/* Generamos buffer, le asignamos un identificador y comprobamos errores */
	alGenBuffers( 1, &buffer[identificador] );
	if ( !alIsBuffer ( buffer[identificador] )){
		fprintf ( logs, "error al crear los buffers\n");
		exit(1);
	}

	/* Cargamos ficheros Wave */
#ifdef _LINUX
	alutLoadWAV ( fichero_wav, &data, &format, &size, &bits, &freq ); /* Cargamos en memoria */
	alBufferData ( buffer[identificador], format, data, size, freq ); /* Almacenamos en buffer */
	free (data); /* liberamos */
#endif
#ifdef _WIN32
	alutLoadWAVFile ( fichero_wav, &format1, &data, &size, &freq, &loop );
	alBufferData ( buffer[identificador], format1, data, size, freq );
	alutUnLoadWAV ( format1, data, size, freq );
#endif

	/* Generamos las fuentes de sonido y comprobamos errores */
	alGenSources( 1, &source[identificador] );
	if ( !alIsSource ( source[identificador])){
		fprintf ( logs, "No se pueden crear las fuentes de sonido\n");
		exit(1);
	}

	/* Pasamos el archivo wav del buffer a la fuente */
	alSourcei ( source[identificador], AL_BUFFER, buffer[identificador]);

}





/************************************************************************************************************
Funcion    : ReproducirSonido ( ALuint identificador, ALfloat src_pos[3], ALfloat src_vel[3],
                           ALfloat ganancia, Alfloat pitch, ALboolean repeticion )
Objetivo   : Hace sonar el sonido especificado en la posicion y velocidad indicados
              y con la ganancia, frecuencia y repeticion que se les introduzca
Parametros : Hay que pasarle 6 parametros

ALuint identificador --> Para indicar que sonido queremos escuchar
ALfloat src_pos[3] --> Indica la posicion donde se va escuchar el sonido
ALfloat src_vel[3] --> Indica la velocidad del sonido
ALfloat ganancia --> Ganancia en amplitud de la fuente
ALfloat pitch --> Frecuencia de la fuente
ALboolean repeticion --> Si se repite o no
************************************************************************************************************/

void ReproducirSonido ( int identificador, ALfloat src_pos[3], ALfloat src_vel[3],
		      ALfloat ganancia, ALfloat pitch,ALfloat distancia_maxima, ALboolean repeticion ){

	/* Configuramos la fuente con los parametros */
	alSourcefv ( source[identificador], AL_POSITION, src_pos); /* Posicion */
	alSourcefv ( source[identificador], AL_VELOCITY, src_vel); /* Velocidad */
	alSourcef ( source[identificador], AL_GAIN, ganancia); /* Ganancia */
	alSourcef ( source[identificador], AL_PITCH, pitch); /* Frecuencia */
	alSourcei ( source[identificador], AL_LOOPING, repeticion); /* Repeticion */
	alSourcef ( source[identificador],AL_MAX_DISTANCE,distancia_maxima);/* Distancia a partir de la cual no se oye */


	/* Hacemos que suene */
	alSourcePlay ( source[identificador] );
}


/***************************************************************************************
Funcion      : ActualizarSource ( ALuint identificador, ALfloat src_pos[3])
Objetivo     : Actualizar la posicion de la fuente para sonidos moviles,
                   como por ejemplo,el sonido del motor de una nave
Parametros : Hay que pasarle 2 parametros

ALuint identificador --> Para indicar que sonido queremos escuchar
ALfloat src_pos[3] --> Indica la posicion donde se va escuchar el sonido
***************************************************************************************/

void ActualizarSource ( ALuint identificador, ALfloat src_pos[3]){

	/* Introducimos nueva posicion */
	alSourcefv ( source[identificador], AL_POSITION, src_pos);
}


/*****************************************************************************************************
Funcion       : ConfigurarEntorno ( ALuint identificador, ALenum modelo,
                                  ALfloat doppler_factor, ALfloat doppler_vel,
                                  ALint room, Alint room_high_frequency,
                                  ALfloat rolloff_factor, ALfloat decay_time,
                                  ALfloat decay_high_frecuency_ratio, ALint reflections,
                                  ALfloat reflections_delay, ALint reverb,
                                  ALfloat reverb_delay, ALfloat diffusion,
                                  ALfloat density, ALfloat high_frequency_reference )
Objetivo      : Configurar nuestro entorno lo maximo posible para obtener los
                    efectos deseados
Parametros : Hay que pasarle 16 parametros

ALuint identificador --> Para indicar el entorno a configurar
ALenum modelo --> Indica el modelo de atenuacion por la distancia
ALfloat doppler_factor --> Indica el factor de escalado del efecto doppler

ALfloat doppler_vel --> Indica velocidad de propagacion
ALint room --> Tipo de entorno
Alint room_high_frequency --> La frecuencia
ALfloat rolloff_factor  --> El factor rolloff
ALfloat decay_time --> El tiempo de cese
ALfloat decay_high_frecuency_ratio --> El radio de cese de la frecuencia
ALint reflections --> La reflexion
ALfloat reflections_delay --> Cese de la reflexion
ALint reverb --> La reverberacion
ALfloat reverb_delay --> Retraso de la reverberacion
ALfloat diffusion --> La difusion
ALfloat density --> La densidad
ALfloat high_frequency_reference --> La referencia de la frecuencia
*********************************************************************************************************/


void ConfigurarEntorno ( ALsizei identificador, ALenum modelo,
                         ALfloat doppler_factor, ALfloat doppler_vel,
                         ALint room, ALint room_high_frequency,
                         ALfloat rolloff_factor, ALfloat decay_time,
                         ALfloat decay_high_frequency_ratio, ALint reflections,
                         ALfloat reflections_delay, ALint reverb,
                         ALfloat reverb_delay, ALfloat diffusion,
                         ALfloat density, ALfloat high_frequency_reference ){



	/* Configuramos la atenuacion y el efecto doppler */
	alEnable ( AL_DISTANCE_MODEL );
	alDistanceModel ( modelo );
	alDopplerFactor ( doppler_factor );
	alDopplerVelocity ( doppler_vel ); /* Recordad que en metros la velocidad del sonido es 343 */

#ifdef _LINUX
	/* Generamos el entorno y comprobamos errores */
	alGenEnvironmentIASIG ( identificador, &entornos[identificador] );
	if ( !alIsEnvironmentIASIG ( entornos[identificador] )){
		fprintf ( logs, "No se puede configurar parte del entorno\n");
	}

	/* Configuramos las propiedades del entorno */
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_ROOM_IASIG, room );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_ROOM_HIGH_FREQUENCY_IASIG,
	                      room_high_frequency);

	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_ROOM_ROLLOFF_FACTOR_IASIG, rolloff_factor );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DECAY_TIME_IASIG, decay_time );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DECAY_HIGH_FREQUENCY_RATIO_IASIG,
	                      decay_high_frequency_ratio );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_REFLECTIONS_IASIG, reflections );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_REFLECTIONS_DELAY_IASIG, reflections_delay );
	alEnvironmentiIASIG ( entornos[identificador], AL_ENV_REVERB_IASIG, reverb );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_REVERB_DELAY_IASIG, reverb_delay );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DIFFUSION_IASIG, diffusion );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_DENSITY_IASIG, density );
	alEnvironmentfIASIG ( entornos[identificador], AL_ENV_HIGH_FREQUENCY_REFERENCE_IASIG,
	                      high_frequency_reference );
#endif
#ifdef _WIN32
	/* Para windows se pueden crear y configurar entornos utilizando las extensiones EAX
	que admiten algunas tarjetas Soundblaster. Pero como no sé si es gratuito la utilizacion
	de dichas extensiones, de momento para windows no se generaran entornos
	*/
#endif
}


/*****************************************************************************************
Funcion       : CargarMusica ( char *fichero_ogg )
Objetivo      : Esta funcion decodifica un fichero ogg y lo pasa a un buffer
                    en formato wav
Parametros : Hay que pasarle 2 parametros

char *fichero_ogg --> Nombre del archivo de musica que queremos cargar

BUG: La reproduccion de ficheros tendria que ser independiente de su bitrate, cosa que ahora no es
*****************************************************************************************/

void CargarMusica ( char *fichero_ogg ){

	/* Variables locales */
	
    FILE *fichero;
    ALint error;
	/* Abrimos fichero para lectura */
	if ( ( fichero = fopen ( fichero_ogg, "r" )) == NULL ){
		fprintf( logs, "No se puede cargar fichero %s\n", fichero_ogg );
		exit(2);
	}

	/* Accedemos al fichero ogg */
	if( ov_open ( fichero, &buff, NULL, 0 ) < 0) {
		fprintf( logs, "Esto no es un fichero ogg.\n" );
		exit(2);
	}

	/* Obtenemos formato, frecuencia */
	informacion = ov_info ( &buff, -1);
	frecuencia = informacion->rate;

    	/* Adjudicamos valores, que son necesarios para una correcta reproduccion*/
    	if ((informacion->channels) == 2){
		formato = AL_FORMAT_STEREO16;
	} else {
		formato = AL_FORMAT_MONO16;
	}

      	/* FIXME : Esto tendria que funcionar con un numero y tamanyo de buffers fijo
      	en vez de lo que hacemos ahora. Corrijeme */
      	/* Preferiblemente usa archivos con un bitrate superior a 92 kbps. Una cantidad inferior a
      	esto podria hacer que el archivo no se reprodujera correctamente */
     	if (((informacion->bitrate_nominal) >= 16000) & ((informacion->bitrate_nominal) < 48000)){
        	NUM_BUFFER_MUSICA = 4;
        	BUFFER_MUSICA = 4096;
     	}
     	else if (((informacion->bitrate_nominal) >= 48000) & ((informacion->bitrate_nominal) < 92000)){
        	NUM_BUFFER_MUSICA = 50;
        	BUFFER_MUSICA = 512;
     	}
     	else if ((informacion->bitrate_nominal) >= 92000){
        	NUM_BUFFER_MUSICA = 200;
        	BUFFER_MUSICA = 256;
     	}

	/* Obtenemos el tamanyo de la cancion*/
	tamanyo_cancion = ov_pcm_total ( &buff, -1 );
	
	

}

/******************************************************
Funcion       : PararMusica ( )
Objetivo      : Para la musica seleccionada
Parametros : No hay que pasarle parametros
******************************************************/

void PararMusica (  ){

    	/* Paramos la musica */
    	/*alSourceStop ( streamsource[0] );
    	musica_on = 0;
    	streambuffer_vacio = 1;*/
}



/***********************************************************************************************
Funcion      : ResetearMusica (  )

Objetivo      : Esta funcion elimina la musica para poder cargar otro archivo OGG
Parametros : No hay que pasarle parametros
************************************************************************************************/

void ResetearMusica (  ){

	/* Antes de limpiar asegurarse de parar la musica */
	/* Eliminamos Buffers y fuente */

	/*alDeleteSources ( 1, &streamsource[0] );
	alDeleteBuffers ( 4, &streambuffers );
	if ( alGetError != AL_NO_ERROR ){
		fprintf ( logs, "No se puede eliminar buffers o fuente");
	}

	/* Liberamos buffer de decodificacion */
	ov_clear ( &buff );
}


/******************************************************************************************************
Funcion       : ActualizarMusica (  )
Objetivo      : Esta funcion rellena los buffers segun se van vaciando. Hay que llamarla
                    muy muy a menudo ya que es la que realmente realiza el streaming.
                    Preferiblemente hay que incluirla en un thread independiente.
Parametros : No hay que pasarle parametros
******************************************************************************************************/

void ActualizarMusica (  ){
        ALint error;
    	int cont = 0;
    	int contador = 0;
    	int i;
    	int posicion = 0;
        ALuint streambuffers[NUM_BUFFER_MUSICA]; /* Utilizado en la carga de archivos OGG */
        ALshort waveout [BUFFER_MUSICA];  /* Donde almacenamos los OGG Vorbis decodificados */
        ALuint streamsource[1]; /* Utilizado en la carga de archivos OGG */
        
      /* Generamos  buffers para hacer el streaming */
	alGenBuffers ( NUM_BUFFER_MUSICA, streambuffers);
     	if ( (error = alGetError()) != AL_NO_ERROR){
        	fprintf ( logs,"Fallo al crear los buffers para la musica:%s\n", alGetString(error));
        	exit (2);
     	}  
     /* Rellenamos los buffers creados con la musica decodificada */
     for ( i=0; i < NUM_BUFFER_MUSICA ; i++){
		cont = ov_read ( &buff, (char *)&waveout[posicion], BUFFER_MUSICA , 0, 2, 1, &current_section ) / 2;
        contador += cont;
        fprintf ( logs, "contador = \n");
        alBufferData ( streambuffers[i], formato, waveout , BUFFER_MUSICA , informacion->rate );
        if ( (error =alGetError ()) != AL_NO_ERROR ){
               	fprintf ( logs, "Error al anyadir datos al buffer %i:%s\n",i,alGetString(error));
        }
	}
        
        /* Creamos la fuente y definimos sus propiedades */
        alGenSources( 1, streamsource );
        if ( (error = alGetError()) != AL_NO_ERROR ){
                	fprintf ( logs, "Error al generar la fuente de sonido: %s\n", alGetString (error));
        }
         
        /* Defino propiedades para la fuente */
        /*alSourcei ( streamsource[0], AL_SOURCE_RELATIVE, AL_TRUE ); /* Para que se mueva con el listener */
        /*alSourcei ( streamsource[0], AL_LOOPING, AL_FALSE ); /* No se repite por ella sola */
        /*alSourcef ( streamsource[0], AL_GAIN, 0.9f ); /* Para que suene menos que los sonidos */

        /* Asignamos los buffers creados a la fuente */
        alSourceQueueBuffers ( streamsource[0], NUM_BUFFER_MUSICA, streambuffers );

        /* Se empieza a reproducir la musica */
        alSourcePlay ( streamsource[0] );
        if ( (error = alGetError ()) != AL_NO_ERROR ){
              fprintf ( logs, "Error al reproducir musica:%s\n",alGetString (error));
        }
	/* A partir de aqui es donde realmente empieza el Streaming*/
	while ( contador < tamanyo_cancion ){

            /* Comprobamos estado de los buffers */
        	alGetSourceiv ( streamsource[0], AL_BUFFERS_PROCESSED, &buffers_vacios);
        
       		/* Si algun buffer esta vacio, lo rellenamos */
       		if ( buffers_vacios > 0 ){
         
               while ( buffers_vacios ){
				
                    /* Desasignamos buffers para rellenarlos */
          			alSourceUnqueueBuffers ( streamsource[0], 1, &streambuffers );
          			if ( (alGetError( )) != AL_NO_ERROR ){
              				fprintf ( logs,"No va el streaming\n");
          			}
					/* Descomprimimos datos en el buffer intermedio */	
			   		cont = ov_read ( &buff, (char *)&waveout, BUFFER_MUSICA, 0, 2, 1, &current_section);
                	contador += cont;
                    /* Los  anyadimos en el buffer */
              		alBufferData ( streambuffers, formato, waveout, BUFFER_MUSICA, frecuencia );
					if ((alGetError()) != AL_NO_ERROR ){
						fprintf ( logs, "No se puede añadir datos al buffer\n");
					}
          			/* Asignamos de nuevo los buffers al streamsource */
          			alSourceQueueBuffers ( streamsource[0], 1, &streambuffers );
          			buffers_vacios --;
                    /* Compruebo si se ha acabado la cancion */
                    if ( contador < tamanyo_cancion){
                        break;
                    }
                }
             }
     }

     /* Cuando se acaba la cancion, paramos todo y borramos buffers y fuentes */
     alSourceStopv(1, streamsource);
     if (alGetError() != AL_NO_ERROR){
              fprintf ( logs,"No se pueden parar el streamsource\n");
     }
     alDeleteSources(1, streamsource);
     if (alGetError() != AL_NO_ERROR){
             fprintf ( logs,"No se puede borrar el stremsource\n");
     }
     alDeleteBuffers(NUM_BUFFER_MUSICA, streambuffers);
     if (alGetError() != AL_NO_ERROR){
             fprintf ( logs,"No se pueden borrar los buffers\n");
     }

     musica_on = 0;
}

/********************************************************
Funcion       : ReproducirMusica ( )
Objetivo      : reproduce la musica seleccionada
Parametros : No hay que pasarle parametros
********************************************************/

void ReproducirMusica (  ){

    	musica_on=1;

    	/* Creamos thread independiente para la musica */
    	threadmusica = SDL_CreateThread (ActualizarMusica, NULL);
    	if (threadmusica == NULL) {
		fprintf(logs,"No podemos crear el thread para la musica.\n");
    	}
}