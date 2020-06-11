#include "effect.h"
#include <Qt3DRender/QShaderProgramBuilder>
#include <Qt3DRender/QGraphicsApiFilter>

Effect::Effect(Qt3DCore::QEntity *rootEntity, QString url, QStringList enabledLayers)
    : m_effect(new Qt3DRender::QEffect(rootEntity))
    , m_filterKey(new Qt3DRender::QFilterKey(rootEntity))
    , m_shader(new Qt3DRender::QShaderProgram(rootEntity))
    , m_builder(new Qt3DRender::QShaderProgramBuilder(rootEntity))
    , m_renderPass(new Qt3DRender::QRenderPass(rootEntity))
    , m_technique(new Qt3DRender::QTechnique(rootEntity))
{
    QUrl shaderUrl = QUrl::fromLocalFile(url);

    m_filterKey->setName("renderingStyle");
    m_filterKey->setValue("forward");
    m_technique->addFilterKey(m_filterKey);

    m_shader->setVertexShaderCode(Qt3DRender::QShaderProgram::loadSource(shaderUrl));
    m_builder->setShaderProgram(m_shader);
    m_builder->setFragmentShaderGraph(QUrl("qrc:/shaders/graphs/metalrough.frag.json"));
    enabledLayers.append(QString("normal"));
    qDebug() << enabledLayers;
    m_builder->setEnabledLayers(enabledLayers);

    m_renderPass->setShaderProgram(m_shader);
    m_technique->addRenderPass(m_renderPass);

    m_technique->graphicsApiFilter()->setApi(Qt3DRender::QGraphicsApiFilter::OpenGL);
    m_technique->graphicsApiFilter()->setMajorVersion(3);
    m_technique->graphicsApiFilter()->setMinorVersion(1);
    m_technique->graphicsApiFilter()->setProfile(Qt3DRender::QGraphicsApiFilter::CoreProfile);

    m_effect->addTechnique(m_technique);
}

Qt3DRender::QEffect *Effect::getEffect() const
{
    return m_effect;
}
