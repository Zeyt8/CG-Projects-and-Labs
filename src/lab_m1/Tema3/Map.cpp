#include "Map.h"
#include "Player.h"
#include <iostream>

p3::Map::Map(Tema3* scene) : GameObject(scene)
{
    Mesh* mesh = new Mesh("snow");
    mesh->LoadMesh(scene->SourcePrimitiveDir, "plane50.obj");
    Meshes[mesh->GetMeshID()] = mesh;

    SetScale(glm::vec3(1.2f, 1, 1.2f));
    SetRotation(glm::vec3(RADIANS(30), 0, 0));
}

void p3::Map::Update(float deltaTime)
{
	SetPosition(Scene->PlayerObject->Position);
}

void p3::Map::Render()
{
    Scene->RenderMesh(Meshes["snow"], Scene->GetShader("snow"), ModelMatrix, Scene->Textures["snow"], true);
}
