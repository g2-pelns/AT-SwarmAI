#ifndef _MODEL_CLASS_H_
#define _MODEL_CLASS_H_

#include <d3d11.h>
#include <DirectXMath.h>

#include <fstream>
#include <memory>
#include <vector>
#include <ctime>

#include "ColorShaderClass.h"

using namespace std;
using namespace DirectX;

class ModelClass
{
public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	void ShutDown();
	bool Init(ID3D11Device*, char*);
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	int GetVertexCount();
	int GetInstanceCount();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	int m_instanceCount = 4;

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT3 instanacePosition;
	};

	struct ModelType
	{
		float x;
		float y;
		float z;
	};

	//struct InstanceType
	//{
	//	XMFLOAT3 position;
	//};

	void ShutDownBuffers();
	bool InitBuffers(ID3D11Device*);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadModel(char*);
	void ReleaseModel();

	vector<unique_ptr<ModelType>> m_model;
	//ModelType* m_model;
	ID3D11Buffer* m_instanceBuffer;
};
#endif
