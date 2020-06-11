#include "light.h"

Light::Light(Qt3DCore::QEntity *rootEntity)
    : m_rootLightEntity(rootEntity)
{

}

void Light::setLightType(Light::LightType type)
{
    m_type = type;
}

void Light::setLightParameters()
{

}
