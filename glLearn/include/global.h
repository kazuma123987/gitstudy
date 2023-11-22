#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include "tool.h"
#include "shader.h"
#include "sound.h"
#include <camera.h>
extern char filePath[260];
extern FMODSOUND* s1;
extern FMODSOUND* s2;
extern FMODMUSIC music;
extern Camera* camera;
extern float arr_vertex[];
extern size_t arrVertex_N;
extern glm::vec3 offsetModel[10];
extern glm::vec3 offsetLight[4];
#endif