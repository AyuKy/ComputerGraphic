#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include "CGRenderable.h"
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
class CGModel2DTransform : public UIEventHandler
{
public:
	//���캯������Ҫʩ�ӱ任�Ķ������ѻ��Ƶ�ֱ�߶Ρ����ߵ�
    CGModel2DTransform(
        CGNode* node,
        GLFWwindow* window= nullptr,
        bool isScaleX = false,
        bool isScaleY = false,
        glm::vec3 pivotPoint = glm::vec3(0.0f),
        bool showPivot = false
    );
	~CGModel2DTransform();

	virtual EventType GetType() override; //��������
	//�ٶ�ʹ��������ʵ�ֶ������ţ���ס����ƶ�ʵ�ֶ���ƽ�ƣ���ס�Ҽ��ƶ�ʵ�ֶ�����ת
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

	//ȡ������ִ�е�����簴ESC����
	virtual int Cancel(GLFWwindow* window) override;
protected:
	CGRenderable* mNode; //�����ݵ�ģ��
	glm::vec3 mPivotPoint; //�任�ο��㣬��סShift+���������ȡ

    //
    bool mIsDragging;
    bool mIsRotating;
    bool mShowPivot;
    bool mIsScaleX;
    bool mIsScaleY;
    glm::dvec2 mLastCursorPos;

    const double M_PI = 3.1415926;
};
