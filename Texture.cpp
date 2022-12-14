#include"texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {

	type = texType;


	//Defines texture Attributesx
	int imgWidth, imgHeight, colorChannel;
	//Flips orientation of texture to Normal orientation.
	stbi_set_flip_vertically_on_load(true);

    //Reads an img texture File
	unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &colorChannel, 0);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);
	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);



	// Assigns the image to the OpenGL Texture object
	glTexImage2D(texType, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);
	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUniform = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUniform, unit);
}

//Binds texture to the Shader Prog
void Texture::Bind()
{
	glBindTexture(type, ID);
}

//Unbinds Texture from Shader Prog
void Texture::Unbind()
{
	glBindTexture(type, 0);
}

//Deletes texture Altogether, cleaning the pipeline.
void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
