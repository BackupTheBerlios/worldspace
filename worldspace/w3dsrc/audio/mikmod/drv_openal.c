/*	MikMod sound library
	(c) 1998, 1999, 2000 Miodrag Vallat and others - see file AUTHORS for
	complete list.

	This library is free software; you can redistribute it and/or modify
	it under the terms of the GNU Library General Public License as
	published by the Free Software Foundation; either version 2 of
	the License, or (at your option) any later version.
 
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Library General Public License for more details.
 
	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
	02111-1307, USA.
*/

/*==============================================================================

  $Id: drv_openal.c,v 1.2 2003/04/21 10:37:45 lordloki Exp $

  Driver for output via openal.

==============================================================================*/

/*

	Written by J. Valenzuela <tsaotsao@lokigames.com>
	Modified by Jorge Bernal <lordloki@users.berlios.de>

	The driver doesn't use LOKI extensions now. It use
	Queue buffers for streaming.

*/

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mikmod_internals.h"

#include <AL/al.h>
#include <AL/alc.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define DEFBUFSIZ         4096
#define NUM_BUFFERS_MUSIC 4
#define MAXVOLUME         128.0
#define MAX_SPEC          256

int i=0;
static ALuint sid[1];
static ALuint bid[NUM_BUFFERS_MUSIC];

static ALCdevice *device;
static void *context_id;
static int sampleSize     = 2; /* in bytes */
static ALenum format      = AL_FORMAT_STEREO16; /* stereo   */
static int bufsiz         = DEFBUFSIZ;
static SBYTE *audiobuffer = NULL;

static void Openal_PlayStop(void);
static ALboolean sourceIsPlaying(ALuint sid);
static void Openal_SetupMultiChannel(void);

static void Openal_CommandLine(CHAR *cmdline)
{
	CHAR *ptr;

	ptr = MD_GetAtom("openal-bufsize", cmdline, 0);
	if(ptr != NULL) {
		bufsiz = atoi(ptr);
		free(ptr);
	}

	return;
}


static BOOL Openal_IsThere(void)
{
	/* Always here.  If there isn't a context, we create it. */

	return 1;
}


static BOOL Openal_Init(void)
{
	int attrlist[] = { ALC_FREQUENCY, 0,
					   /* ALC_BUFFERSIZE, 0, JIV FIXME*/
					   ALC_INVALID };

	attrlist[1] = md_mixfreq;
	/*
	 * JIV FIXME do something for bufsiz
	 *
	 * attrlist[3] = bufsiz;
	 */

	if(context_id == NULL)
	{
			context_id = alcGetCurrentContext();
			if(context_id == NULL)
			{
					char devspec[MAX_SPEC];

					sprintf( devspec, "'(( sampling-rate %d ))", md_mixfreq );
						
					/* FIXME: used passed params */
					device = alcOpenDevice( (ALubyte *) devspec );
					if(device == NULL)
					{
							_mm_errno = MMERR_OPENING_AUDIO;
							return 1;
					}

					context_id = alcCreateContext( device, attrlist);
					if(context_id == NULL)
					{
							alcCloseDevice( device );

							_mm_errno = MMERR_OPENING_AUDIO;
							return 1;
					}

					alcMakeContextCurrent( context_id );
			} else
			{
					/* There is already an existing openal context,
					 * so we use that, but mark context_id as NULL so
					 * that we don't try to delete it below.
					 */
					context_id = NULL;
			}
	}

	audiobuffer= _mm_malloc(bufsiz);
	if(audiobuffer == NULL) {
		_mm_errno = MMERR_OPENING_AUDIO;

		return 1;
	}

	alGenBuffers(NUM_BUFFERS_MUSIC, bid);

    /* Openal_SetupMultichannel */
	Openal_SetupMultiChannel();

	return VC_Init();
}

static void Openal_Exit(void)
{
    Openal_PlayStop();

	if(context_id == NULL) {
			alDeleteSources(1, sid);
			alDeleteBuffers(NUM_BUFFERS_MUSIC, bid);
			return;
	}

	alcDestroyContext( context_id );
	alcCloseDevice( device );
	context_id = NULL;
	device = NULL;

	_mm_free(audiobuffer);
	audiobuffer = NULL;

	return;
}

static void Openal_PlayStop(void)
{
	if(alIsSource(sid[0]) == AL_TRUE) {
        alSourceStop(sid[0]);
	}

	VC_PlayStop();

	return;
}

static void Openal_Update(void)
{

	int err = 0, loop, buffers_empty;
	ALfloat fvol;
	ALuint buffer_id;

	if(i == 0) {
			alGenSources(1, sid);
			for ( loop=0; loop < NUM_BUFFERS_MUSIC ; loop++){
				err = VC_WriteBytes(audiobuffer, DEFBUFSIZ);
   				if (err == 0){
       				break;
   				}else{
       				alBufferData ( bid[loop], format, audiobuffer , DEFBUFSIZ , md_mixfreq );
   				}
   			}
			alSource3f( sid[0], AL_POSITION, 0.0f, 0.0f, 0.0f );
			alSourcei( sid[0], AL_SOURCE_RELATIVE, AL_TRUE );
   			alSourceQueueBuffers ( sid[0], NUM_BUFFERS_MUSIC, bid );
			i=1;
	}else{
       		alGetSourcei ( sid[0], AL_BUFFERS_PROCESSED, &buffers_empty);
       		if ( buffers_empty > 0 ){
       			while ( buffers_empty ){
           			alSourceUnqueueBuffers ( sid[0], 1, &buffer_id );
               		err = VC_WriteBytes(audiobuffer, DEFBUFSIZ);
   					if (err == 0){
       					break;
   					}else{
       					alBufferData ( buffer_id, format, audiobuffer , DEFBUFSIZ , md_mixfreq );
   					}
       				alSourceQueueBuffers ( sid[0], 1, &buffer_id );
       				buffers_empty --;
       			}
       		}
	}

	if(sourceIsPlaying(sid[0]) == AL_FALSE) {
			alSourcePlay(sid[0]);
	}

	/* FIXME: is this correct? */
	fvol = (md_musicvolume + md_volume)/ (MAXVOLUME * 2);

	/* set volume */
	alSourcef(sid[0], AL_GAIN, fvol);

	return;
}

static BOOL Openal_Reset(void)
{
	
	Openal_PlayStop();

	alDeleteSources(1, sid);
	alDeleteBuffers(NUM_BUFFERS_MUSIC, bid);
	
	alGenBuffers(NUM_BUFFERS_MUSIC, bid);
	/* since we hosed out bid, resetup multi channel */
	Openal_SetupMultiChannel();
	i=0;
	
	return 0;
}

static ALboolean sourceIsPlaying(ALuint sid)
{
		ALint state;

		alGetSourcei(sid, AL_SOURCE_STATE, &state);

		if(state == AL_PLAYING) {
				return AL_TRUE;
		}

		return AL_FALSE;
}

static void Openal_SetupMultiChannel(void)
{
	int channels = (md_mode & DMODE_STEREO)?  2 : 1;
	int bits     = (md_mode & DMODE_16BITS)? 16 : 8;

	switch(channels) {
			case 1:format = bits==8?AL_FORMAT_MONO8:AL_FORMAT_MONO16; break;
			case 2:format = bits==8?AL_FORMAT_STEREO8:AL_FORMAT_STEREO16; break;
			default: format = 0;
	}

	sampleSize = channels;

	return;
}

MIKMODAPI MDRIVER drv_openal = {
	NULL,
	"OpenAL Sound System",
	"OpenAL Sound System driver v1.0",
	0,255,
	"openal",

	Openal_CommandLine,
	Openal_IsThere,

	VC_SampleLoad,
	VC_SampleUnload,
	VC_SampleSpace,
	VC_SampleLength,

	Openal_Init,
	Openal_Exit,
	Openal_Reset,

	VC_SetNumVoices,
	VC_PlayStart,

	Openal_PlayStop,
	Openal_Update,

	NULL,
	VC_VoiceSetVolume,
	VC_VoiceGetVolume,
	VC_VoiceSetFrequency,
	VC_VoiceGetFrequency,
	VC_VoiceSetPanning,
	VC_VoiceGetPanning,
	VC_VoicePlay,
	VC_VoiceStop,
	VC_VoiceStopped,
	VC_VoiceGetPosition,
	VC_VoiceRealVolume
};



/* ex:set ts=4: vim:set ts=4 */
