#pragma once
#include "CGRenderable.h"

class TessellationHints;
class CGSphere :public CGRenderable
{
    DECLARE_SERIAL(CGSphere)
public:
    CGSphere()
        : mRadius(1.0f)/*, mSlices(40), mStacks(20) */ {
    }
    CGSphere(float radius/*, unsigned int slices, unsigned int stacks*/)
        : mRadius(radius)/*, mSlices(slices), mStacks(stacks) */ {
    }
    CGSphere(const CGSphere& box) :
        mRadius(box.mRadius) {
    }
    virtual ~CGSphere() {}

    void setRadius(float r) { mRadius = r; }
    float getRadius() const { return mRadius; }

    void setTessellationHints(std::shared_ptr<TessellationHints> hints);
    TessellationHints* tessellationHints() { return mTessellationHints.get(); }
    const TessellationHints* tessellationHints() const { return mTessellationHints.get(); }

    virtual void buildDisplayList(); //重写基类虚函数
protected:
    float mRadius;
    std::shared_ptr<TessellationHints> mTessellationHints = nullptr;
    const float M_PI = 3.14159265358979323846f;
};

