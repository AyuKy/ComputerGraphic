#include "CGRenderState.h"

class LightAnimCallback : public CGCallback {
public:
    LightAnimCallback() : mTime(0.0f) {}
    virtual bool run(CGObject* object, void* data) override {
        CGLight* light = dynamic_cast<CGLight*>(object);
        if (!light) return false;
        mTime += 0.016f; // 假设每帧约16ms
        //让光源绕Y轴旋转
        float radius = 500.0f;
        float x = radius * cos(mTime);
        float z = radius * sin(mTime);
        light->setPosition(glm::vec4(x, 500.0f, z, 1.0f));
        // 也可以动态改变类型、方向等
        return true;
    }
    float mTime;
};

class MaterialAnimCallback : public CGCallback {
public:
    MaterialAnimCallback() : mTime(0.0f) {}
    virtual bool run(CGObject* object, void* data) override {
        CGMaterial* mat = dynamic_cast<CGMaterial*>(object);
        if (!mat) return false;
        mTime += 0.016f;
        // 例：让材质颜色随时间变化
        float v = (sin(mTime) + 1.0f) * 0.5f;
        mat->setDiffuse(glm::vec4(v, 0.2f, 1.0f - v, 1.0f));
        return true;
    }
    float mTime;
};

// 头灯回调类，将光源位置设置为当前相机位置，并设置聚光灯方向
class HeadLightCallback : public CGCallback {
public:
    virtual bool run(CGObject* object, void* data) override {
        CGLight* light = dynamic_cast<CGLight*>(object);
        CGCamera* camera = static_cast<CGCamera*>(data); // 传入当前相机
        if (!light || !camera) return false;
        // 设置光源位置为相机位置
        glm::vec3 eye = camera->MEye();
        glm::vec3 target = camera->MTarget();
        glm::vec3 dir = glm::normalize(target - eye);
        light->setPosition(glm::vec4(eye, 1.0f));
        // 设置聚光灯方向
        glLightfv(light->lightID(), GL_SPOT_DIRECTION, &dir[0]);
        glLightf(light->lightID(), GL_SPOT_CUTOFF, 10.0f); // 30度锥角
        return true;
    }
};

