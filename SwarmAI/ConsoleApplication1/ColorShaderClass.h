#ifndef _COLOR_SHADER_CLASS_H_
#define _COLOR_SHADER_CLASS_H_

//Includes
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>

using namespace DirectX;
using namespace std;

class ColorShaderClass
{
public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	void ShutDown();
	bool Init(ID3D11Device*, HWND);
	bool Render(ID3D11DeviceContext*, int, int, XMMATRIX&, XMMATRIX&, XMMATRIX&);

private:
	ID3D11Buffer* m_matrixBuffer;
	ID3D11InputLayout* m_layout;
	ID3D11PixelShader* m_pixelShader;
	ID3D11VertexShader* m_vertexShader;

	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	bool InitShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutDownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX&, XMMATRIX&, XMMATRIX&);
	void RenderShader(ID3D11DeviceContext*, int, int);
};

#endif