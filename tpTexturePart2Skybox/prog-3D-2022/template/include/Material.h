#ifndef MATERIAL_H_DEFINED
#define MATERIAL_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct Material {
	// Shader program
	GLuint m_program;
	GLuint sphereprogram;
	GLuint skyboxprogram;

	// Material parameters
	glm::vec4 m_color;
	GLuint m_texture;
	GLuint m_textureSphere;

	bool ObjetSkybox;

	inline void check() {
		if (skyboxprogram == 0 || sphereprogram==0) {
			throw std::runtime_error("Shader program not initialized");
		}
		// if (m_program2 == 1) {
		// 	throw std::runtime_error("Shader program not initialized");
		// }
	}

	Material(): m_program(0) {

	}


	virtual ~Material();

	virtual void init();

	virtual void clear();

	void bind(bool cube);

	virtual void internalBind();

	void setMatrices(glm::mat4& projectionMatrix, glm::mat4& viewMatrix, glm::mat4& modelMatrix);

	GLint getAttribute(const std::string& in_attributeName);

	GLint getUniform(const std::string& in_uniformName);
};

#endif
