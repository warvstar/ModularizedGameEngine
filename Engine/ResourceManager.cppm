export module ResourceManager;
import std.core;
import Object;
export {
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}
std::string demangle(std::string_view s1) {
	std::string s = s1.data();
	replaceAll(s, "class ", "");
	s.erase(std::remove_if(s.begin(), s.end(), [](char x) {return std::isspace(x); }), s.end());
	return s;
}
class ResourceManager {
private:
public:
	std::vector<std::unique_ptr<Object>> objects; //id can be stored in each object
	static ResourceManager* rm;
	Engine* engine;
	std::unordered_map<std::string, std::function<Object*()>> class_map;
	template<class T>
	static T * Create() {
		std::string className = typeid(T).name();
		auto className2 = demangle(className);
		if (rm){
		rm->objects.emplace_back(std::make_unique<T>(rm->engine)).get()->engine = rm->engine;
		return (T*)rm->objects.back().get();
		}
		else return nullptr;
	}
	template<class T>
	static T * CreateNamed(std::string_view name) {
		std::string className = typeid(T).name();
		auto className2 = demangle(className);
		if (rm){
		rm->objects.emplace_back(std::make_unique<T>(rm->engine)).get()->engine = rm->engine;
		rm->objects.back()->id = name;
		return (T*)rm->objects.back().get();
		}
		else return nullptr;
	}
	template<class T>
	static T * Get(std::string_view name) {
			for (auto& o : rm->objects) {
				if (o->GetID() == name) {
					return dynamic_cast<T*>(o.get());
				}
			}
			return nullptr;
	}
	//static Object* CreateScriptObject(std::string_view className);
};
ResourceManager* ResourceManager::rm;
}