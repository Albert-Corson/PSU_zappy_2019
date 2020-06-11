#include "model.h"
#include <Qt3DRender/QTexture>
#include <Qt3DRender/QParameter>

Model::Model(Qt3DCore::QEntity *rootEntity)
    : m_modelEntity(new Qt3DCore::QEntity(rootEntity))
    , m_material(new Qt3DRender::QMaterial(m_modelEntity))
    , m_transform(new Qt3DCore::QTransform(m_modelEntity))
{
    m_modelEntity->addComponent(m_material);
    m_modelEntity->addComponent(m_transform);
}

void Model::addMesh(QString url)
{
    m_mesh = new Qt3DRender::QMesh(m_modelEntity);
    m_mesh->setSource(QUrl::fromLocalFile(url));
    m_modelEntity->addComponent(m_mesh);
}

void Model::addArmature(QString url)
{
    m_skeleton = new Qt3DCore::QSkeletonLoader(m_modelEntity);
    m_skeleton->setSource(QUrl::fromLocalFile(url));
    m_armature = new Qt3DCore::QArmature(m_modelEntity);
    m_armature->setSkeleton(m_skeleton);
    m_modelEntity->addComponent(m_armature);
}

void Model::addAnimation(Qt3DAnimation::QClipAnimator *animation)
{
    m_modelEntity->addComponent(animation);
}

void Model::setEffect(Effect *effect)
{
    m_effect = effect;
    m_material->setEffect(m_effect->getEffect());
}

void Model::addTexture(QString name, QString url)
{
    Qt3DRender::QTextureLoader *texture = new Qt3DRender::QTextureLoader(m_modelEntity);

    texture->setSource(QUrl::fromLocalFile(url));
    texture->setMirrored(false);
    m_enabledLayers.append(name);
    m_material->addParameter(new Qt3DRender::QParameter(name, texture, m_modelEntity));
}

void Model::addTexture(QString name, QString url, Qt3DRender::QAbstractTexture::TextureFormat format)
{
    Qt3DRender::QTextureLoader *texture = new Qt3DRender::QTextureLoader(m_modelEntity);

    texture->setSource(QUrl::fromLocalFile(url));
    texture->setMirrored(false);
    texture->setFormat(format);
    m_enabledLayers.append(name);
    m_material->addParameter(new Qt3DRender::QParameter(name, texture, m_modelEntity));
}

void Model::setScale(float scale)
{
    m_transform->setScale(scale);
}

void Model::setPosition(float X, float Y)
{
    m_position.setX(X);
    m_position.setY(Y);
    m_transform->setTranslation(m_position);
}

void Model::setPosition(float X, float Y, float Z)
{
    m_position.setX(X);
    m_position.setY(Y);
    m_position.setZ(Z);
    m_transform->setTranslation(m_position);
}

void Model::setPostionX(float X)
{
    m_position.setX(X);
    m_transform->setTranslation(m_position);
}

void Model::setPostionY(float Y)
{
    m_position.setY(Y);
    m_transform->setTranslation(m_position);
}

void Model::setPostionZ(float Z)
{
    m_position.setZ(Z);
    m_transform->setTranslation(m_position);
}

void Model::setRotationX(float X)
{
    m_transform->setRotationX(X);
}

void Model::setRotationY(float Y)
{
    m_transform->setRotationY(Y);
}

void Model::setRotationZ(float Z)
{
    m_transform->setRotationZ(Z);
}

void Model::updatePostionX(float X)
{
    m_position.setX(m_position.x() + X);
    m_transform->setTranslation(m_position);
}

void Model::updatePostionY(float Y)
{
    m_position.setY(m_position.y() + Y);
    m_transform->setTranslation(m_position);
}

void Model::updatePostionZ(float Z)
{
    m_position.setZ(m_position.z() + Z);
    m_transform->setTranslation(m_position);
}

QStringList Model::getEnabledLayers() const
{
    return m_enabledLayers;
}

Qt3DCore::QAbstractSkeleton *Model::getSkeleton() const
{
    return m_skeleton;
}

