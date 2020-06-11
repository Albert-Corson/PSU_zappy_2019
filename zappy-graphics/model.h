#ifndef MODEL_H
#define MODEL_H

#include "effect.h"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QMesh>
#include <Qt3DCore/QSkeletonLoader>
#include <Qt3DCore/QArmature>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QAbstractTexture>

class Model
{
public:
    Model(Qt3DCore::QEntity *rootEntity);

    void addMesh(QString url);
    void addArmature(QString url);

    void setEffect(Effect *effect);
    void addTexture(QString name, QString url);
    void addTexture(QString name, QString url, Qt3DRender::QAbstractTexture::TextureFormat format);

    void setScale(float scale);

    void setPosition(float X, float Y);
    void setPosition(float X, float Y, float Z);

    void setPostionX(float X);
    void setPostionY(float Y);
    void setPostionZ(float Z);

    void updatePostionX(float X);
    void updatePostionY(float Y);
    void updatePostionZ(float Z);
private:
    Qt3DCore::QEntity *m_modelEntity;
    Qt3DRender::QMesh *m_mesh;
    Qt3DCore::QSkeletonLoader *m_skeleton;
    Qt3DCore::QArmature *m_armature;
    Qt3DRender::QMaterial *m_material;
    Qt3DCore::QTransform *m_transform;
    Effect *m_effect = nullptr;
    QVector3D m_position = QVector3D(0, 0, 0);
};

#endif // MODEL_H
