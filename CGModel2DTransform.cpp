#include "pch.h"
#include "CGModel2DTransform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "CG2022112465杨奎Doc.h" // 包含View之前要包含Doc
#include "CG2022112465杨奎View.h" // 用户交互绘制，并将图形对象通过Doc添加到场景
#include <iostream>
CGModel2DTransform::CGModel2DTransform(
	CGNode* node,
	GLFWwindow* window,
	bool isScaleX,
	bool isScaleY,
	glm::vec3 pivotPoint,
	bool showPivot
) : UIEventHandler(window),
//mNode(node),
mIsScaleX(isScaleX),
mIsScaleY(isScaleY),
mPivotPoint(pivotPoint),
mShowPivot(showPivot),
mIsRotating(false),      // 固定默认值
mLastCursorPos(0.0),
mIsDragging(false)
{
	mNode = dynamic_cast<CGRenderable*> (node);
	if (window) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		glfwFocusWindow(window);
		mLastCursorPos = glm::dvec2(x, y);
	}
}

CGModel2DTransform::~CGModel2DTransform() = default;

EventType CGModel2DTransform::GetType()
{
	return EventType::Model2DTransform;
}

int CGModel2DTransform::OnMouseButton(GLFWwindow* window, int button, int action, int mods) {
	if (!mNode || !window) return 0;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		if (mods & GLFW_MOD_SHIFT) {
			// Shift+左键：设置旋转中心（需转换坐标）
			CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
			if (view) {
				// 转换屏幕坐标 (DCS) → 世界坐标 (WCS)
				glm::dvec3 pivotDCS(x, y, 0.0);
				mPivotPoint = view->DCS2WCS(pivotDCS); // 存储为世界坐标
				mShowPivot = true;
				// 强制刷新界面（显示旋转中心标记）
				std::string coordText = "旋转中心: (" +
					std::to_string(mPivotPoint.x) + ", " +
					std::to_string(mPivotPoint.y) + ", " +
					std::to_string(mPivotPoint.z) + ")";
				// 在界面上显示坐标
				view->ShowPrompt(coordText.c_str());  // 假设 ShowPrompt 接受 const char*
				view->Invalidate();
				view->UpdateWindow();
			}
		}
	}
	// 右键直接旋转逻辑
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			mIsRotating = true; // 开始旋转
			glm::dvec3 pivotDCS(x, y, 0.0);
			mLastCursorPos = pivotDCS;
			glfwGetCursorPos(window, &mLastCursorPos.x, &mLastCursorPos.y);
		}
		else if (action == GLFW_RELEASE) {
			mIsRotating = false; // 停止旋转
		}
	}

	return 1;
}



int CGModel2DTransform::OnCursorPos(GLFWwindow* window, double xpos, double ypos) {
	if (!mNode || !window || !mIsRotating) return 0;

	CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
	if (!view) return 0;

	glm::dvec3 currentPosDCS(xpos, ypos, 0.0);
	glm::dvec3 currentPosWCS = view->DCS2WCS(currentPosDCS);
	glm::dvec3 lastPosDCS(mLastCursorPos.x, mLastCursorPos.y, 0.0);
	glm::dvec3 lastPosWCS = view->DCS2WCS(lastPosDCS);


	double currentDx = currentPosWCS.x - mPivotPoint.x;
	double currentDy = currentPosWCS.y - mPivotPoint.y;
	double currentAngle = atan2(currentDy, currentDx);

	double lastDx = lastPosWCS.x - mPivotPoint.x;
	double lastDy = lastPosWCS.y - mPivotPoint.y;
	double lastAngle = atan2(lastDy, lastDx);


	double deltaAngleByPosition = currentAngle - lastAngle;


	if (deltaAngleByPosition > M_PI) {
		deltaAngleByPosition -= 2.0 * M_PI;
	}
	else if (deltaAngleByPosition < -M_PI) {
		deltaAngleByPosition += 2.0 * M_PI;
	}

	// 屏幕坐标位移
	double dx = xpos - mLastCursorPos.x;
	double dy = ypos - mLastCursorPos.y;
	if (deltaAngleByPosition * dx > 0)
		dx = -dx;

	// 【改正】用 dx 带方向
	const double distanceFactor = 0.5; // 可以调
	double deltaAngleByDistance = dx * distanceFactor;

	// 融合
	double deltaAngle = deltaAngleByPosition + deltaAngleByDistance;

	// 平滑
	const double smoothingFactor = 0.8;
	deltaAngle *= smoothingFactor;
	deltaAngle = -deltaAngle;
	// 显示
	std::string coordText = "旋转中心: (" + std::to_string(mPivotPoint.x) + std::to_string(mPivotPoint.y) + "），旋转角度:(" + std::to_string(deltaAngle) + ")";
	view->ShowPrompt(coordText.c_str());
	// 旋转
	mNode->Rotate(deltaAngle, mPivotPoint.x, mPivotPoint.y);

	view->Invalidate();
	view->UpdateWindow();

	mLastCursorPos = glm::dvec2(xpos, ypos);

	return 1;
}





int CGModel2DTransform::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	// 检查是否按下 Ctrl 键
	CCG2022112465杨奎View* view = (CCG2022112465杨奎View*)glfwGetWindowUserPointer(window);
	if (!view) return 0;
	bool isCtrlPressed = (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);
	if (isCtrlPressed && mNode != nullptr)
	{
		// 计算缩放因子（滚轮向上放大，向下缩小）
		double scaleFactor = (yoffset > 0) ? 1.1 : 0.9; // 10% 缩放

		// 直接调用节点的Scale方法
		mNode->Scale(
			mIsScaleX ? scaleFactor : 1.0,
			mIsScaleY ? scaleFactor : 1.0,
			mPivotPoint.x,
			mPivotPoint.y
		);
		view->ShowPrompt("已实现缩放！");
		view->Invalidate();
		view->UpdateWindow();

		return 1; // 事件已处理
	}
	return 0; // 事件未处理
}

int CGModel2DTransform::Cancel(GLFWwindow* window)
{
	mIsRotating = false;
	return 1;
}