#include "camera.h"

Camera::Camera(Qt3DRender::QCamera *rootCamera, Qt3DCore::QEntity *rootEntity)
    : m_camera(rootCamera)
    , m_controller(new Qt3DExtras::QOrbitCameraController(rootEntity))
{
    m_controller->setCamera(m_camera);
}

Qt3DRender::QCamera *Camera::getCamera() const
{
    return m_camera;
}

void Camera::setPerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    m_camera->lens()->setPerspectiveProjection(fieldOfView, aspectRatio, nearPlane, farPlane);
}

void Camera::setPosition(QVector3D vect)
{
    m_camera->setPosition(vect);
}

void Camera::setViewCenter(QVector3D vect)
{
    m_camera->setViewCenter(vect);
}

void Camera::setLinearSpeed(float linearSpeed)
{
    m_controller->setLinearSpeed(linearSpeed);
}

void Camera::setLookSpeed(float lookSpeed)
{
    m_controller->setLookSpeed(lookSpeed);
}
