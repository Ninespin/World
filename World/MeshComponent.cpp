#include "MeshComponent.h"



MeshComponent::MeshComponent()
	: Component("MeshComponent")
{
	m_features = MESH_FEATURES::VERTEX;

	m_vertex.push_back({ glm::vec3(-1, -1, 0) });
	m_vertex.push_back({ glm::vec3( 0,  1, 0) });
	m_vertex.push_back({ glm::vec3( 1, -1, 0) });

	glGenVertexArrays(1, &m_mainBuffer);
	glBindVertexArray(m_mainBuffer);
	glGenBuffersARB(1, &m_packedBuffer);
	buildVertexBuffer();
}


MeshComponent::~MeshComponent()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glDeleteBuffersARB(1, &m_packedBuffer);
	glDeleteBuffersARB(1, &m_mainBuffer);
}

void MeshComponent::buildVertexBuffer()
{

	glBindVertexArray(m_mainBuffer);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_packedBuffer);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(Vertex)* m_vertex.size(), m_vertex.data(), GL_STATIC_DRAW_ARB);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
	glBindVertexArray(0);
}

GLuint MeshComponent::getVAO() const
{
	return m_mainBuffer;
}

unsigned MeshComponent::getNumberVertex() const
{
	return m_vertex.size();
}

MeshComponent::MESH_FEATURES MeshComponent::getFeatures() const
{
	return m_features;
}
