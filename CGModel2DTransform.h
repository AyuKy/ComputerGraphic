#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include "CGRenderable.h"
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
class CGModel2DTransform : public UIEventHandler
{
public:
	//构造函数传入要施加变换的对象，如已绘制的直线段、折线等
    CGModel2DTransform(
        CGNode* node,
        GLFWwindow* window= nullptr,
        bool isScaleX = false,
        bool isScaleY = false,
        glm::vec3 pivotPoint = glm::vec3(0.0f),
        bool showPivot = false
    );
	~CGModel2DTransform();

	virtual EventType GetType() override; //命令类型
	//假定使用鼠标滚动实现对象缩放，按住左键移动实现对象平移，按住右键移动实现对象旋转
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

	//取消正在执行的命令（如按ESC键）
	virtual int Cancel(GLFWwindow* window) override;
protected:
	CGRenderable* mNode; //被操纵的模型
	glm::vec3 mPivotPoint; //变换参考点，按住Shift+左键单击获取

    //
    bool mIsDragging;
    bool mIsRotating;
    bool mShowPivot;
    bool mIsScaleX;
    bool mIsScaleY;
    glm::dvec2 mLastCursorPos;

    const double M_PI = 3.1415926;
};
