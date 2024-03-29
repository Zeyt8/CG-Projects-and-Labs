#include "lab_m1/Tema1/Grass.h"

using namespace p1;

Grass::Grass(Tema1* scene) : GameObject(scene)
{

}

void Grass::Awake()
{
    int xMin = 0;
    int yMin = 0;
    int xMax = scene->GetSceneCamera()->GetProjectionInfo().width;
    int yMax = scene->GetSceneCamera()->GetProjectionInfo().height / 5;
    {
        std::vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(xMin, yMin, 0), glm::vec3(0.44f, 0.93f, 0.3f), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(xMax, yMin, 0), glm::vec3(0.44f, 0.93f, 0.3f), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(xMax, yMax, 0), glm::vec3(0.44f, 0.93f, 0.3f), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(xMin, yMax, 0), glm::vec3(0.44f, 0.93f, 0.3f), glm::vec3(0.2, 0.8, 0.6)),
        };

        std::vector<unsigned int> indices
        {
            0, 1, 2,
            0, 2, 3
        };

        meshes["grass"] = new Mesh("grass");
        meshes["grass"]->InitFromData(vertices, indices);

        CreateMesh("grass", vertices, indices);
    }

    position = glm::vec3(0, 0, 0.1f);
}

void Grass::Start()
{

}

void Grass::Update(float deltaTime)
{
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = Translate(modelMatrix, position);
    scene->RenderMesh(meshes["grass"], scene->GetShader("VertexColor"), modelMatrix);
}