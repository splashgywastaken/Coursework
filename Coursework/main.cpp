#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "element_sim.h"
#include "resource_manager.h"

#include <iostream>

#include "sand.h"

//TODO: Разработать отдельный класс под игровое пространство (т.е. уровень)
//TODO: В данном классе нужно реализовать подгрузку игрового поля с клетками и всё остальное
//TODO: Реализовать генерацию простой частицы с пустой текстурой (а далее уже попрёт со всеми остальными)))))

// GLFW function declarations
void framebuffer_size_callback(
    GLFWwindow* window, 
    int width, 
    int height
);
void key_callback(
    GLFWwindow* window, 
    int key, 
    int scancode, 
    int action, 
    int mode
);
void mouse_button_callback(
    GLFWwindow* window,
    int button,
    int action,
    int mods
);

// The Width of the screen
constexpr unsigned int screen_width = 800;
// The height of the screen
constexpr unsigned int screen_height = 600;

element_sim sandbox(screen_width, screen_height);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
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

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, screen_width, screen_height);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize element_sim
    // ---------------
    sandbox.init();

    // deltaTime variables
    // -------------------
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    glm::mat4 projection = glm::ortho(
        0.0f,
        800.0f,
        600.0f,
        0.0f,
        -1.0f,
        1.0f
    );

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        const float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        glfwPollEvents();

        // manage user input
        // -----------------
        

        // update element_sim state
        // -----------------
        sandbox.update(delta_time);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        sandbox.render();

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    resource_manager::clear();

    glfwTerminate();
    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        element* sand_element = new sand(
            glm::vec2(xpos, ypos),
            glm::vec2(1.0f),
            resource_manager::get_texture("face"),
            glm::vec2(0.0f, 0.0f)
        );

        sandbox.add_element_to_level(sand_element, xpos, ypos);

        /*sandbox.draw_circle(
            sand_element,
            xpos,
            ypos,
            32
        );*/
    }

}

void key_callback(
    GLFWwindow* window,
    const int key, 
    int scancode,
    const int action,
    int mode
)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            sandbox.keys[key] = true;
        else if (action == GLFW_RELEASE)
            sandbox.keys[key] = false;
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