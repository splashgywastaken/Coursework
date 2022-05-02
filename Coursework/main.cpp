#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "element_sim.h"
#include "resource_manager.h"

#include <iostream>

#include "elements_initializer.h"

// GLFW function declarations
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

void mouse_hold(GLFWwindow* window);
float get_random_float(
    float min,
    float max
);

// Ширина экрана
constexpr unsigned int screen_width = 240;
// Высота экрана
constexpr unsigned int screen_height = 240;

bool left_mouse_button_pressed = false;
bool right_mouse_button_pressed = false;
int brush_element_id = 1;
int brush_radius = 16;

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

    // glad: подгрузка всех указателей на функции OpenGL
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

    // Спрятал курсор
    // --------------------
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // Конфигурация OpenGL
    // --------------------
    glViewport(0, 0, screen_width, screen_height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // инициализация
    // ---------------
    sandbox = new element_sim(screen_width, screen_height);
    sandbox->init();

    // deltaTime переменные
    // -------------------
    double delta_time = 0.0;
    double last_frame = 0.0;
    
    while (!glfwWindowShouldClose(window))
    {
        // Вычисление позиции мышки для обработки при рендере:
        // --------------------
        double x_position, y_position;
        glfwGetCursorPos(window, &x_position, &y_position);

        // Вычисление delta времени
        // --------------------
        const double current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        glfwPollEvents();

        // Обработка пользовательского ввода
        // -----------------
        mouse_hold(window);

        // Обновление состояния element_sim
        // -----------------
        sandbox->update(delta_time);

        // Рендер
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sandbox->render(brush_element_id, brush_radius, glm::vec2(x_position, y_position));

        glfwSwapBuffers(window);
    }

    // Удаление всех ресурсов менеджера ресурсов
    // ---------------------------------------------------------
    resource_manager::clear();

    glfwTerminate();
    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    left_mouse_button_pressed = 
        button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS;

    right_mouse_button_pressed =
        button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS;
    
}

void scroll_callback(GLFWwindow* window, const double x_offset, const double y_offset)
{
	if (y_offset < 0 && brush_radius > 1)
	{
        brush_radius--;
	}
    else if (y_offset > 0 && brush_radius <= 64)
	{
        brush_radius++;
	}
}

void mouse_hold(GLFWwindow* window)
{
    if (left_mouse_button_pressed)
    {
        double x_position, y_position;
        glfwGetCursorPos(window, &x_position, &y_position);

        sandbox->draw_circle(brush_element_id, x_position, y_position, brush_radius);
    }
    if (right_mouse_button_pressed)
    {
        double x_position, y_position;
        glfwGetCursorPos(window, &x_position, &y_position);

        sandbox->draw_circle(0, x_position, y_position, brush_radius);
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
    // когда пользователь нажимает эскейп, мы устанавливаем WindowShouldClose свойство на значение true,
    // благодаря чему закрываем приложение
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            sandbox->keys[key] = true;
        else if (action == GLFW_RELEASE)
            sandbox->keys[key] = false;
    }
    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        sandbox->clear_level();
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        sandbox->pause();
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        brush_element_id = 1;
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        brush_element_id = 2;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        brush_element_id = 3;
    }
}

void framebuffer_size_callback(
    GLFWwindow* window,
    const int width,
    const int height
)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

float get_random_float(const float min, const float max)
{
	return min + static_cast <float> (rand()) / (RAND_MAX / (max - min));
}