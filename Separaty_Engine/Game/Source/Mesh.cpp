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
    //bbox = obb.MinimalEnclosingAABB();

    //std::vector<float3> bboxVerticesTemp;

    //for (Vertex v : vertices)
    //{
    //    bboxVerticesTemp.push_back((float3)v.Position);
    //}

    //float3* bboxVertices = &bboxVerticesTemp[0];



    //bbox.Enclose((float3*)bboxVertices, vertices.size());
    //bbox.GetCornerPoints(bboxPoints);
    //int a = 0;


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


}

void Mesh::DrawCube(static float3* corners, vec color)
{
    glLineWidth(2.0f);
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_QUADS);

    glVertex3fv((GLfloat*)&corners[1]);
    glVertex3fv((GLfloat*)&corners[5]);
    glVertex3fv((GLfloat*)&corners[7]);
    glVertex3fv((GLfloat*)&corners[3]);

    glVertex3fv((GLfloat*)&corners[4]);
    glVertex3fv((GLfloat*)&corners[0]);
    glVertex3fv((GLfloat*)&corners[2]);
    glVertex3fv((GLfloat*)&corners[6]);

    glVertex3fv((GLfloat*)&corners[5]);
    glVertex3fv((GLfloat*)&corners[4]);
    glVertex3fv((GLfloat*)&corners[6]);
    glVertex3fv((GLfloat*)&corners[7]);

    glVertex3fv((GLfloat*)&corners[0]);
    glVertex3fv((GLfloat*)&corners[1]);
    glVertex3fv((GLfloat*)&corners[3]);
    glVertex3fv((GLfloat*)&corners[2]);

    glVertex3fv((GLfloat*)&corners[3]);
    glVertex3fv((GLfloat*)&corners[7]);
    glVertex3fv((GLfloat*)&corners[6]);
    glVertex3fv((GLfloat*)&corners[2]);

    glVertex3fv((GLfloat*)&corners[0]);
    glVertex3fv((GLfloat*)&corners[4]);
    glVertex3fv((GLfloat*)&corners[5]);
    glVertex3fv((GLfloat*)&corners[1]);

    glEnd();

}