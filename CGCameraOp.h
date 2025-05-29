#pragma once
#include "UIEventHandler.h"
#include "CGScene.h"
#include "CGCamera.h"
#include<iostream>
class CGCameraOp : public UIEventHandler {
public:

    bool mRightButtonDown = false;     // �Ҽ��Ƿ���
    glm::dvec2 mLastCursorPos;         // ��һ֡���λ�ã���Ļ���꣩

    std::shared_ptr<CGScene> mScene;
    CGCameraOp(GLFWwindow* window, std::shared_ptr<CGScene> scene);
    ~CGCameraOp();
    virtual EventType GetType() override;
    virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)override;
    virtual int OnChar(GLFWwindow* window, unsigned int codepoint)override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
};