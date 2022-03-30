#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// ���������� ��������� ��������� ��������� �������� ������. ������������ � �������� ����������, ����� ��������� �������� �� ����������� ��� ������� ������� ������� �����
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// ��������� ������ �� ���������
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// ����������� ����� ������, ������� ������������ ������� ������ � ��������� ��������������� �������� ����, ������� � ������� ��� ������������� � OpenGL
class camera
{
public:
    //������� ��������� ������������
    float currentPositionY = 0.0f;
    // �������� ������
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    // ��������� ������
    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    bool is_running = false;

    // �����������, ������������ �������
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
    // �����������, ������������ �������
    camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM)
    {
        position = glm::vec3(posX, posY, posZ);
        world_up = glm::vec3(upX, upY, upZ);
        yaw = yaw;
        pitch = pitch;
        updateCameraVectors();
    }

    // ���������� ������� ����, ����������� � �������������� ����� ������ � LookAt-������� 
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(position, position + front, up);
    }

    //������������ ������� ������, ���������� �� ����� ������������������ ������� �����. ��������� ������� �������� � ���� ������������� ������� ������������ (��� ��������������� ��� �� ������� ������)
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

            // ����������, ��� ������������ ��������� �� �����
            position.y = currentPositionY; // ��� ������ ���������� ������������ �� ������ ����� (��������� xz)
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

    //������������ ������� ������, ���������� �� ������� ����� � ������� ����. ������� � �������� ���������� �������� �������� ��� � ����������� X, ��� � � ����������� Y.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= mouse_sensitivity;
        yoffset *= mouse_sensitivity;

        

        // ��������� �������� �������-�����, �������-������ � �������-�����, ��������� ����������� �������� ����� ������
        updateCameraVectors();
    }

    // ������������ ������� ������, ���������� �� ������� ������ ��������� ����. ���������� ������ ������� ������ �� ������������ ��� �������� 
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
    // ��������� ������-����� �� (�����������) ����� ������ ������
    void updateCameraVectors()
    {
        // ��������� ����� ������-�����
        glm::vec3 front;
        front = glm::normalize(front);
        // ����� ������������� ������-������ � ������-�����
        right = glm::normalize(glm::cross(front, world_up));  // ����������� �������, ������ ��� �� ����� ���������� ��������� � 0 ��� ������, ��� ������ �� �������� ����� ��� ����, ��� �������� � ����� ���������� ��������.
        up = glm::normalize(glm::cross(right, front));
    }
};
#endif