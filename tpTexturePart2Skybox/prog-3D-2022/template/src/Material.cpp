// Local includes
#include <iostream>
#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Context.h"
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
std::vector<std::string> faces = {
	"skybox/right.jpg",
	"skybox/left.jpg",
	"skybox/top.jpg",
	"skybox/bottom.jpg",
	"skybox/front.jpg",
	"skybox/back.jpg"};

float skyboxVertices[] = {
	// positions
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f};

unsigned int skyboxVAO, skyboxVBO;

void Material::init()
{
	// TODO : Change shader by your
	skyboxprogram = load_shaders("shaders/unlit/vertex.glsl", "shaders/unlit/fragment.glsl");
	sphereprogram = load_shaders("shaders/unlit/vertex2.glsl", "shaders/unlit/fragment2.glsl");
	check();
	m_color = {1.0, 1.0, 1.0, 1.0};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

	m_texture = loadSkybox(faces);
	m_textureSphere = loadTexture2DFromFilePath("data/jean.png");
}

void Material::clear()
{
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material

	if (ObjetSkybox)
	{
		glDeleteTextures(1, &m_texture);
		glDeleteBuffers(1, &skyboxVBO);
		glDeleteVertexArrays(1, &skyboxVAO);
	}
	else
	{
		glDeleteTextures(1, &m_texture);
		glDeleteBuffers(1, &skyboxVBO);
		glDeleteVertexArrays(1, &skyboxVAO);
		glDeleteTextures(1, &m_textureSphere);
	}
}

void Material::bind(bool cube)
{
	check();
	ObjetSkybox = cube;
	if (cube)
	{
		m_program = skyboxprogram;
	}
	else
	{
		m_program = sphereprogram;
	}
	glUseProgram(m_program);

	internalBind();
}

void Material::internalBind()
{
	// bind parameters

	if (ObjetSkybox && m_texture != -1)
	{
		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
	}
	else if (m_textureSphere != -1)
	{
		glUniform1i(getUniform("Texture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureSphere);
		// glDepthMask(GL_FALSE);
		// glDepthFunc(GL_LEQUAL);
		// glBindVertexArray(skyboxVAO);
		// glActiveTexture(GL_TEXTURE0);
		// glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
		// glDrawArrays(GL_TRIANGLES, 0, 36);
		// glBindVertexArray(0);
		// glDepthFunc(GL_LESS);
		// glDepthMask(GL_TRUE);
	}
	GLuint c_p = glGetUniformLocation(sphereprogram, "cameraPos");
    glUniform3f(c_p,Context::camera.position[0], Context::camera.position[1], Context::camera.position[2]);

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
