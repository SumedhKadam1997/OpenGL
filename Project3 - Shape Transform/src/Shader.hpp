#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
	unsigned int id;
	int success;
	char infoLog[512];
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate();

	// utility functions
	std::string loadShaderSrc(const char* filename);
	GLuint compileShader(const char* filepath, GLenum type);

	// uniform functions
	void setMat4(const std::string& name, glm::mat4 val);
};

#endif // !SHADER_HPP
