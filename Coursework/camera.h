#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Определяет несколько возможных вариантов движения камеры. Используется в качестве абстракции, чтобы держаться подальше от специфичных для оконной системы методов ввода
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Параметры камеры по умолчанию
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// Абстрактный класс камеры, который обрабатывает входные данные и вычисляет соответствующие Эйлеровы углы, векторы и матрицы для использования в OpenGL
class camera
{
public:
    //Атрибут положения пользователя
    float currentPositionY = 0.0f;
    // Атрибуты камеры
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    // Настройки камеры
    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    bool is_running = false;

    // Конструктор, использующий векторы
    explicit camera(
        glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float camera_yaw = YAW, 
        float camera_pitch = PITCH)
	:   front(glm::vec3(0.0f, 0.0f, -1.0f)),
	    world_up(up), movement_speed(SPEED),
		mouse_sensitivity(SENSITIVITY),
		zoom(ZOOM)
    {
        position = position;
        updateCameraVectors();
    }
    // Конструктор, использующие скаляры
    camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = glm::vec3(posX, posY, posZ);
        world_up = glm::vec3(upX, upY, upZ);
        yaw = yaw;
        pitch = pitch;
        updateCameraVectors();
    }

    // Возвращает матрицу вида, вычисленную с использованием углов Эйлера и LookAt-матрицы 
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    //Обрабатываем входные данные, полученные от любой клавиатуроподобной системы ввода. Принимаем входной параметр в виде определенного камерой перечисления (для абстрагирования его от оконных систем)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {

        float velocity = movement_speed * deltaTime;
        if (direction != UP && direction != DOWN)
        {
            if (direction == FORWARD)
                position += front * velocity;
            if (direction == BACKWARD)
                position -= front * velocity;
            if (direction == LEFT)
                position -= right * velocity;
            if (direction == RIGHT)
                position += right * velocity;

            // Убеждаемся, что пользователь находится на земле
            position.y = currentPositionY; // эта строка удерживает пользователя на уровне земли (плоскость xz)
        }

        if (direction == UP)
        {
            position += up * (velocity / 2);
            currentPositionY = position.y;
        }

        if (direction == DOWN)
        {
            position -= up * (velocity / 2);
            currentPositionY = position.y;
        }


    }

    //Обрабатываем входные данные, полученные от системы ввода с помощью мыши. Ожидаем в качестве параметров значения смещения как в направлении X, так и в направлении Y.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= mouse_sensitivity;
        yoffset *= mouse_sensitivity;

        

        // Обновляем значения вектора-прямо, вектора-вправо и вектора-вверх, используя обновленные значения углов Эйлера
        updateCameraVectors();
    }

    // Обрабатывает входные данные, полученные от события колеса прокрутки мыши. Интересуют только входные данные на вертикальную ось колесика 
    void ProcessMouseScroll(float yoffset)
    {

        if (zoom < 45.0f && zoom > 1.0f) {
            zoom -= static_cast<float>(yoffset);
        }
        else if (zoom == 46.0f) {
            zoom = 44.0f;
        }
        else {
            if (zoom == 45.0f && yoffset > 0)
                zoom = 44.0f;
            if (zoom == 1.0f && yoffset < 0)
                zoom = 2.0f;
        }
    }

private:
    // Вычисляет вектор-прямо по (обновленным) углам Эйлера камеры
    void updateCameraVectors()
    {
        // Вычисляем новый вектор-прямо
        glm::vec3 front;
        front = glm::normalize(front);
        // Также пересчитываем вектор-вправо и вектор-вверх
        right = glm::normalize(glm::cross(front, world_up));  // Нормализуем векторы, потому что их длина становится стремится к 0 тем больше, чем больше вы смотрите вверх или вниз, что приводит к более медленному движению.
        up = glm::normalize(glm::cross(right, front));
    }
};
#endif