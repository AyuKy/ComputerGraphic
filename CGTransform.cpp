#include "pch.h"
#include "CGTransform.h"
IMPLEMENT_SERIAL(CGTransform, CGGroup, 1)
CGTransform::CGTransform()
{
}
CGTransform::~CGTransform()
{
}
void CGTransform::Serialize(CArchive& ar)
{
	CGGroup::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
bool CGTransform::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	/*for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->Render(pRC, pCamera);
	}*/

	glPushMatrix(); //����
	glMultMatrixf(glm::value_ptr(localMatrix())); //�����һ���任
	if (getRenderStateSet()) {
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		getRenderStateSet()->apply(pCamera, pRC);
	}
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->Render(pRC, pCamera);
	}
	if (getRenderStateSet()) {
		glPopAttrib();
	}
	glPopMatrix(); //�ָ�
	return true;
}

void CGTransform::dirtyWorldMatrix()
{
	mWorldMatrixDirty = true;
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		CGTransform* trans = (*itr != nullptr) ? (*itr)->asTransform() : 0;
		if (trans) {
			trans->dirtyWorldMatrix();
		}
	}
	dirtyBound();
}
void CGTransform::setLocalMatrix(const glm::mat4& m)
{
	mLocalMatrix = m;
	dirtyWorldMatrix(); //�ֲ�����仯�ᵼ�µ���������ϵ�ľ���ı䡣
}
void CGTransform::translate(float tx, float ty, float tz)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = glm::translate(mLocalMatrix, glm::vec3(tx, ty, tz));
	dirtyWorldMatrix();
}
void CGTransform::translate(const glm::vec3& t)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = glm::translate(mLocalMatrix, t);
	dirtyWorldMatrix();
}
void CGTransform::scale(float sx, float sy, float sz)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = glm::scale(mLocalMatrix, glm::vec3(sx, sy, sz));
	dirtyWorldMatrix();
}
void CGTransform::rotate(float degrees, float x, float y, float z)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = glm::rotate(mLocalMatrix, glm::radians(degrees), glm::vec3(x, y, z));
	dirtyWorldMatrix();
}
void CGTransform::rotate(float degrees, glm::vec3 t)
{// ����һ����ʾ��ת�任�ľ���
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), t);
	// ������ת�����뵱ǰ�ֲ�������ˣ��ҳˣ�
	postMultiply(rotationMatrix);
}
void CGTransform::preMultiply(const glm::mat4& m)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = m * mLocalMatrix;
	dirtyWorldMatrix();
}
void CGTransform::postMultiply(const glm::mat4& m)
{
	//���в���ʵ�ֹ���
	mLocalMatrix = mLocalMatrix * m;
	dirtyWorldMatrix();
}