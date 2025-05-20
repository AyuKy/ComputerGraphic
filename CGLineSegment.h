#pragma once
#include "CGGeometry.h"
class CGLineSegment : public CGGeometry
{
	DECLARE_SERIAL(CGLineSegment)
public:
	CGLineSegment();
	CGLineSegment(const glm::dvec3& start, const glm::dvec3& end);
	virtual ~CGLineSegment();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	
	//��άͼ�α任
	virtual void Translate(float tx, float ty); //ƽ��
	virtual void Rotate(double angle, double cx, double cy); //��ת����ʱ��Ϊ�����ȣ�
	virtual void Scale(double sx, double sy, double cx, double cy); //���ţ���������ԭ�����ţ�
protected:
	glm::dvec3 mStart;//���
	glm::dvec3 mEnd;//�յ�
	double M_PI = 3.14159265358979323846;
};