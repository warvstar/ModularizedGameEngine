export module Buffer;

import std.core;
import Renderer;
export {
import Object;
class Buffer : public Object {
public:
	ui32 vao = 0;
	Buffer(Engine* engine);
	void Bind();
	void Unbind();
};
}