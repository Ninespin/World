#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Component.h"
#include "Vertex.h"
#include "GL/glew.h"

#include <vector>


class MeshComponent: public Component
{
public:
	//
	//  Used by draw system and mesh loading system
	//	Represents available features of a mesh
	//
	enum MESH_FEATURES {
		VERTEX = 0x01, // if not present cant render...
		NORMALS = 0x01 << 2,
		COLOR = 0x01 << 3,
		COLOR_SECONDARY = 0x01 << 4,
		FOG_COORD = 0x01 << 5,
		UV0 = 0x01 << 6,
		UV1 = 0x01 << 7,
		UV2 = 0x01 << 8,
		UV3 = 0x01 << 9,
		UV4 = 0x01 << 10,
		UV5 = 0x01 << 11,
		UV6 = 0x01 << 12,
		UV7 = 0x01 << 13,
		TANGENTS = 0x01 << 14,
		BITANGENTS = 0x01 << 15,

	};

public:
	MeshComponent();
	virtual ~MeshComponent();
	void buildVertexBuffer();
	GLuint getVAO()const;
	unsigned int getNumberVertex()const;
	MESH_FEATURES getFeatures()const;
	

protected:
	MESH_FEATURES m_features; // bit mask representing available mesh features
	std::vector<Vertex> m_vertex;
	GLuint m_mainBuffer; // VAO / IBO
	GLuint m_packedBuffer;

};

#endif