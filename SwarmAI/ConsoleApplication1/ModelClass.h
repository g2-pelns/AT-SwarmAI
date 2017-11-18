#ifndef _MODEL_CLASS_H_
#define _MODEL_CLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

class ModelClass
{
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	void ShutDown();
	bool Init(ID3D11Device*);
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	void ShutDownBuffers();
	bool InitBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);
};
#endif
