#include "GraphicsClass.h"
#include <string>

GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Input = 0;
	m_Pos = 0;
	m_Model = 0;
	m_ColorShader = 0;
}

GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}

GraphicsClass::~GraphicsClass()
{
}

bool GraphicsClass::Init(HINSTANCE hinstance,int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	//Create the Direct3D object
	m_Direct3D = new D3dClass;
	if (!m_Direct3D)
	{
		return false;
	}

	//Initialize the Direct3D object
	result = m_Direct3D->Init(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}


	//Create pos object
	m_Pos = new PositionClass;
	if (!m_Pos)
	{
		return false;
	}

	//Set the initial pos and rot
	m_Pos->SetPos(0.0f, 0.0f, -4.0f);
	m_Pos->SetRot(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -4.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Init(m_Direct3D->GetDevice(), "../ConsoleApplication1/Cube.txt");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the color shader object.
	result = m_ColorShader->Init(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	return true;
}

void GraphicsClass::ShutDown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->ShutDown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->ShutDown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	if (m_Pos)
	{
		delete m_Pos;
		m_Pos = 0;
	}

	//Release the Direct3D object
	if (m_Direct3D)
	{
		m_Direct3D->ShutDown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
	return;
}

bool GraphicsClass::Frame(InputClass* Input, float frameTime)
{
	bool result;

	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	HandleCamMovement(m_Input, frameTime);
	//Render the graphics scene
	result = Render();
	if (!result)
	{
		return false;
	}
	return true;
}

void GraphicsClass::HandleCamMovement(InputClass* input, float frameTime)
{
	bool result;
	bool keyDown;
	bool testKey = true;
	float posX, posY, posZ, rotX, rotY, rotZ;

	//Set the frame time for calculating the updated position
	m_Pos->SetFrameTime(frameTime);

	//Position X & Z
	keyDown = input->IsLeftPressed();
	m_Pos->MoveLeft(keyDown);

	keyDown = input->IsRightPressed();
	m_Pos->MoveRight(keyDown);

	keyDown = input->IsUpPressed();
	m_Pos->MoveForward(keyDown);

	keyDown = input->IsDownPressed();
	m_Pos->MoveBackward(keyDown);


	//Rotation
	keyDown = input->IsWPressed();
	m_Pos->LookUpward(keyDown);

	keyDown = input->IsAPressed();
	m_Pos->TurnLeft(keyDown);

	keyDown = input->IsSPressed();
	m_Pos->LookDownward(keyDown);

	keyDown = input->IsDPressed();
	m_Pos->TurnRight(keyDown);


	//Position Y
	keyDown = input->IsPgUpPressed();
	m_Pos->MoveUpward(keyDown);

	keyDown = input->IsPgDownPressed();
	m_Pos->MoveDownward(keyDown);

	// Get the view point position/rotation.
	//m_Pos->GetPos(posX, posY, posZ);

	posX = m_Pos->GetPosX();
	posY = m_Pos->GetPosY();
	posZ = m_Pos->GetPosZ();

	m_Pos->GetRot(rotX, rotY, rotZ);

	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	/*char x[256];
	int i = int(posX);
	sprintf(x, "X: %d\n", i);
	OutputDebugStringA(x);*/
	
	//sprintf(x, "My variable is %d\n", posX);
	//OutputDebugString((LPCWSTR)x);

	/*result = Render();
	if (!result)
	{
		return;
	}*/
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, baseViewMatrix, orthoMatrix;
	bool result;
	
	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.5f, 0.1f, 0.3f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	
	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the color shader.
	result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}
