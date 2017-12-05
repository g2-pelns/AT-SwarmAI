#include "ModelClass.h"

ModelClass::ModelClass()
{
	m_instanceBuffer = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_model = 0;
}

ModelClass::ModelClass(const ModelClass &)
{
}

ModelClass::~ModelClass()
{
}

void ModelClass::ShutDown()
{
	ShutDownBuffers();
	ReleaseModel();
	return;
}

bool ModelClass::Init(ID3D11Device* device, char* modelFileName)
{
	bool result;

	//Load in the model data
	result = LoadModel(modelFileName);
	if (!result)
	{
		return false;
	}

	//Initalize the vertex and index buffers
	result = InitBuffers(device);
	if (!result)
	{
		return false;
	}
	return true;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	//Put the vertex and index buffers on the graphics pipeline to prepare them for drawing
	RenderBuffers(deviceContext);
	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}

int ModelClass::GetInstanceCount()
{
	return m_instanceCount;
}
void ModelClass::ShutDownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	//Release the instance buffer
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	return;
}

bool ModelClass::LoadModel(char* fileName)
{
	ifstream fin;
	char input = 0;
	int i;

	//Open the model file
	fin.open(fileName);

	//if cound not open the file then exit
	if (fin.fail())
	{
		return false;
	}

	//Read up to the value of vertex count
	//fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	//Read in the vertex count
	m_vertexCount = input;

	//Set the number of indices to be the same as the vertex count
	m_indexCount = m_vertexCount;

	//Create the model using the vertex count that was read in
	m_model = new ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	//Read up to the beginning of the data
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	//fin.get(input);
	//fin.get(input);

	//Read the vertex data
	for (i = 0; i < m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
	}

	//Close the model file
	fin.close();
	return true;
}

bool ModelClass::InitBuffers(ID3D11Device* device)
{
	int i = 0;
	HRESULT result;
	VertexType* vertices;
	//InstanceType* instances;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData, instanceData;

	////// Set the number of vertices in the vertex array.
	m_vertexCount = 36;

	////// Set the number of indices in the index array.
	m_indexCount = m_vertexCount;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Load the vertex array with data.
	vertices[0].position = XMFLOAT3(-1.0f, 1.0f, -1.0f);  // Bottom left.
	vertices[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[1].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Top middle.
	vertices[1].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[2].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom right.
	vertices[2].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[3].position = XMFLOAT3(-1.0f, -1.0f, -1.0f);  // Bottom left. -1.0f -1.0f -1.0f
	vertices[3].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[4].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Top middle.  1.0f  1.0f -1.0f
	vertices[4].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[5].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom right.  111.0f -1.0f -1.0f
	vertices[5].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[6].position = XMFLOAT3(1.0f, 1.0f, -1.0f);  // Bottom left.  1.0f  1.0f -1.0f
	vertices[6].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[7].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top middle.  1.0f  1.0f  1.0f
	vertices[7].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[8].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom right.  1.0f -1.0f -1.0f
	vertices[8].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	vertices[9].position = XMFLOAT3(1.0f, -1.0f, -1.0f);  // Bottom left.  1.0f -1.0f -1.0f
	vertices[9].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	vertices[10].position = XMFLOAT3(1.0f, 1.0f, 1.0f);  // Top middle.  1.0f  1.0f  1.0f
	vertices[10].color = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

	vertices[11].position = XMFLOAT3(1.0f, -1.0f, 1.0f);  // Bottom right.  1.0f -1.0f  1.0f
	vertices[11].color = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.
	indices[3] = 3;  // Bottom left.
	indices[4] = 4;  // Top middle.
	indices[5] = 5;  // Bottom right.
	indices[6] = 6;  // Bottom left.
	indices[7] = 7;  // Top middle.
	indices[8] = 8;  // Bottom right.
	indices[9] = 9;  // Bottom left.
	indices[10] = 10;  // Top middle.
	indices[11] = 11;  // Bottom right.

	//Load the vertex array and index array with data
	/*for (i = 0; i < m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

		indices[i] = i;
	}*/

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Set the number of instances int the array
	m_instanceCount = 1000;

	//Create instance array
	auto instances = new VertexType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	int x = 0;
	int y = 0;
	int z = 5;
	int iterator = 0;
	int ziter = 0;

	for (int i = 0; i < m_instanceCount; i++)
	{
		instances[i].position = XMFLOAT3(x, y, z);

		x += 2;
		iterator++;
		if (iterator == 10)
		{
			iterator = 0;
			ziter++;
			y -= 2;
			x = 0;
			if (ziter == 10)
			{
				z += 2;
				y = 0;
				ziter = 0;
			}
		}
	}

	//Set up the description of the instance buffer
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(VertexType)* m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	//Give the subrespurce structure a pointer to the instace data
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	//Create the instance buffer
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	delete[] instances;
	instances = 0;

	return true;
}

void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set vertex buffer stride and offset.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(VertexType);
	
	//Set the buffer offsets
	offsets[0] = 0;
	offsets[1] = 0;

	//Set he array of ointers to the vertex and instance buffers
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

void ModelClass::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}
	return;
}


