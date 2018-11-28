#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Component.h"
#include <vector>
#include "GL/glew.h"

// TODO: Create Vector classes (Vector2<>, Vector3<>, Vector4<>)
// TODO: Create typedefs for Vectors: e.g. Vector2f -> Vector2<float>

class MeshComponent: public Component
{

public:
	MeshComponent();
	virtual ~MeshComponent();

protected:
	std::vector<float> m_vertex;
	std::vector<float> m_normals;
	std::vector<float> m_colors;
	std::vector<float> m_uv;
	GLuint m_mainBuffer; // VAO / IBO
	GLuint m_vertexBuffer;
	GLuint m_normalBuffer;
	GLuint m_colorBuffer;
	GLuint m_uvBuffer;

};

#endif