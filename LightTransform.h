#include "CGRenderState.h"

class LightAnimCallback : public CGCallback {
public:
    LightAnimCallback() : mTime(0.0f) {}
    virtual bool run(CGObject* object, void* data) override {
        CGLight* light = dynamic_cast<CGLight*>(object);
        if (!light) return false;
        mTime += 0.016f; // ����ÿ֡Լ16ms
        //�ù�Դ��Y����ת
        float radius = 500.0f;
        float x = radius * cos(mTime);
        float z = radius * sin(mTime);
        light->setPosition(glm::vec4(x, 500.0f, z, 1.0f));
        // Ҳ���Զ�̬�ı����͡������
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
        // �����ò�����ɫ��ʱ��仯
        float v = (sin(mTime) + 1.0f) * 0.5f;
        mat->setDiffuse(glm::vec4(v, 0.2f, 1.0f - v, 1.0f));
        return true;
    }
    float mTime;
};

// ͷ�ƻص��࣬����Դλ������Ϊ��ǰ���λ�ã������þ۹�Ʒ���
class HeadLightCallback : public CGCallback {
public:
    virtual bool run(CGObject* object, void* data) override {
        CGLight* light = dynamic_cast<CGLight*>(object);
        CGCamera* camera = static_cast<CGCamera*>(data); // ���뵱ǰ���
        if (!light || !camera) return false;
        // ���ù�Դλ��Ϊ���λ��
        glm::vec3 eye = camera->MEye();
        glm::vec3 target = camera->MTarget();
        glm::vec3 dir = glm::normalize(target - eye);
        light->setPosition(glm::vec4(eye, 1.0f));
        // ���þ۹�Ʒ���
        glLightfv(light->lightID(), GL_SPOT_DIRECTION, &dir[0]);
        glLightf(light->lightID(), GL_SPOT_CUTOFF, 10.0f); // 30��׶��
        return true;
    }
};

