module TriangleObject;
import Engine;
import Renderer;
import Shader;
import Buffer;
import ResourceManager;
import std.core;
TriangleObject::TriangleObject() {
}
TriangleObject::TriangleObject(Engine* rm) {
	buf = 1;
	engine = rm;
	buffer = ResourceManager::Get<Buffer>("triangleBuffer");
	shader = Shader::LoadShader("triangleShader");
};
void TriangleObject::Draw() {
	shader->Use();
	engine->mRenderer->SetVec2("p", x += speedx, y += speedy);
	buffer->Bind();
	engine->mRenderer->DrawArrays(0, 3);
	buffer->Unbind();
	shader->Finish();
}
void TriangleObject::Update() {
};