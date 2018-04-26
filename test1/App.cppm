export module App;
import std.core;
#include "windowdefines.h"
export {
struct dllType {
	std::string name = "";
	std::string fullname = "";
	std::vector<std::string> classes;
	std::chrono::system_clock::time_point last_write;
};
class App {
public:
	HWND Handle;
	HDC mDeviceContext;
	HMODULE Instance;
	HGLRC	 m_hrc;
	int HandleEvents();
	void Start();
	static LRESULT __stdcall WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool NewWindow(class Engine* engine);
	void SwapBuffers() { ::SwapBuffers(mDeviceContext); };
};
}