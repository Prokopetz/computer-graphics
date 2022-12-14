#include "NewShader.h"

Shader::~Shader() {}

void Shader::UseTexture(std::string textureName)
{
	glBindTexture(GL_TEXTURE_2D, textures[textureName].GetTextureId());
}

void Shader::LoadTexture(char *path, char *textureUniformName, std::string textureName)
{

	try
	{
		Texture texture = textures.at(textureName);
	}
	catch (const std::out_of_range e)
	{
		Texture tempTexture;
		tempTexture.Load(path, textureUniformName, program, textureQtd);
		textures[textureName] = tempTexture;
		textureQtd += 1;
	}
}

void Shader::setMatrix4fv(const std::string &name, glm::mat4 &matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec4(const std::string &name, glm::vec4 vec4)
{
	glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, glm::value_ptr(vec4));
}

void Shader::setVec3(const std::string &name, glm::vec3 vec3)
{
	glUniform3fv(glGetUniformLocation(this->program, name.c_str()), 1, glm::value_ptr(vec3));
}

void Shader::setFloat(const std::string &name, float f)
{
	glUniform1f(glGetUniformLocation(this->program, name.c_str()), f);
}
