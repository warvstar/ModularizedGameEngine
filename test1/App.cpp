module App;
import std.core;
import sol;
import Core;
import Engine;
import Renderer;
#include "windowdefines.h"
import glew;
#include "../Renderer/glewdefines.h"
#include "wglewdefines.h"
typedef void* create_t(Engine* engine);
std::unordered_map<std::string, HMODULE> map;
std::unordered_map<std::string, create_t*> map2;
std::vector<dllType> dlls;
bool FileLastWrite(std::string_view f, std::chrono::system_clock::time_point& tp) {
	namespace fs = std::experimental::filesystem;
	fs::path p = f.data();
	fs::file_status s = fs::status(p);
	if (fs::status_known(s) && fs::exists(p)) {
		tp = fs::last_write_time(p);
		return true;
	}
	return false;
}
void LoadMod(std::string str, std::vector<std::string> classes) {
	std::string dllName = std::string(str.data() + std::string(".so")).data();
	std::string dllName2 = std::string(str.data() + std::string(".dll")).data();
	if (map[str] != nullptr) {
		printf("Unloading module %s.\n", str.data());
		if (FreeLibrary(map[str])) {   //2: unload the DLL
			printf("Successfully unloaded module %s.\n", str.data());
			remove(dllName2.data());
		}
		else
			printf("Error unloading module %s.\n", str.data());
	}
	if (CopyFileA(dllName.data(), dllName2.data(), false)) {
		printf("Succesfully copied dll.\n");
	}
	map[str] = LoadLibraryA(dllName2.data());
	if (map[str]) {
		printf("Module %s loaded correctly.\n", str.data());
		dllType t;
		t.name = str;
		t.fullname = dllName;
		t.last_write = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point tp;
		if (FileLastWrite(t.fullname, tp))
			t.last_write = tp;
		for (auto& c : classes) {
			std::string funcName = std::string("create" + c);
			map2[c] = (create_t*)GetProcAddress(map[str], funcName.data());
			t.classes.push_back(c);
		}
		int rem = -1;
		for (int i = 0; i < dlls.size(); ++i) {
			if (dlls[i].name == str)
				rem = i;
		}
		if (rem > -1)
			dlls.erase(dlls.begin() + rem);
		dlls.push_back(t);
	}
}
LRESULT CALLBACK App::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_SIZE:
		break;
	case WM_CLOSE:
		PostMessage(hWnd, WM_USER + 2, wParam, lParam);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
int App::HandleEvents() {

	MSG message;
	if (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
		switch (message.message) {
		case WM_USER + 1:
			return 1;
			break;
		case WM_USER + 2:
			return 2;
			break;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}
bool App::NewWindow(Engine* engine) {
	Instance = GetModuleHandle(nullptr);
	std::wstring title = L"FutureEngine";
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = App::WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = Instance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"Test";
	wcex.hIconSm = 0;

	if (!RegisterClassEx(&wcex)) {
		return false;
	}
	Handle = CreateWindow(L"Test", title.c_str(), WS_POPUP, 0, 0, engine->GetWidth(), engine->GetHeight(), nullptr, nullptr, Instance, nullptr);
	if (!Handle) {
		return false;
	}

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	mDeviceContext = GetDC(Handle);
	int nPixelFormat = ChoosePixelFormat(mDeviceContext, &pfd);

	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(mDeviceContext, nPixelFormat, &pfd);

	if (!bResult) return false;
	HGLRC tempContext = wglCreateContext(mDeviceContext);
	wglMakeCurrent(mDeviceContext, tempContext);

	GLenum err = glewInit();
	if (GLEW_OK != err) {
	}

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 0,
		WGL_CONTEXT_FLAGS_ARB, 0,
		0
	};
	wglSwapIntervalEXT(0); //VSYNC
	if (wglewIsSupported("WGL_ARB_create_context") == 1) {
		m_hrc = wglCreateContextAttribsARB(mDeviceContext, 0, attribs);
		wglMakeCurrent(0, 0);
		wglDeleteContext(tempContext);
		wglMakeCurrent(mDeviceContext, m_hrc);
	}
	else {	m_hrc = tempContext; }
	const GLubyte *GLVersionString = glGetString(GL_VERSION);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
	if (!m_hrc) return false;
	ShowWindow(Handle, SW_SHOWNORMAL);
	UpdateWindow(Handle);
	return true;
}
void ReadCin(std::atomic<bool>& run, ScriptManager* sm) {
	std::string buffer;
	while (run.load()) {
		getline(std::cin, buffer);
		if (buffer == "Quit") run.store(false);
		try {
			sm->vm.script(buffer);
		}
		catch (sol::error& e) {
			std::cout << "caught sol::error: " << e.what() << std::endl;
		}
		catch (...) {
			std::cout << "error with sol2 " << std::endl;
		}
	}
}
#define PERSIST(O) static_cast<O*>(sm->vm.script("return " + demangle(typeid(O).name()) + ".new()"))
#define REPLACE(O) static_cast<O*>(sm->vm.script("return " + demangle(typeid(O).name()) + ".new()"))
void App::Start() {
	Engine* engine = nullptr;
	Renderer* r;
	ScriptManager* sm = nullptr;
	ResourceManager* rm = nullptr;
	LoadMod("Engine", { "Engine" });
	engine = (Engine*)map2["Engine"](nullptr);
	engine->SetWidth(1720);
	engine->SetHeight(1440);
	engine->mWindow = this;
	NewWindow(engine);
	LoadMod("Renderer", { "Renderer" });
	r = (Renderer*)map2["Renderer"](engine);
	engine->mRenderer = r;
	engine->Setup();
	sm = engine->GetScriptManager();
	rm = engine->GetResourceManager();
	auto res = sm;
	uint64_t time = 0;
	r = engine->mRenderer;
	sm = engine->mScriptManager;
	rm = engine->mResourceManager;
	LoadMod("Core", { "Core" });
	auto core = (Core*)map2["Core"](engine);

	//auto obj = PERSIST(TriangleObject); //An object that will persist even upon restart of module
	//auto obj2 = REPLACE(Runner_Fast); //An object that will be replaced upon restart of module
	Sleep(1000);
	std::atomic<bool> run(true);
	std::thread cinThread(ReadCin, std::ref(run), std::ref(sm));
	while (run.load()) {
		if (time > 10000) {
			time = 0;
			for (auto& dll : dlls) {
				std::chrono::system_clock::time_point tp;
				if (FileLastWrite(dll.fullname, tp)) {
					if (dll.last_write < tp) {
						printf("Module(%s) recompiled.\n", dll.name.c_str());
						using namespace std::chrono_literals;
						dll.last_write = tp + 100ms;
						if (dll.name == "Engine") {
							engine->Destroy();
							LoadMod(dll.name, dll.classes);
							engine = (Engine*)map2["Engine"](nullptr);
							engine->mRenderer = r;
							engine->Setup();
							r->engine = engine;
							rm = engine->mResourceManager;
							sm = engine->mScriptManager;
							engine->mWindow = this;
							sm->vm["engine"] = engine;
							engine->SetWidth(1720);
							engine->SetHeight(1440);
							delete core;
							(Core*)map2["Core"](engine);
						}
						else if (dll.name == "Core") {
							//goota find a way to clear objcets that wear created in core? for now just clear restart engine
							engine->Destroy();
							engine = (Engine*)map2["Engine"](nullptr);
							engine->mRenderer = r;
							engine->Setup();
							r->engine = engine;
							rm = engine->mResourceManager;
							sm = engine->mScriptManager;
							engine->mWindow = this;
							sm->vm["engine"] = engine;
							engine->SetWidth(1720);
							engine->SetHeight(1440);
							LoadMod(dll.name, dll.classes);
							delete core;
							(Core*)map2["Core"](engine);
						}
					}
				}
			}
		}
		if (engine == nullptr) {
			printf("error");
			continue;
		}
		time++;
		HandleEvents();
		engine->Run();
	}
	run.store(false);
	cinThread.join();
}