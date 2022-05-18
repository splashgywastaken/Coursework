#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "element_sim.h"
#include "resource_manager.h"

#include <iostream>

#include "elements_initializer.h"

// ����������� ������� GLFW
void framebuffer_size_callback(
    GLFWwindow* window, 
    int width, 
    int height
);
void key_callback(
    GLFWwindow* window, 
    int key, 
    int scan_code, 
    int action, 
    int mode
);
void mouse_button_callback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
);
void scroll_callback(
    GLFWwindow* window, 
    double x_offset, 
    double y_offset
);

// ������ ������
constexpr unsigned int screen_width = 240;
// ������ ������
constexpr unsigned int screen_height = 240;

element_sim* sandbox;

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = 
        glfwCreateWindow(
            screen_width,
            screen_height,
            "Sandbox",
            nullptr,
            nullptr
        );
    glfwMakeContextCurrent(window);

    // glad: ��������� ���� ���������� �� ������� OpenGL
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // ������� ������
    // --------------------
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // ������������ OpenGL
    // --------------------
    glViewport(0, 0, screen_width, screen_height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // �������������
    // ---------------
    sandbox = new element_sim(screen_width, screen_height);
    sandbox->init();

    // deltaTime ����������
    // -------------------
    int number_of_frames = 0;
    double last_time = glfwGetTime();
    
    while (!glfwWindowShouldClose(window))
    {
        // ���������� ������� ����� ��� ��������� ��� �������:
        // --------------------
        double x_position, y_position;
        glfwGetCursorPos(window, &x_position, &y_position);

        // ���������� delta �������
        // --------------------
        const double current_time = glfwGetTime();
        const double delta_time = current_time - last_time;
        number_of_frames++;
        if (delta_time >= 1.0)
        {
            sandbox->set_fps(number_of_frames);
            number_of_frames = 0;
            last_time += 1.0;
        }
        glfwPollEvents();
        // ��������� ����������������� �����
        // -----------------
        sandbox->process_input(x_position, y_position);

        // ���������� ��������� element_sim
        // -----------------
        sandbox->update(delta_time);

        // ������
        // ------
        glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        sandbox->render(glm::vec2(x_position, y_position));

        glfwSwapBuffers(window);
    }

    // �������� ���� �������� ��������� ��������
    // ---------------------------------------------------------
    resource_manager::clear();

    glfwTerminate();
    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= 0 && button < 3)
    {
        if (action == GLFW_PRESS)
        {
            sandbox->mouse_buttons[button] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            sandbox->mouse_buttons[button] = false;
        }
    }
}

void scroll_callback(GLFWwindow* window, const double x_offset, const double y_offset)
{
	if (y_offset < 0)
	{
        sandbox->change_brush_size(-1);
	}
    else if (y_offset > 0)
	{
        sandbox->change_brush_size(1);
	}
}

void key_callback(
    GLFWwindow* window,
    const int key, 
    int scan_code,
    const int action,
    int mode
)
{
    // ����� ������������ �������� ������, �� ������������� WindowShouldClose �������� �� �������� true,
    // ��������� ���� ��������� ����������
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
	    glfwSetWindowShouldClose(window, true);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
	        sandbox->pressed_keys[key] = true;
        }
    }
}

void framebuffer_size_callback(
    GLFWwindow* window,
    const int width,
    const int height
)
{
    glViewport(0, 0, width, height);
}