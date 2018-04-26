module Core;
import std.core;
import sol;
import Engine;
import TriangleObject;
import ResourceManager;
import Shader;
import Buffer;
import Renderer;
#define RAND_MAX 0x7fff
class SmallTriangle : public TriangleObject {
public:
	float c = 0.0f;
	float dir = 0.0001f;
	SmallTriangle::SmallTriangle(Engine* rm) {
		buf = 1;
		engine = rm;
		buffer = ResourceManager::Get<Buffer>("triangleBuffer");
		shader = Shader::LoadShader("shinyShader");
	}
	void SmallTriangle::Draw() {
		shader->Use();
		engine->mRenderer->SetVec2("p", x += speedx, y += speedy);
		engine->mRenderer->SetFloat("time", c += dir);
		if (c >= 1.0f) dir *= -1.0f;
		if (c <= 0.0f) dir = abs(dir);

		buffer->Bind();
		engine->mRenderer->DrawArrays(0, 3);
		buffer->Unbind();
		shader->Finish();
	}
};
Core* createCore(Engine* e) {
	printf("test");
	ResourceManager::rm = e->mResourceManager;
	e->mScriptManager->vm.new_usertype<TriangleObject>("TriangleObject",
		"x", &TriangleObject::x,
		"y", &TriangleObject::y,
		"speedx", &TriangleObject::speedx,
		"speedy", &TriangleObject::speedy,
		"new", sol::factories(ResourceManager::Create<TriangleObject>));
	e->mScriptManager->vm.new_usertype<SmallTriangle>("SmallTriangle",
		"x", &TriangleObject::x,
		"y", &TriangleObject::y,
		"speedx", &TriangleObject::speedx,
		"speedy", &TriangleObject::speedy,
		"new", sol::factories(ResourceManager::Create<SmallTriangle>));
	auto triangleBuffer = ResourceManager::CreateNamed<Buffer>("triangleBuffer");
	auto triangleShader = ResourceManager::CreateNamed<Shader>("triangleShader");
	triangleShader->LoadShader(VERTEX, "triangleShader.vs");
	triangleShader->LoadShader(FRAGMENT, "triangleShader.fs");
	triangleShader->Link();
	auto shinyShader = ResourceManager::CreateNamed<Shader>("shinyShader");
	shinyShader->LoadShader(VERTEX, "triangleShader.vs");
	shinyShader->LoadShader(FRAGMENT, "shinyShader.fs");
	shinyShader->Link();
	e->mScriptManager->vm.script("test = TriangleObject.new()");
	e->mScriptManager->vm.script("test2 = SmallTriangle.new()");
	e->mScriptManager->vm.script("test2.y = 0.55");
	/*e->mScriptManager->vm.script("test.x = -0.5");
	e->mScriptManager->vm.script("test.y = 0.5");
	e->mScriptManager->vm.script("test.speed = 0.00002");
	e->mScriptManager->vm.script("test2 = TriangleObject.new()");
	e->mScriptManager->vm.script("test2.x = -0.5");
	e->mScriptManager->vm.script("test2.y = -0.5");
	e->mScriptManager->vm.script("test2.speed = 0.00001");*/
	return new Core();
}