#ifndef CAMERA_H
#define CAMERA_H

#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QOrbitCameraController>

class Camera
{
public:
    Camera(Qt3DRender::QCamera *parent, Qt3DCore::QEntity *rootEntity);

    Qt3DRender::QCamera *getCamera() const;

    void setPerspectiveProjection(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    void setPosition(QVector3D vect);
    void setViewCenter(QVector3D vect);

    void setLinearSpeed(float linearSpeed);
    void setLookSpeed(float lookSpeed);

private:
    Qt3DRender::QCamera *m_camera;
    Qt3DExtras::QOrbitCameraController *m_controller;
};

#endif // CAMERA_H
