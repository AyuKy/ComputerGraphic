#pragma once
//�ڵ�任�Զ�����������Ը��ݸ�����Ҫ�������
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};

