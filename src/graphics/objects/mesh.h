#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

#include "../rendering/texture.h"
#include "../rendering/shader.h"


struct Vertex {
	glm::vec3 pos;
	glm::vec2 texCoord;

	/*
	v1.vec3.x|v1.vec3.y|v1.vec3.z|v1.vec2.x|v1.vec2.y|
	v2.vec3.x|v2.vec3.y|v2.vec3.z|v2.vec2.x|v2.vec2.y
	*/

	static std::vector<Vertex> genList(float* vertices, int noVertices);
};

class mesh {
private:
	unsigned int VBO, EBO;

	void setup();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VAO;

	std::vector<texture> textures;

	mesh();
	mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<texture> textures);

	void render(Shader shader);

	void cleanup();
};

#endif //MESH_H