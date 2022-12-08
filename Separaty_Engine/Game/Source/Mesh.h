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
#include "Color.h"

struct Vertex {

    Vertex(){}

    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;

    Vertex(vec3 v)
    {
        Position = v;
    }

    Vertex(vec v)
    {
        Position.x = v.x;
        Position.y = v.y;
        Position.z = v.z;
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

    void Draw(Shader& shader, bool wireframeActive);

    bool GetDrawBoundingBox() const
    {
        return drawBbox;
    }

    void SetDrawBoundingBox(bool draw)
    {
        drawBbox = draw;
    }

    bool drawBbox = true;

    std::string name;
    AABB bbox;
    vec bboxPoints[8];
    vec bboxOriginalPoints[8];
    //GOC_MeshRenderer* renderer;

private:
    //  render data
    unsigned int VAO, VBO, EBO;
    
   

    void SetupMesh();
    void DrawCube(static float3* corners, Color color);
};