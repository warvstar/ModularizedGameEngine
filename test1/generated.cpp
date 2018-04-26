module generated;
import std.core;
import ResourceManager;
import ScriptManager;
import glm;
template <typename A, typename B>
A multiply(const A& a, const B& b) { return a * b; };
template <typename A, typename B>
A divide(const A& a, const B& b) { return a / b; };
template <typename A, typename B>
A subtract(const A& a, const B& b) { return a - b; };
template <typename A, typename B>
A add(const A& a, const B& b) { return a + b; };
template <typename A>
A clamp(const A& a, const float& b, const float& c) { return glm::clamp(a, b, c); };
template <typename A>
A clamp(const A& a, const int& b, const int& c) { return glm::clamp(a, b, c); };
template <typename A>
A clamp(const A& a, const unsigned int& b, const unsigned int& c) { return glm::clamp(a, b, c); };
#define IMPORTS(v)
#define FUNCTIONS(v)
#define CLASS_START(v)
#define CLASS_END(v)
IMPORTS(s)
namespace ScriptManager_Generated {
#define lua ScriptManager::getInstance()->vm
#define classes ScriptManager::getInstance()->classes
template <typename A, typename B>
A multiply(const A& a, const B& b) { return a * b; };
template <typename A, typename B>
A divide(const A& a, const B& b) { return a / b; };
template <typename A, typename B>
A subtract(const A& a, const B& b) { return a - b; };
template <typename A, typename B>
A add(const A& a, const B& b) { return a + b; };
template <typename A>
A clamp(const A& a, const float& b, const float& c) { return glm::clamp(a, b, c); };
template <typename A>
A clamp(const A& a, const int& b, const int& c) { return glm::clamp(a, b, c); };
template <typename A>
A clamp(const A& a, const unsigned int& b, const unsigned int& c) { return glm::clamp(a, b, c); };
std::string vec2_to_string(const vec2& v) { return std::to_string(v.x) + "," + std::to_string(v.y); }
std::string vec3_to_string(const vec3& v) { return std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z); }
std::string vec4_to_string(const vec4& v) { return std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z) + "," + std::to_string(v.w); }
std::string dvec3_to_string(const dvec3& v) { return std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z); }
std::string dvec4_to_string(const dvec4& v) { return std::to_string(v.x) + "," + std::to_string(v.y) + "," + std::to_string(v.z) + "," + std::to_string(v.w); }
void InitScripts() {
auto RM = ResourceManager::instance();
lua.new_usertype<glm::vec2>("vec2", sol::constructors<glm::vec2(), glm::vec2(float), glm::vec2(float, float)>(),
"x", &glm::vec2::x,
"y", &glm::vec2::y,
"__add", add<glm::vec2, float>,
"__sub", subtract<glm::vec2, float>,
"__mul", multiply<glm::vec2, float>,
"__div", divide<glm::vec2, float>,
"__tostring", vec2_to_string
);
lua.new_usertype<glm::vec3>("vec3", sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
"x", &glm::vec3::x,
"y", &glm::vec3::y,
"z", &glm::vec3::y,
"__add", add<glm::vec3, float>,
"__sub", subtract<glm::vec3, float>,
"__mul", multiply<glm::vec3, float>,
"__div", divide<glm::vec3, float>,
"__tostring", dvec3_to_string
);
lua.new_usertype<glm::vec4>("vec4", sol::constructors<glm::vec4(), glm::vec4(float), glm::vec4(float, float, float, float)>(),
	"x", &glm::vec4::x,
	"y", &glm::vec4::y,
	"z", &glm::vec4::y,
	"w", &glm::vec4::y,
	"__add", add<glm::vec4, float>,
	"__sub", subtract<glm::vec4, float>,
	"__mul", multiply<glm::vec4, float>,
	"__div", divide<glm::vec4, float>,
	"__tostring", dvec4_to_string
	);
lua.new_usertype<glm::dvec3>("dvec3", sol::constructors<glm::dvec3(), glm::dvec3(double), glm::dvec3(double, double, double)>(),
"x", &glm::dvec3::x,
"y", &glm::dvec3::y,
"z", &glm::dvec3::y,
"__add", add<glm::dvec3, double>,
"__sub", subtract<glm::dvec3, double>,
"__mul", multiply<glm::dvec3, double>,
"__div", divide<glm::dvec3, double>,
"__tostring", dvec3_to_string
);
FUNCTIONS(s)
}
}
						