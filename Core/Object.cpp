module Object;
import Engine;
import ResourceManager;
import std.core;

Object::Object() {
}
Object::Object(Engine* engine) {
	engine->mResourceManager->objects.emplace_back(this);
}