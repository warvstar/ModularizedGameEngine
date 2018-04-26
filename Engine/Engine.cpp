module Engine;
import std.core;
import sol;
import Renderer;
import App;
import Object;
import ResourceManager;
import TriangleObject;
typedef std::chrono::high_resolution_clock Time;
Engine* createEngine(Engine* engine) {
	auto e = new Engine();
	if (engine != nullptr) {
		delete engine->mResourceManager;
		delete engine->mScriptManager;
		delete engine;
		engine = nullptr;
		e->time_start = Time::now();
	}
	return e;
}
Engine::Engine() {
	printf("Created Engine.\n");
};
void Engine::Destroy() {
	for (auto& o : mResourceManager->objects) {
		o.reset();
	}
	mResourceManager->objects.clear();
	delete mScriptManager;
	delete mResourceManager;
	delete this;
}
using namespace std::chrono_literals; 
constexpr std::chrono::milliseconds timestep(16ms);
std::chrono::nanoseconds lag(0ns);
void Engine::Run() {
	auto delta_time = Time::now() - time_start;
	time_start = Time::now();
	std::chrono::nanoseconds frameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);
	if (frameTime > 25ms)
		frameTime = 25ms;
	lag += frameTime;
	while (lag >= timestep) {
		Update();
		lag -= timestep;
	}
	Draw();
}
void Engine::Update() {
	auto rm = GetResourceManager();
	for (auto& o : rm->objects)
		o->Update();
}
void Engine::Draw() {
	mRenderer->ClearColor(bb += 0.000001, bb += 0.00001,1,1);
	mRenderer->Clear();
	for (auto& o : mResourceManager->objects)
		if (o->buf > 0)
			o->Draw();
	mWindow->SwapBuffers();
}
void Engine::Setup() {
	mResourceManager = new ResourceManager();
	auto rm = GetResourceManager();
	rm->engine = this;
	mRenderer->Initialize();
	ResourceManager::rm = rm;
	mScriptManager = new ScriptManager();
	mScriptManager->classes["Object"];
	mScriptManager->vm.new_usertype<Engine>("Engine",
		"Run", &Engine::Run);
	mScriptManager->vm.new_usertype<ResourceManager>("ResourceManager");
	/*mScriptManager->vm.new_usertype<Object>("Object",
		"new", sol::factories(ResourceManager::Create<Object>));*/
	mScriptManager->vm["engine"] = this;
	printf("Engine: Loading modules.\n");
	time_start = Time::now();
}