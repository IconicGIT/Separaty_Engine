#ifndef __TEXTURE_LOADER_H__
#define __TEXTURE_LOADER_H__


#include <iostream>
#include "Glew/include/GL/glew.h"
#include "Texture.h"


Texture LoadTexture(std::string file_path);

#endif // !__TEXTURE_LOADER_H__


