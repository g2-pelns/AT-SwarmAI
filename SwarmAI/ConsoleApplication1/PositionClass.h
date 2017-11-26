#ifndef _POSITION_CLASS_H_
#define _POSITION_CLASS_H_

#include <math.h>
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void SetPos(float, float, float);
	void SetRot(float, float, float);

	float GetPosX();
	float GetPosY();
	float GetPosZ();

	void GetRot(float&, float&, float&);

	void SetFrameTime(float);

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
};

#endif