#include "light.h"
#include <Qt3DCore/QTransform>

Light::Light(Qt3DCore::QEntity *rootEntity)
    : m_rootLightEntity(rootEntity)
{

}

void Light::setLightType(Light::LightType type)
{
    m_type = type;

    switch (m_type) {
    case ENVIRONMENT:
        m_environment = new Qt3DRender::QEnvironmentLight(m_rootLightEntity);
        break;
    case DIRECTIONAL:
        m_directional = new Qt3DRender::QDirectionalLight(m_rootLightEntity);
         break;
    case POINT:
        m_point = new Qt3DRender::QPointLight;
         break;
    case UNKNOW:
        // THROW
        break;
    }
}

void Light::setLightParameters(float intensity, QVector3D position)
{
    Qt3DCore::QTransform *lightTransform = new Qt3DCore::QTransform(m_rootLightEntity);

    lightTransform->setTranslation(position);

    switch (m_type) {
    case DIRECTIONAL:
        m_directional->setIntensity(intensity);
        m_directional->setColor("white");
        m_rootLightEntity->addComponent(m_directional);
        m_rootLightEntity->addComponent(lightTransform);
         break;
    case POINT:
        m_point->setIntensity(intensity);
        m_point->setColor("white");
        m_rootLightEntity->addComponent(m_point);
        m_rootLightEntity->addComponent(lightTransform);
         break;
    case UNKNOW:
        // THROW
        break;
    }
}
