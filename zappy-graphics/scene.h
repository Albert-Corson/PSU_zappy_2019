#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include <Qt3DExtras/Qt3DWindow>

class Scene
{
public:
    Scene(Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *rootEntity);

private:
    Qt3DCore::QEntity *m_sceneEntity;
    Camera *m_camera;
};

#endif // SCENE_H
