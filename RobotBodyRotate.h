#pragma once
#include "CGCamera.h"
#include "RobotBodyTransformParam.h"
//��ת���»ص�ʾ��
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object); //Ҫ��任�ڵ�
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //�Ƿ����Զ������
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //���û�����Զ���������Ĭ�ϲ�������
				body->rotate(1.0f, 0.0f, 1.0f, 0.0f);
			}
			return true;
		}
		return false;
	}
};

