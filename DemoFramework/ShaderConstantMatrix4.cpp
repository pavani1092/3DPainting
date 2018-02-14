#include "ShaderConstantMatrix4.h"
#include "OpenGL.h"
#include <string>

Crawfis::Graphics::ShaderConstantMatrix4::ShaderConstantMatrix4(std::string constantName)
{
	this->constantName = constantName;
}

Crawfis::Graphics::ShaderConstantMatrix4::~ShaderConstantMatrix4() {}

void Crawfis::Graphics::ShaderConstantMatrix4::setValue(const Crawfis::Math::Matrix4& value)
{
	this->value = value;
}
void Crawfis::Graphics::ShaderConstantMatrix4::OnLink(unsigned int shaderID)
{
	constantLocation = glGetUniformLocation(shaderID, constantName.c_str());
}

void Crawfis::Graphics::ShaderConstantMatrix4::OnShaderEnabled(unsigned int shaderID)
{
	GLenum error = glGetError();
	if (error != 0) {
		std::cout << "shader const error 1 " << gluErrorString(error) << std::endl;
	}
	if( constantLocation >= 0)
		glUniformMatrix4fv(constantLocation, 1, GL_FALSE, value.getValue());
	error = glGetError();
	if (error != 0) {
		std::cout << "shader const error "<<gluErrorString(error) << std::endl;
	}
}
