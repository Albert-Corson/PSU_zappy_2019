#ifndef EFFECT_H
#define EFFECT_H

#include <Qt3DCore/QEntity>
#include <Qt3DRender/QFilterKey>
#include <Qt3DRender/QShaderProgram>
#include <Qt3DRender/QShaderProgramBuilder>
#include <Qt3DRender/QRenderPass>
#include <Qt3DRender/QTechnique>
#include <Qt3DRender/QEffect>

class Effect
{
public:
    Effect(Qt3DCore::QEntity *rootEntity, QString url, QStringList);

    Qt3DRender::QEffect *getEffect() const;

private:
    Qt3DRender::QEffect *m_effect;
    Qt3DRender::QFilterKey *m_filterKey;
    Qt3DRender::QShaderProgram *m_shader;
    Qt3DRender::QShaderProgramBuilder *m_builder;
    Qt3DRender::QRenderPass *m_renderPass;
    Qt3DRender::QTechnique *m_technique;
};

#endif // EFFECT_H
