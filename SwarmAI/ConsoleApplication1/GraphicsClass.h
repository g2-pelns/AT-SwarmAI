#ifndef _GRAPHICS_CLASS_H_
#define _GRAPHICS_CLASS_H_

#include "D3dClass.h"
#include "InputClass.h"
#include "CameraClass.h"
#include "PositionClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Init(HINSTANCE,int, int, HWND);
	void HandleCamMovement(InputClass*, float);
	void ShutDown();
	bool Frame(InputClass*, float);

private:
	bool Render();
	D3dClass* m_Direct3D;
	CameraClass* m_Camera;
	InputClass* m_Input;
	PositionClass* m_Pos;
	ModelClass* m_Model;
	ColorShaderClass* m_ColorShader;
};

#endif