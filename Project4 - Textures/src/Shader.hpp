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
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void set4Float(const std::string& name, float v1, float v2, float v3, float v4);
};

#endif // !SHADER_HPP
