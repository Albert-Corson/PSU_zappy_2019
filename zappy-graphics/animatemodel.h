#ifndef ANIMATEMODEL_H
#define ANIMATEMODEL_H

#include "model.h"
#include <Qt3DAnimation/QSkeletonMapping>
#include <Qt3DAnimation/QChannelMapper>
#include <Qt3DAnimation/QClock>
#include <Qt3DAnimation/QClipAnimator>
#include <Qt3DAnimation/QAnimationClipLoader>

class AnimateModel
{
public:
    AnimateModel(Qt3DCore::QAbstractSkeleton *skeleton, QString animationUrl, Qt3DCore::QEntity *rootEntity);

    Qt3DAnimation::QClipAnimator *getAnimation() const;

private:
    Qt3DAnimation::QAnimationClipLoader *m_animationClip;
    Qt3DAnimation::QClock *m_clock;

    Qt3DAnimation::QSkeletonMapping *m_skeletonMapping;
    Qt3DAnimation::QChannelMapper *m_channelMapper;
    Qt3DAnimation::QClipAnimator *m_animation;
};

#endif // ANIMATEMODEL_H
