#include "pch.h"
#include "CGCameraOp.h"
#include "pch.h"
#include "CG2022112465���View.h"
#include "CG2022112465���Doc.h"
#include "CGCamera.h"
#include "CGScene.h"


CGCameraOp::CGCameraOp(GLFWwindow* window, std::shared_ptr<CGScene> scene)
    : UIEventHandler(window), mScene(scene) {
}
CGCameraOp::~CGCameraOp() = default;
EventType CGCameraOp::GetType()
{
    return EventType::CameraTransform;
}

int CGCameraOp::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    CCG2022112465���View* view = (CCG2022112465���View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;

    if (key == GLFW_KEY_T && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setTopView();
    }
    if (key == GLFW_KEY_D && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setBottomView();
    }
    if (key == GLFW_KEY_L && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setLeftView();
    }
    if (key == GLFW_KEY_R && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setRightView();
    }
    if (key == GLFW_KEY_F && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setFrontView();
    }
    if (key == GLFW_KEY_B && (mods & GLFW_MOD_CONTROL) && action == GLFW_PRESS) {
        mScene->GetMainCamera()->setBackView();
    }
    if (view) {
        view->Invalidate();
        view->UpdateWindow();
        view->ShowPrompt("��ʵ���ƶ�");
    }
    return 1;
}

int CGCameraOp::OnChar(GLFWwindow* window, unsigned int codepoint)
{
    CCG2022112465���View* view = (CCG2022112465���View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;
    switch (codepoint) {
    case '+':mScene->GetMainCamera()->zoom(0.8f); break;
    case '-':mScene->GetMainCamera()->zoom(1.25f); break;
    case 'L':mScene->GetMainCamera()->adjustLeft(-10); break;
    case 'l':mScene->GetMainCamera()->adjustLeft(10); break;
    case 'R':mScene->GetMainCamera()->adjustRight(10); break;
    case 'r':mScene->GetMainCamera()->adjustRight(-10); break;
    case 'T':mScene->GetMainCamera()->adjustTop(10); break;
    case 't':mScene->GetMainCamera()->adjustTop(-10); break;
    case 'B':mScene->GetMainCamera()->adjustBottom(-10); break;
    case 'b':mScene->GetMainCamera()->adjustBottom(10); break;
    case 'P': mScene->GetMainCamera()->SetProjectionMode(1); break;
    case 'O': mScene->GetMainCamera()->SetProjectionMode(0); break;
    }
    if (view) {
        view->Invalidate();
        view->UpdateWindow();
        view->ShowPrompt("��ʵ���ƶ�");
    }
    return 1;
}

int CGCameraOp::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    CCG2022112465���View* view = (CCG2022112465���View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;

    // �����������ӣ��������ϷŴ�������С��
    float scaleFactor = yoffset * 1.25f; //
    mScene->GetMainCamera()->zoomDistance(scaleFactor);
    if (view) {
        view->Invalidate();
        view->UpdateWindow();
        view->ShowPrompt("��ʵ���ƶ�");
    }
    return 0;
}

int CGCameraOp::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    CCG2022112465���View* view = (CCG2022112465���View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            // �Ҽ����£���¼��ʼλ��
            glfwGetCursorPos(window, &mLastCursorPos.x, &mLastCursorPos.y);
            mRightButtonDown = true;
        }
        else if (action == GLFW_RELEASE) {
            // �Ҽ��ͷţ�����״̬
            mRightButtonDown = false;
        }
        if (view) {
            view->Invalidate();
            view->UpdateWindow();
            view->ShowPrompt("��ʵ���ƶ�");
        }
    }
    return 0;
}

int CGCameraOp::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (mRightButtonDown) {
        // ��������
        double dx = xpos - mLastCursorPos.x;
        double dy = ypos - mLastCursorPos.y;

        // ���������ת�����������ȣ�
        mScene->GetMainCamera()->rotate(-dx * 0.01f, -dy * 0.01f);

        // ˢ����ͼ
        CCG2022112465���View* view = static_cast<CCG2022112465���View*>(glfwGetWindowUserPointer(window));
        if (view) {
            view->Invalidate();
            view->UpdateWindow();
        }
        // ��¼��ǰ���λ�ù���һ֡ʹ��
        mLastCursorPos = glm::dvec2(xpos, ypos);
    }
    return 0;
}

