#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow * window);
std::string loadShaderScr(const char * filename);

int main() {
	std::cout << "Hello World !" << std::endl;

	int success;
	char infoLog[512];

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow * window = glfwCreateWindow(800, 600, "Shapes", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize glad " << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Shaders - Compile Vertex Shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderSrc = loadShaderScr("assets/vertex_core.glsl");
	const GLchar * vertShader = vertShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &vertShader, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error with Vertex Shader Compilation : " << std::endl << infoLog << std::endl;
	}

	// Shaders - Compile Fragment Shader
	unsigned int fragmentShader[2];
	fragmentShader[0] = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragShaderSrc = loadShaderScr("assets/fragment_core.glsl");
	const GLchar * fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShader[0], 1, &fragShader, NULL);
	glCompileShader(fragmentShader[0]); 

	glGetShaderiv(fragmentShader[0], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader[0], 512, NULL, infoLog);
		std::cout << "Error with Fragment Shader Compilation : " << std::endl << infoLog << std::endl;
	}

	fragmentShader[1] = glCreateShader(GL_FRAGMENT_SHADER);
	fragShaderSrc = loadShaderScr("assets/fragment_core2.glsl");
	fragShader = fragShaderSrc.c_str();
	glShaderSource(fragmentShader[1], 1, &fragShader, NULL);
	glCompileShader(fragmentShader[1]);

	glGetShaderiv(fragmentShader[1], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader[1], 512, NULL, infoLog);
		std::cout << "Error with Fragment Shader Compilation : " << std::endl << infoLog << std::endl;
	}

	unsigned int shaderProgram[2];
	shaderProgram[0] = glCreateProgram();
	glAttachShader(shaderProgram[0], vertexShader);
	glAttachShader(shaderProgram[0], fragmentShader[0]);
	glLinkProgram(shaderProgram[0]);

	glGetProgramiv(shaderProgram[0], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[0], 512, NULL, infoLog);
		std::cout << "Shader Program Linking Error : " << std::endl << infoLog << std::endl;
	}

	shaderProgram[1] = glCreateProgram();
	glAttachShader(shaderProgram[1], vertexShader);
	glAttachShader(shaderProgram[1], fragmentShader[1]);
	glLinkProgram(shaderProgram[1]);

	glGetProgramiv(shaderProgram[1], GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram[1], 512, NULL, infoLog);
		std::cout << "Shader Program Linking Error : " << std::endl << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader[0]);
	glDeleteShader(fragmentShader[1]);

	// vertex array
	float vertices[] = {
		// position                color
		-0.25f, -0.5f, 0.0f,	1.0f, 1.0f, 0.5f,
		 0.15f,  0.0f, 0.0f,	0.5f, 1.0f, 0.75,
		 0.00f,  0.5f, 0.0f,	0.6f, 0.1f, 0.2f,
		 0.50f, -0.4f, 0.0f,	1.0f, 0.2f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		3, 1, 2
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glUseProgram(shaderProgram[0]);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
		// send new frames to window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

std::string loadShaderScr(const char * filename)
{
	std::ifstream file;
	std::stringstream buffer;
	std::string returnString = "";
	file.open(filename);
	if (file.is_open()) {
		buffer << file.rdbuf();
		returnString = buffer.str();
	} else {
		std::cout << "Could not open " << filename << std::endl;
	}
	file.close();
	return returnString;
}