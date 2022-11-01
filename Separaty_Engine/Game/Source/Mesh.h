#pragma once

#include "Glew/include/GL/glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glmath.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Texture.h"

struct Vertex {
    vec3 Position;
    vec3 Normal;
    vec2 TexCoords;
};



class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

    void Set(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Draw(Shader& shader/*, std::vector<Texture*> textures*/);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void SetupMesh();
};