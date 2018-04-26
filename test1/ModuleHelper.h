#pragma once
template<class T>
HMODULE LoadModule(std::string str) {
	HMODULE hDLL;
	bool fFreeResult, fRunTimeLinkSuccess = false;
	if (CopyFileA(str.data(), std::string(str.data() + std::string("1")).data(), false)) {
	}
	hDLL = LoadLibraryA(std::string(str.data() + std::string("1")).data());
	if (!hDLL)
		hDLL = LoadLibraryA(std::string(str.data() + std::string("1")).data());
	if (hDLL) {
		typedef T* create_t();
		create_t* creat = (create_t*)GetProcAddress(hDLL, "create");
	}
	return hDLL;
}