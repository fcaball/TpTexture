// Local includes
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>

Material::~Material()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
	}
}

void Material::init()
{
	// TODO : Change shader by your
	m_program = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	check();
	// TODO : set initial parameters
	// m_color = {1.0, 1.0, 1.0, 1.0};
	lightPos = {0., 10., 0.};
	viewPos = {0., 1., 0.};
	m_texture = loadTexture2DFromFilePath("data/brickWall.png");
	m_normaltexture = loadTexture2DFromFilePath("data/brickWallNormalMap.png");
}

void Material::clear()
{
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
	glDeleteTextures(1, &m_texture);
	glDeleteTextures(1, &m_normaltexture);
}

void Material::bind()
{
	check();
	glUseProgram(m_program);
	internalBind();
}

void Material::internalBind()
{
	// bind parameters

	if (m_texture != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(getUniform("colorText"), 0);
		glBindTexture(GL_TEXTURE_2D, m_texture);

	}

	if (m_normaltexture != -1)
	{
		glActiveTexture(GL_TEXTURE0+1);
		glUniform1i(getUniform("normalText"), 1);
		glBindTexture(GL_TEXTURE_2D, m_normaltexture);
	}

	GLint lp=getUniform("lightPos");
	glUniform3fv(lp, 1.f, glm::value_ptr(lightPos));
	GLint vp=getUniform("viewPos");
	glUniform3fv(vp, 1.f, glm::value_ptr(viewPos));
	
}

void Material::setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{	
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}

GLint Material::getAttribute(const std::string &in_attributeName)
{
	check();
	return glGetAttribLocation(m_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string &in_uniformName)
{
	check();
	return glGetUniformLocation(m_program, in_uniformName.c_str());
}
