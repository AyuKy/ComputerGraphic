#pragma once
#include "CGCamera.h"
#include "RobotBodyTransformParam.h"
//旋转更新回调示例
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object); //要求变换节点
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //是否传入自定义参数
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //如果没传入自定参数，按默认参数进行
				body->rotate(1.0f, 0.0f, 1.0f, 0.0f);
			}
			return true;
		}
		return false;
	}
};

