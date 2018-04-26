export module TriangleObject;
import std.core;
export {
import Object;
class TriangleObject : public Object {
public:
	class Shader* shader = nullptr;
	class Buffer* buffer = nullptr;
	float x = 0.0f;
	float y = 0.0f;
	float speedx = 0.0f;
	float speedy = 0.0f;
	TriangleObject();
	TriangleObject(Engine* rm);
	void Draw();
	void Update();
};
}