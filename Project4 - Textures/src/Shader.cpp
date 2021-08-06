#include "Shader.hpp"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	GLuint vertexShader = compileShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShader = compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(id, 512, NULL, infoLog);
		std::cout << "Shader Program Linking Error : " << std::endl << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate()
{
	glUseProgram(id);
}

std::string Shader::loadShaderSrc(const char* filename)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string returnString = "";
	file.open(filename);
	if (file.is_open()) {
		buffer << file.rdbuf();
		returnString = buffer.str();
	}
	else {
		std::cout << "Could not open " << filename << std::endl;
	}
	file.close();
	return returnString;
}

GLuint Shader::compileShader(const char* filepath, GLenum type)
{
	GLuint returnShader = glCreateShader(type);
	std::string shaderSrc = loadShaderSrc(filepath);
	const GLchar* shader = shaderSrc.c_str();
	glShaderSource(returnShader, 1, &shader, NULL);
	glCompileShader(returnShader);

	glGetShaderiv(returnShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(returnShader, 512, NULL, infoLog);
		std::cout << "Error with Fragment Shader Compilation : " << std::endl << infoLog << std::endl;
	}
	return returnShader;
}

void Shader::setMat4(const std::string& name, glm::mat4 val)
{	
	glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::setBool(const std::string& name, bool value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::set4Float(const std::string& name, float v1, float v2, float v3, float v4) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), v1, v2, v3, v4);
}