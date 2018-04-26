export module Windows;
#ifdef _WIN32
export {
#include <windows.h>
#include <Xinput.h>
}
#endif