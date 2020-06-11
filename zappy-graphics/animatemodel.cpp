#include "animatemodel.h"

AnimateModel::AnimateModel(Qt3DCore::QAbstractSkeleton *skeleton, QString animationUrl, Qt3DCore::QEntity *rootEntity)
    : m_animationClip(new Qt3DAnimation::QAnimationClipLoader(rootEntity))
    , m_clock(new Qt3DAnimation::QClock(rootEntity))
    , m_skeletonMapping(new Qt3DAnimation::QSkeletonMapping(rootEntity))
    , m_channelMapper(new Qt3DAnimation::QChannelMapper(rootEntity))
    , m_animation(new Qt3DAnimation::QClipAnimator(rootEntity))
{
    m_animationClip->setSource(QUrl::fromLocalFile(animationUrl));
    m_clock->setPlaybackRate(1.0);

    m_skeletonMapping->setSkeleton(skeleton);
    m_channelMapper->addMapping(m_skeletonMapping);

    m_animation->setChannelMapper(m_channelMapper);
    m_animation->setClock(m_clock);
    m_animation->setClip(m_animationClip);
    m_animation->setLoopCount(-1);
    m_animation->setRunning(true);
}

Qt3DAnimation::QClipAnimator *AnimateModel::getAnimation() const
{
    return m_animation;
}
