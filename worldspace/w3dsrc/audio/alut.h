#ifndef _ALUT_H_
#define _ALUT_H_


#include <AL/al.h>
#include <AL/alu.h>


extern ALvoid  alutInit(ALint *argc,ALbyte **argv);
extern ALvoid  alutExit(ALvoid);
extern ALvoid  alutLoadWAVFile(ALbyte *file,ALenum *format,ALvoid **data,ALsizei *size,ALsizei *freq,ALboolean *loop);
extern ALvoid  alutLoadWAVMemory(ALbyte *memory,ALenum *format,ALvoid **data,ALsizei *size,ALsizei *freq,ALboolean *loop);
extern ALvoid  alutUnloadWAV(ALenum format,ALvoid *data,ALsizei size,ALsizei freq);

#endif
