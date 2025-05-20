#pragma once
#include "UIEventHandler.h" // UIEventHandler �ǻ���
#include "CGBrokenLine.h"
#include <vector>

// �������޸�Ϊ CGDraw2DBrokenLine
class CGDraw2DBrokenLine : public UIEventHandler
{
public:
	// ���캯��
	CGDraw2DBrokenLine(GLFWwindow* window);
	// ��������
	virtual ~CGDraw2DBrokenLine();
	//��������
	virtual EventType GetType() override; 
	// ������갴���¼�
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
	// ���������λ���¼�
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
	// ȡ������ִ�е�����簴ESC����
	virtual int Cancel(GLFWwindow* window) override;

protected:
	// ���ƶ�ά�ߣ�����������
	static void draw2dline(glm::dvec3& s, glm::dvec3& e);
protected:
	std::vector<glm::dvec3> mPoints; // �洢���ߵ����ж��� (��Ļ����ϵ)
	glm::dvec3 mCurrentPos; // �洢��ǰ���λ�� (��Ļ����ϵ)�����ڻ�����Ƥ����
	bool mDrawing; // ����Ƿ����ڻ�������

	// ������Ƥ���� (�����һ����ȷ���㵽��ǰ���λ��)
	glm::dvec3 mRubberBandStart; // ��Ƥ���ߵ���� (���һ��ȷ���㣬��Ļ����ϵ)
	glm::dvec3 mRubberBandEnd;   // ��Ƥ���ߵ��յ� (��ǰ���λ�ã���Ļ����ϵ)

	int mRubberBandMoveCount; // ��Ƥ�����ƶ���������
	bool mRubberBandActive;      // ��ǵ�ǰ�Ƿ�����Ƥ�������ڻ���
	glm::dvec3 mPrePos1; // �洢��һ�λ�����Ƥ����ʱ���յ�λ�� (���ڲ�������)
	glm::dvec3 mPrePos2;
};