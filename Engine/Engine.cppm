export module Engine;
import std.core;
import sol;
export {
class ResourceManager;
enum enumType { v, r, p };
struct arg {
	std::string type;
	bool isConst = false;
	enumType by;
};
struct prop {
	std::string desc;
	std::string type;
	bool isConst = false;
	bool isStatic = false;
	enumType by;
};
using _args = std::unordered_map<std::string, arg>;
struct method {
	std::string desc;
	std::string returnType = "";
	enumType returnBy;
	bool isStatic = false;
	_args args;
};
struct GetterSetterProp {
	method get;
	method set;
};
using _props = std::unordered_map<std::string, prop>;
using _methods = std::unordered_map<std::string, method>;
using _gettersetters = std::unordered_map<std::string, GetterSetterProp>;
struct _class {
	std::string parent = "";
	_methods functions;
	_gettersetters gettersetters;
	_props properties;
	std::vector<std::string> objects;
};
using Classes = std::unordered_map<std::string, _class>;
class ScriptManager {
private:
public:
	Classes classes;
	ScriptManager() { printf("Created ScriptManager.\n"); };
	sol::state vm;
	int i = 0;
};
class eI {
public:
eI(){};
virtual void Setup() {};
virtual void Run() {};
virtual void Destroy() {};
};
class Engine : public eI {
private:
int b = 0;
float bb = 0.0f;
float width = 0.0f;
float height = 0.0f;
public:
	ScriptManager* mScriptManager = nullptr;
	ResourceManager* mResourceManager = nullptr;
	class Renderer* mRenderer = nullptr;
	class App* mWindow = nullptr;
	std::chrono::high_resolution_clock::time_point time_start;
	bool fresh = true;
Engine();
void Run();
void Update();
void Draw();
void Destroy();
void Setup();
float GetWidth() {return width;};
float GetHeight() {return height;};
void SetWidth(float w) {width = w;};
void SetHeight(float h) {height = h;};
void LoadMod(std::string str, std::vector<std::string> classes);
ScriptManager* GetScriptManager() {return mScriptManager;};
ResourceManager* GetResourceManager() {return mResourceManager;};
Renderer* GetRenderer() {return mRenderer;};
};

extern "C" Engine* createEngine(Engine* engine);
//extern "C" ScriptManager* instance();
}
