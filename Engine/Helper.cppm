export module Helper;
import std.core;
export {
namespace Helper {
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
std::string readFile(std::string_view filename) {
	std::string buffer = "";
	if (std::ifstream t{ filename.data(), std::ifstream::binary }) {
		t.seekg(0, std::ios::end);
		buffer.resize(t.tellg());
		t.seekg(0);
		t.read(buffer.data(), buffer.size());
	}
	return buffer;
}
}
}