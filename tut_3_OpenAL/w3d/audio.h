/* Se definen aqui las funciones relativas al audio */
#include <AL/al.h>

#ifndef AUDIO_H
#define AUDIO_H
extern int InicializarAudio (); /* Para asignar un dispositivo de audio al programa */

extern void FinalizarAudio (); /* Para cerrar la conexion entre el dispositivo de audio y el programa */

extern void ActualizarListener ( ALuint num, ALfloat x_pos, ALfloat y_pos,
                      ALfloat z_pos, ALfloat x_vel, ALfloat y_vel, ALfloat z_vel,
			    ALfloat x_sup, ALfloat y_sup, ALfloat z_sup, ALfloat x_fro,
			    ALfloat y_fro, ALfloat z_fro ); /* Actualizamos la situacion del listener */

extern void ActualizarSource ( ALuint identificador, ALfloat src_pos[3]); /* Actualizamos la situacion de la fuente */

extern void CargaSonido (  char *fichero_wav, int identificador ); /* Cargamos fichero *.wav */

extern void ReproducirSonido ( int identificador, ALfloat src_pos[3], ALfloat src_vel[3],
		      ALfloat ganancia, ALfloat pitch, ALfloat distancia_maxima, ALboolean repeticion ); /* Reproducimos fichero *.wav */

extern void ConfigurarEntorno ( ALsizei identificador, ALenum modelo,
                         ALfloat doppler_factor, ALfloat doppler_vel,
                         ALint room, ALint room_high_frequency,
                         ALfloat rolloff_factor, ALfloat decay_time,
                         ALfloat decay_high_frequency_ratio, ALint reflections,
                         ALfloat reflections_delay, ALint reverb,
                         ALfloat reverb_delay, ALfloat diffusion,
                         ALfloat density, ALfloat high_frequency_reference ); /* Se configuran propiedades del entorno */

extern void CargarMusica ( char *fichero_ogg ); /* Cargamos fichero *.ogg */

extern void ReproducirMusica (  ); /* Se reproduce la musica */

extern void PararMusica (  ); /* Se para la musica */

extern void ResetearMusica (  ); /* Se prepara todo para cargar nueva musica */

extern void ActualizarMusica (  ); /* Se realiza el streaming */

extern void ThreadMusica ( );

extern int musica_decodificada;
extern int audio_on;


#endif


