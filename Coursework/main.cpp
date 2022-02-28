#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

#include <iostream>

int window_width = 800;
int window_height = 600;

float vertices[] = {
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
};

void framebuffer_size_callback(
	GLFWwindow* window,
	int width,
	int height
);

void process_input(GLFWwindow* window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		window_width,
		window_height,
		"Coursework init window",
		nullptr,
		nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}


	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//Shader things
	shader basic_shader("../shader/basic_shader_vert.glsl", "../shader/basic_shader_frag.glsl");

	unsigned int basic_vbo, basic_vao;
	glGenVertexArrays(1, &basic_vao);
	glGenBuffers(1, &basic_vbo);

	glBindVertexArray(basic_vao);
	glBindBuffer(GL_ARRAY_BUFFER, basic_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//coordinate atributes:
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	//Color attributes:
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Render cycle
	while (!glfwWindowShouldClose(window))
	{
		//Processing user input:
		process_input(window);

		//Performing rendering
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Render of a triangles:
		basic_shader.use();
		glBindVertexArray(basic_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Swapping contents of front and back buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Deleting vertex arrays and buffers
	glDeleteVertexArrays(1, &basic_vao);
	glDeleteBuffers(1, &basic_vbo);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(
	GLFWwindow* window,
	const int width,
	const int height
)
{

	glViewport(0, 0, width, height);

}

void process_input(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

}