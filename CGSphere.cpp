#include "pch.h"
#include "CGSphere.h"
#include "TessellationHints.h"

IMPLEMENT_SERIAL(CGSphere, CGRenderable, 1)
void CGSphere::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}
void CGSphere::buildDisplayList()
{
	TessellationHints* hints = tessellationHints();
	bool createBody = (hints ? hints->createBody() : true);
	if (createBody) {
		unsigned int mStacks = hints->targetStacks();
		unsigned int mSlices = hints->targetSlices();
		// 绘制球体的主体
		glBegin(GL_QUADS);
		// 这里可以添加绘制球体的代码
		for (int i = 0; i < mStacks; ++i) {
			float theta1 = M_PI * (float)i / (float)mStacks;
			float theta2 = M_PI * (float)(i + 1) / (float)mStacks;
			for (int j = 0; j < mSlices; ++j) {
				float phi1 = 2.0f * M_PI * (float)j / (float)mSlices;
				float phi2 = 2.0f * M_PI * (float)(j + 1) / (float)mSlices;
				// 计算顶点坐标
				glm::vec3 v1(mRadius * sin(theta1) * cos(phi1), mRadius * cos(theta1), mRadius * sin(theta1) * sin(phi1));
				glm::vec3 v2(mRadius * sin(theta2) * cos(phi1), mRadius * cos(theta2), mRadius * sin(theta2) * sin(phi1));
				glm::vec3 v3(mRadius * sin(theta2) * cos(phi2), mRadius * cos(theta2), mRadius * sin(theta2) * sin(phi2));
				glm::vec3 v4(mRadius * sin(theta1) * cos(phi2), mRadius * cos(theta1), mRadius * sin(theta1) * sin(phi2));
				// 绘制四边形
				glNormal3fv(glm::value_ptr(v1));
				glVertex3fv(glm::value_ptr(v1));
				glNormal3fv(glm::value_ptr(v2));
				glVertex3fv(glm::value_ptr(v2));
				glNormal3fv(glm::value_ptr(v3));
				glVertex3fv(glm::value_ptr(v3));
				glNormal3fv(glm::value_ptr(v4));
				glVertex3fv(glm::value_ptr(v4));
			}
		}
		glEnd();
	}
}