#include "model.h"

model::model() {}

void model::render(Shader shader) {
	Mesh.render(shader);
}

void model::cleanup() {
	Mesh.cleanup();
}