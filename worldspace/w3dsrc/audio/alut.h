#ifndef _ALUT_H_
#define _ALUT_H_


#include <AL/al.h>
#include <AL/alc.h>



extern ALvoid  alutLoadWAV(ALbyte *file,ALenum *format,ALvoid **data,ALsizei *size,ALsizei *freq,ALboolean *loop);
extern ALvoid  alutUnloadWAV(ALenum format,ALvoid *data,ALsizei size,ALsizei freq);

#endif
