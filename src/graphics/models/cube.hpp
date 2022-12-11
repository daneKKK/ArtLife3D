#ifndef CUBE_H
#define CUBE_H

#include "../objects/model.h"

class cube : public model {
public:
	glm::vec3 pos;
	glm::vec3 size;

	cube(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f))
		: pos(pos), size(size) {}

	void init() {
		int noVertices = 36;

		float vertices[] = {
			//	position				texture coordinates
				-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
				-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
				-0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

				-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

				 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
				 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
				 0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
				 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

				-0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
				 0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
				 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f,	0.0f, 1.0f
		};

		std::vector<unsigned int> indices(noVertices);
		for (unsigned int i = 0; i < noVertices; i++) {
			indices[i] = i;
		}

		texture tex0("../assets/image1.jpg", "texture0");
		tex0.load();
		texture tex1("../assets/image2.jpg", "texture1");
		tex1.load();

		Mesh = mesh(Vertex::genList(vertices, noVertices), indices, { tex0, tex1 });
	}

	void render(Shader shader) {
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::translate(Model, pos);
		Model = glm::scale(Model, size);
		Model = glm::rotate(Model, (float)glfwGetTime() * glm::radians(-55.0f), glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setMat4("model", Model);

		model::render(shader);
	}
};

#endif //CUBE_H