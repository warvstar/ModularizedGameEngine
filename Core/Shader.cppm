export module Shader;
import std.core;
import Renderer;
export {
import Object;
class Shader : public Object {
public:
	std::string v_path = "";
	std::string f_path = "";
	ui32 program = 0;
	ui32 v = 0;
	ui32 f = 0;
	ui32 c = 0;
	std::chrono::system_clock::time_point vertex_last;
	std::chrono::system_clock::time_point fragment_last;
	Shader(Engine* engine);
	void LoadShader(SHADERTYPE type, std::string_view fn);
	void Update();
	void Link();
	void Use();
	void Finish();
	void RecompileVS();
	void RecompileFS();
	static Shader* LoadShader(std::string_view s);
};
}