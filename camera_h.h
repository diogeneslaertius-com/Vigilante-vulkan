#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(float aspectRatio);
    
    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix() const;
    glm::vec3 getPosition() const;
    
    void rotate(float deltaX, float deltaY);
    void zoom(float delta);
    void setAspectRatio(float aspectRatio);
    
private:
    void updateVectors();
    
    // Параметры камеры
    float radius = 5.0f;
    float theta = 45.0f;  // Угол по вертикали (в градусах)
    float phi = 45.0f;    // Угол по горизонтали (в градусах)
    
    glm::vec3 position;
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    // Проекция
    float fov = 45.0f;
    float aspectRatio;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;
    
    // Чувствительность
    float rotationSpeed = 0.3f;
    float zoomSpeed = 0.5f;
    float minRadius = 2.0f;
    float maxRadius = 20.0f;
};