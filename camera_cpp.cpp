#include "Camera.h"
#include <algorithm>

Camera::Camera(float aspectRatio) : aspectRatio(aspectRatio) {
    updateVectors();
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    glm::mat4 proj = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    proj[1][1] *= -1; // Flip Y для Vulkan
    return proj;
}

glm::vec3 Camera::getPosition() const {
    return position;
}

void Camera::rotate(float deltaX, float deltaY) {
    phi += deltaX * rotationSpeed;
    theta -= deltaY * rotationSpeed;
    
    // Ограничение угла по вертикали
    theta = std::clamp(theta, 1.0f, 179.0f);
    
    updateVectors();
}

void Camera::zoom(float delta) {
    radius -= delta * zoomSpeed;
    radius = std::clamp(radius, minRadius, maxRadius);
    
    updateVectors();
}

void Camera::setAspectRatio(float aspectRatio) {
    this->aspectRatio = aspectRatio;
}

void Camera::updateVectors() {
    // Сферические координаты в декартовы
    float thetaRad = glm::radians(theta);
    float phiRad = glm::radians(phi);
    
    position.x = target.x + radius * sin(thetaRad) * cos(phiRad);
    position.y = target.y + radius * cos(thetaRad);
    position.z = target.z + radius * sin(thetaRad) * sin(phiRad);
}