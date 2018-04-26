export module Renderer;
import std.core;
export {
enum SHADERTYPE {
	VERTEX,
	FRAGMENT,
	GEOMETRY,
	COMPUTE
};
class rI {
public:
	rI(){};
	virtual void Initialize() {};
	virtual void Clear() {};
	virtual void ClearColor(float r, float g, float b, float a) {};
	virtual void BufferData(const ui32 buf, const ui32 size, const void* data) {};
	virtual void GenBuffer(ui32& buf) {};
	virtual void BindBuffer(const ui32 buf){};
	virtual void EnableVertexAttrib(ui32 id, ui32 size){};
	virtual void DrawArrays(ui32 size, int count){};
	virtual i32 LoadShader(SHADERTYPE type, const char* source){};
	virtual void LinkProgram(ui32 program){};
	virtual void AttachShader(const ui32 program, const ui32 shader){};
	virtual ui32 CreateProgram(){};
	virtual void DeleteProgram(const ui32 program){};
	virtual void UseProgram(const ui32 program){};
	virtual void GenerateVertexArray(ui32& VAO){};
	virtual void BindVertexArray(const ui32 VAO){};
	virtual i32 SetVec2(std::string_view var, const float x, const float y){};
	virtual i32 SetFloat(std::string_view var, const float x){};
};
class Renderer : public rI  {
	ui32 shader_program = 0;
public:
	class Engine* engine = nullptr;
	Renderer(){};
	void Initialize();
	void Clear();
	void ClearColor(float r, float g, float b, float a);
	void GenBuffer(ui32& buf);
	void BufferData(const ui32 buf, const ui32 size, const void* data);
	void BindBuffer(const ui32 buf);
	void EnableVertexAttrib(ui32 id, ui32 size);
	void DrawArrays(ui32 size, int count);
	i32 LoadShader(SHADERTYPE type, const char* source);
	bool CheckCompilerErrors(ui32 shader, SHADERTYPE type);
	void LinkProgram(ui32 program);
	void AttachShader(const ui32 program, const ui32 shader);
	ui32 CreateProgram();
	void DeleteProgram(const ui32 program);
	void UseProgram(const ui32 program);
	void GenerateVertexArray(ui32& VAO);
	void BindVertexArray(const ui32 VAO);
	bool ValidateProgram(ui32 program);
	i32 SetVec2(std::string_view var, const float x, float const y);
	i32 SetFloat(std::string_view var, const float x);
};
extern "C" Renderer* createRenderer(class Engine* engine);
}