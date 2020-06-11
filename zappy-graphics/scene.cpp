#include "scene.h"
#include "effect.h"
#include "model.h"
#include "light.h"
#include "animatemodel.h"

#include <Qt3DRender/QRenderSettings>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QPlaneMesh>

Scene::Scene(Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *rootEntity)
    : m_sceneEntity(new Qt3DCore::QEntity(rootEntity))
    , m_camera(new Camera(view->camera(), rootEntity))
{
    m_camera->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 40.0f, 40.0f));
    m_camera->setViewCenter(QVector3D(0, 0.0f, 0));
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

    AnimateModel *animation = new AnimateModel(model->getSkeleton(), ":/assets/animation/test.gltf", m_sceneEntity);
    model->addAnimation(animation->getAnimation());

    // Plane shape data
    Qt3DExtras::QPlaneMesh *planeMesh = new Qt3DExtras::QPlaneMesh();
    planeMesh->setWidth(20);
    planeMesh->setHeight(20);

    // Plane mesh transform
    Qt3DCore::QTransform *planeTransform = new Qt3DCore::QTransform();
    planeTransform->setScale(1.3f);
    planeTransform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

    Qt3DExtras::QPhongMaterial *planeMaterial = new Qt3DExtras::QPhongMaterial();
    planeMaterial->setDiffuse("red");

    // Plane
    auto planeEntity = new Qt3DCore::QEntity(m_sceneEntity);
    planeEntity->addComponent(planeMesh);
    planeEntity->addComponent(planeMaterial);
    planeEntity->addComponent(planeTransform);

//    Light *light = new Light(m_sceneEntity);
//    light->setLightType(Light::POINT);
//    light->setLightParameters(1, m_camera->getCamera()->position());
}
