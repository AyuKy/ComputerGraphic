#include "pch.h"
#include "CGCameraOp.h"
#include "pch.h"
#include "CG2022112465杨奎View.h"
#include "CG2022112465杨奎Doc.h"
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
    CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
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
        view->ShowPrompt("已实现移动");
    }
    return 1;
}

int CGCameraOp::OnChar(GLFWwindow* window, unsigned int codepoint)
{
    CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
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
        view->ShowPrompt("已实现移动");
    }
    return 1;
}

int CGCameraOp::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;

    // 计算缩放因子（滚轮向上放大，向下缩小）
    float scaleFactor = yoffset * 1.25f; //
    mScene->GetMainCamera()->zoomDistance(scaleFactor);
    if (view) {
        view->Invalidate();
        view->UpdateWindow();
        view->ShowPrompt("已实现移动");
    }
    return 0;
}

int CGCameraOp::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
    if (!view) return 0;
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            // 右键按下：记录初始位置
            glfwGetCursorPos(window, &mLastCursorPos.x, &mLastCursorPos.y);
            mRightButtonDown = true;
        }
        else if (action == GLFW_RELEASE) {
            // 右键释放：重置状态
            mRightButtonDown = false;
        }
        if (view) {
            view->Invalidate();
            view->UpdateWindow();
            view->ShowPrompt("已实现移动");
        }
    }
    return 0;
}

int CGCameraOp::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (mRightButtonDown) {
        // 计算增量
        double dx = xpos - mLastCursorPos.x;
        double dy = ypos - mLastCursorPos.y;

        // 更新相机旋转（调整灵敏度）
        mScene->GetMainCamera()->rotate(-dx * 0.01f, -dy * 0.01f);

        // 刷新视图
        CCG2022112465杨奎View* view = static_cast<CCG2022112465杨奎View*>(glfwGetWindowUserPointer(window));
        if (view) {
            view->Invalidate();
            view->UpdateWindow();
        }
        // 记录当前光标位置供下一帧使用
        mLastCursorPos = glm::dvec2(xpos, ypos);
    }
    return 0;
}

