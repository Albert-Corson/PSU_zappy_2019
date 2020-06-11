#ifndef LIGHT_H
#define LIGHT_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QEnvironmentLight>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/QDirectionalLight>

class Light
{
public:
    Light(Qt3DCore::QEntity *rootEntity);

    enum LightType {
        ENVIRONMENT,
        DIRECTIONAL,
        POINT,
        UNKNOW,
    };

    void setLightType(LightType type);

    void setLightParameters(float intensity, QVector3D position);

private:
    LightType m_type = UNKNOW;
    Qt3DCore::QEntity *m_rootLightEntity;
    Qt3DRender::QEnvironmentLight *m_environment;
    Qt3DRender::QDirectionalLight *m_directional;
    Qt3DRender::QPointLight *m_point;
};

#endif // LIGHT_H
