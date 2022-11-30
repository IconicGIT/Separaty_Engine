#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    SetupMesh();
}

void Mesh::SetupMesh()
{
    //set mesh
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
        &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);

    ////set bbox
    //bbox.SetNegativeInfinity();
    //vec* bboxVertices = new vec(sizeof(vec) * vertices.size());

    //for (size_t i = 0; i < vertices.size(); i++)
    //{
    //    bboxVertices[i] = float3(vertices[i].Position.x, vertices[i].Position.y, vertices[i].Position.z);
    //}



    //bbox.Enclose((float3*)bboxVertices, vertices.size());
    //bbox.GetCornerPoints(bboxPoints);

    //glGenVertexArrays(1, &bboxVAO);
    //glGenBuffers(1, &bboxVBO);
    //glGenBuffers(1, &bboxEBO);

    //glBindVertexArray(bboxVAO);
    //glBindBuffer(GL_ARRAY_BUFFER, bboxVBO);

    //glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(Vertex), &bboxPoints[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bboxEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, 8 * sizeof(unsigned int), &bboxPoints[0], GL_STATIC_DRAW);

    //// vertex positions
    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //// vertex normals
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
}

void Mesh::Draw(Shader& shader/*, std::vector<Texture*> textures*/)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

     
    if (!textures.empty())
    {
        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            std::string number;
            std::string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            //shader.SetInt(("material." + name + number).c_str(), i);
            glUniform1i(glGetUniformLocation(shader.ID, ("material." + name + number).c_str()), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
    }
    
    
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    /*if (drawBbox)
    {
        glBindVertexArray(bboxVAO);
        glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }*/
}