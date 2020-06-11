#include "scene.h"
#include "effect.h"
#include "model.h"

#include <Qt3DRender/QRenderSettings>
#include <Qt3DExtras/QForwardRenderer>

Scene::Scene(Qt3DExtras::Qt3DWindow *view, Qt3DCore::QEntity *rootEntity)
    : m_sceneEntity(new Qt3DCore::QEntity(rootEntity))
    , m_camera(new Camera(view->camera(), rootEntity))
{
    m_camera->setPerspectiveProjection(40.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0, 0, 40.0f));
    m_camera->setViewCenter(QVector3D(0, 0, 0));
    m_camera->setLinearSpeed(50.0f);
    m_camera->setLookSpeed(180.0f);

//    Qt3DExtras::QForwardRenderer *frame = new Qt3DExtras::QForwardRenderer(rootEntity);
//    frame->setCamera(m_camera->getCamera());
//    frame->setFrustumCullingEnabled(false);
//    frame->setClearColor("white");

//    Qt3DRender::QRenderSettings *render = new Qt3DRender::QRenderSettings(rootEntity);
//    render->setActiveFrameGraph(frame);

//    m_sceneEntity->addComponent(render);

    Effect *effect = new Effect(rootEntity, ":/assets/shader/skinnedPbr.vert");
    Model *model = new Model(rootEntity);

    model->addMesh(":/assets/gltf/robot.gltf");

    model->addArmature(":/assets/gltf/robot.gltf");

    model->setEffect(effect);

    model->addTexture("baseColor", ":/assets/gltf/robot_basecolor.png", Qt3DRender::QAbstractTexture::SRGB8_Alpha8);
    model->addTexture("metalness", ":/assets/gltf/robot_metallic.png");
    model->addTexture("roughness", ":/assets/gltf/robot_roughness.png");
    model->addTexture("ambientOcclusion", ":/assets/gltf/robot_occlusion.png");

    model->setScale(0.06);
}
