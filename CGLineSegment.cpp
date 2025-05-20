#include "pch.h"
#include "CGLineSegment.h"
IMPLEMENT_SERIAL(CGLineSegment, CGGeometry, 1)
CGLineSegment::CGLineSegment()
	: mStart(glm::dvec3(0.0, 0.0, 0.0)), mEnd(glm::dvec3(0.0, 0.0, 0.0))
{
}
CGLineSegment::CGLineSegment(const glm::dvec3& start, const glm::dvec3& end)
	: mStart(start), mEnd(end)
{
}
CGLineSegment::~CGLineSegment()
{
}
void CGLineSegment::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
//��Ⱦ
bool CGLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ
	glBegin(GL_LINES);
	glVertex3f(mStart.x, mStart.y, mStart.z);
	glVertex3f(mEnd.x, mEnd.y, mEnd.z);
	glEnd();
	return true;
}

//��άͼ�α任
void CGLineSegment::Translate(float tx, float ty)
{
	// ƽ�Ʋ���
	mStart.x += tx;
	mStart.y += ty;
	mEnd.x += tx;
	mEnd.y += ty;
}

void CGLineSegment::Rotate(double angle, double cx, double cy)
{
	// ���Ƕ�ת��Ϊ���ȣ���Ϊ���Ǻ���ʹ�û��ȣ�
	double radians = angle * (M_PI / 180.0);

	// ������ת�����Ԫ��
	double cosTheta = cos(radians);
	double sinTheta = sin(radians);

	// ������ת����
	glm::mat2 rotationMatrix(cosTheta, sinTheta, -sinTheta, cosTheta);

	// ����������ת
	glm::dvec2 startRel = glm::dvec2(mStart.x - cx, mStart.y - cy);
	glm::dvec2 rotatedStart = rotationMatrix * startRel;
	mStart.x = rotatedStart.x + cx;
	mStart.y = rotatedStart.y + cy;

	// ���յ������ת
	glm::dvec2 endRel = glm::dvec2(mEnd.x - cx, mEnd.y - cy);
	glm::dvec2 rotatedEnd = rotationMatrix * endRel;
	mEnd.x = rotatedEnd.x + cx;
	mEnd.y = rotatedEnd.y + cy;
}

void CGLineSegment::Scale(double sx, double sy, double cx, double cy)
{
	// 1. ����ƽ�ƾ��󣨽��������ĵ��ƶ���ԭ�㣩
	glm::dmat4 translateToOrigin = glm::translate(glm::dmat4(1.0), glm::dvec3(-cx, -cy, 0.0));

	// 2. �������ž���
	glm::dmat4 scaleMatrix = glm::scale(glm::dmat4(1.0), glm::dvec3(sx, sy, 1.0));

	// 3. ��������ƽ�ƾ��󣨽����ĵ��ƻ�ԭλ�ã�
	glm::dmat4 translateBack = glm::translate(glm::dmat4(1.0), glm::dvec3(cx, cy, 0.0));

	// 4. ��ϱ任����T?? * S * T
	glm::dmat4 transformMatrix = translateBack * scaleMatrix * translateToOrigin;

	// 5. �������յ�Ӧ�ñ任
	glm::dvec4 transformedStart = transformMatrix * glm::dvec4(mStart, 1.0);
	glm::dvec4 transformedEnd = transformMatrix * glm::dvec4(mEnd, 1.0);

	// 6. �����߶ζ˵�
	mStart = glm::dvec3(transformedStart);
	mEnd = glm::dvec3(transformedEnd);
}