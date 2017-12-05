#include "positionclass.h"
#include <Windows.h>

PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 1.0f;

	//Position
	m_forwardSpeed = 0.1f;
	m_backwardSpeed = 0.1f;

	m_upwardSpeed = 0.01f;
	m_downwardSpeed = 0.01f;

	//Rotation
	m_leftTurnSpeed = 0.1f;
	m_rightTurnSpeed = 0.1f;
	m_lookUpSpeed = 0.1f;
	m_lookDownSpeed = 0.1f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPos(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRot(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


float PositionClass::GetPosX()
{
	float x = m_positionX;
	return x;
}

float PositionClass::GetPosY()
{
	float y = m_positionY;
	return y;
}

float PositionClass::GetPosZ()
{
	float z = m_positionZ;
	return z;
}

void PositionClass::GetRot(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void PositionClass::MoveForward(bool keyDown)
{
	float radians;
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keyDown)
	{
		/*m_forwardSpeed += m_frameTime * 1.0f;
		if (m_forwardSpeed > (m_frameTime * 50.0f))
		{
			m_forwardSpeed = m_frameTime * 50.0f;
		}*/
		
	// Convert degrees to radians.
	radians = m_rotationY * 0.0174532925f;

	// Update the position.
	//m_positionX += m_forwardSpeed;
	//m_positionX += 0.01f;
	m_positionZ += m_forwardSpeed;
	}
	//OutputDebugStringW(L"MoveForward");
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}
	return;
}


void PositionClass::MoveBackward(bool keydown)
{
	float radians;


	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_backwardSpeed += m_frameTime * 1.0f;

		if (m_backwardSpeed > (m_frameTime * 50.0f))
		{
			m_backwardSpeed = m_frameTime * 50.0f;
		}*/
		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		// Update the position.
		//m_positionX -= sinf(radians) * m_backwardSpeed;
		//m_positionZ -= cosf(radians) * m_backwardSpeed;
		m_positionZ -= m_backwardSpeed;
		//OutputDebugStringW(L"MoveBack");
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.5f;

		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	return;
}

void PositionClass::MoveLeft(bool keyDown)
{
	float radians;
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keyDown)
	{
		/*m_forwardSpeed += m_frameTime * 1.0f;
		if (m_forwardSpeed > (m_frameTime * 50.0f))
		{
		m_forwardSpeed = m_frameTime * 50.0f;
		}*/

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		// Update the position.
		//m_positionX += m_forwardSpeed;
		//m_positionX += 0.01f;
		m_positionX -= m_forwardSpeed;
	}
	//OutputDebugStringW(L"MoveForward");
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}
	return;
}

void PositionClass::MoveRight(bool keyDown)
{
	float radians;
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keyDown)
	{
		/*m_forwardSpeed += m_frameTime * 1.0f;
		if (m_forwardSpeed > (m_frameTime * 50.0f))
		{
		m_forwardSpeed = m_frameTime * 50.0f;
		}*/

		// Convert degrees to radians.
		radians = m_rotationY * 0.0174532925f;

		// Update the position.
		//m_positionX += m_forwardSpeed;
		//m_positionX += 0.01f;
		m_positionX += m_forwardSpeed;
	}
	//OutputDebugStringW(L"MoveForward");
	else
	{
		m_forwardSpeed -= m_frameTime * 0.5f;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}
	return;
}


void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_upwardSpeed += m_frameTime * 1.5f;

		if (m_upwardSpeed > (m_frameTime * 15.0f))
		{
			m_upwardSpeed = m_frameTime * 15.0f;
		}*/
		//OutputDebugStringW(L"MoveUp");
	// Update the height position.
	m_positionY += m_upwardSpeed;
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.5f;

		if (m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	return;
}


void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_downwardSpeed += m_frameTime * 1.5f;

		if (m_downwardSpeed > (m_frameTime * 15.0f))
		{
			m_downwardSpeed = m_frameTime * 15.0f;
		}*/
		//OutputDebugStringW(L"MoveDown");
	
	// Update the height position.
	m_positionY -= m_downwardSpeed;
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.5f;

		if (m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	return;
}


void PositionClass::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_leftTurnSpeed += m_frameTime * 5.0f;

		if (m_leftTurnSpeed > (m_frameTime * 150.0f))
		{
			m_leftTurnSpeed = m_frameTime * 150.0f;
		}*/
		//OutputDebugStringW(L"TurnLeft");
		// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 3.5f;

		if (m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}



	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}


void PositionClass::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_rightTurnSpeed += m_frameTime * 5.0f;

		if (m_rightTurnSpeed > (m_frameTime * 150.0f))
		{
			m_rightTurnSpeed = m_frameTime * 150.0f;
		}*/
		//OutputDebugStringW(L"MoveRight");
	
	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 3.5f;

		if (m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}


	// Keep the rotation in the 0 to 360 range.
	if (m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}


void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_lookUpSpeed += m_frameTime * 7.5f;

		if (m_lookUpSpeed > (m_frameTime * 75.0f))
		{
			m_lookUpSpeed = m_frameTime * 75.0f;
		}*/
		//OutputDebugStringW(L"LookUp");
	
	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 2.0f;

		if (m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Keep the rotation maximum 90 degrees.
	if (m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}


void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		/*m_lookDownSpeed += m_frameTime * 7.5f;

		if (m_lookDownSpeed > (m_frameTime * 75.0f))
		{
			m_lookDownSpeed = m_frameTime * 75.0f;
		}*/
		//OutputDebugStringW(L"LookDown");
	
	// Update the rotation.
	m_rotationX += m_lookDownSpeed;
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 2.0f;

		if (m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}


	// Keep the rotation maximum 90 degrees.
	if (m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}