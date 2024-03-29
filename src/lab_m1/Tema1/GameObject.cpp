#include "lab_m1/Tema1/GameObject.h"
#include "components/simple_scene.h"

using namespace p1;

GameObject::GameObject(Tema1* scene)
{
    position = glm::vec3(0);
    rotation = 0;
    scale = glm::vec3(1);
    GameObject::scene = scene;
}

GameObject::~GameObject()
{
}

void GameObject::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->SetDrawMode(GL_TRIANGLES);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}

glm::mat4 GameObject::Translate(glm::mat4 model, glm::vec3 pos)
{
    glm::mat4 trans = glm::mat4(
        1, 0, 0, pos.x,
        0, 1, 0, pos.y,
        0, 0, 1, pos.z,
        0, 0, 0, 1
    );
    return model * glm::transpose(trans);
}

glm::mat4 GameObject::Rotate(glm::mat4 model, float rot, glm::vec3 axis)
{
    glm::mat4 rotZ = glm::mat4(
        glm::cos(rot), -glm::sin(rot), 0, 0,
        glm::sin(rot), glm::cos(rot), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
    return model * glm::transpose(rotZ);
}

glm::mat4 GameObject::Scale(glm::mat4 model, glm::vec3 scale)
{
    glm::mat4 scaleMat = glm::mat4(
        scale.x, 0, 0, 0,
        0, scale.y, 0, 0,
        0, 0, scale.z, 0,
        0, 0, 0, 1
    );
    return model * glm::transpose(scaleMat);
}
