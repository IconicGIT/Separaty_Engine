#define STB_IMAGE_IMPLEMENTATION
#include "Stb/stb_image.h"
#include "TextureLoader.h"

Texture LoadTexture(std::string file_path)
{
	

	unsigned int texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	// load and generate the texture
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 0);
	int data_size = sizeof(data);
	int compare_data = width * height * 4;

	bool correct_data_size = !(data_size < compare_data);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture " << file_path << std::endl;
	}

	stbi_image_free(data);
	
	Texture tex;
	tex.id = texture;
	tex.path = file_path;
	tex.type = "null";
	tex.width = width;
	tex.height = height;
	tex.nrChannels = nrChannels;


return tex;
}