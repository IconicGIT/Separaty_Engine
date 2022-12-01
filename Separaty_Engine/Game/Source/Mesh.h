#pragma once

#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "MathGeoLib/Geometry/AABB.h"
#include "MathGeoLib/Geometry/OBB.h"

struct Vertex {

    Vertex(){}

    vec Position;
    vec Normal;
    vec2 TexCoords;

    Vertex(vec v)
    {
        Position = v;
    }

    
};



class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh() {}

    void Draw(Shader& shader/*, std::vector<Texture*> textures*/);

    std::string name;
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    unsigned int bboxVAO, bboxVBO, bboxEBO;
    bool drawBbox = true;

    OBB obb;
    AABB bbox;
    vec bboxPoints[8];

    void DrawCube(static float3* corners, vec color);

    void SetupMesh();
};