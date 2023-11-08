#include "global.h"
char filePath[PATH_MAX];
FMODSOUND *s1;
FMODSOUND *s2;
FMODMUSIC music;
glm::mat4 viewMat = glm::mat4(1.0f);
glm::mat4 viewRotate = glm::mat4(1.0f);
glm::mat4 projMat = glm::mat4(1.0f);