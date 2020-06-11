#include "scene.h"
#include "effect.h"
#include "model.h"
#include "light.h"

#include <Qt3DRender/QRenderSettings>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QConeMesh>

Scene::Scene(Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *rootEntity)
    : m_sceneEntity(new Qt3DCore::QEntity(rootEntity))
    , m_camera(new Camera(view->camera(), rootEntity))
{
    m_camera->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 40.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));
    m_camera->setLinearSpeed(50.0f);
    m_camera->setLookSpeed(180.0f);


    Model *model = new Model(rootEntity);

    model->addMesh(":/assets/gltf/robot.gltf");

    model->addArmature(":/assets/gltf/robot.gltf");

    model->addTexture("baseColorMap", ":/assets/gltf/robot_basecolor.png", Qt3DRender::QAbstractTexture::SRGB8_Alpha8);
    model->addTexture("metalnessMap", ":/assets/gltf/robot_metallic.png");
    model->addTexture("roughnessMap", ":/assets/gltf/robot_roughness.png");
    model->addTexture("ambientOcclusionMap", ":/assets/gltf/robot_occlusion.png");

    Effect *effect = new Effect(rootEntity, ":/assets/shader/skinnedPbr.vert", model->getEnabledLayers());
    model->setEffect(effect);

    model->setScale(0.06);
    model->setRotationX(90);

    Light *light = new Light(m_sceneEntity);
    light->setLightType(Light::POINT);
    light->setLightParameters(3, m_camera->getCamera()->position());
}
