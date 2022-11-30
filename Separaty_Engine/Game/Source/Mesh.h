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

struct Vertex {

    Vertex(){}

    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;

    Vertex(vec3 v)
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
    AABB bbox;
    vec bboxPoints[8];

    void SetupMesh();
};