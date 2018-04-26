module Shader;
import Engine;
import Helper;
import Renderer;
import std.core;
import ResourceManager;
import Helper;
#define Log(...) printf(__VA_ARGS__)
#ifdef __ANDROID__
const char* version = "#version 310 es\n";
#else
const char* version = "#version 430\n";
#endif
Shader::Shader(Engine* e) {
	engine = e;
	//temporary, this should be moved out obviosly to support more type of buffers
	program = e->mRenderer->CreateProgram();
}
void Shader::LoadShader(SHADERTYPE type, std::string_view fn) {
	switch (type){
	case VERTEX: {
		std::string vertexCode;
		v_path = fn;
		vertexCode = Helper::readFile(fn.data());
		if (vertexCode == "") {
			Log("File %s empty or non existant.\n", fn.data());
			//Logger::Log("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
			return;
		}
		Helper::FileLastWrite(v_path, vertex_last);
		std::string vShaderCode = version + vertexCode;
		v = engine->GetRenderer()->LoadShader(SHADERTYPE::VERTEX, vShaderCode.c_str());
		if (v != -1)
			engine->GetRenderer()->AttachShader(program, v);
		else
			Log("Error compiling vertex shader: %s\n", fn.data());
		//Engine::instance()->GetRenderer()->DeleteShader(Program, vertex);
	}
		break;
	case FRAGMENT: {
		std::string fsCode;
		f_path = fn;
		fsCode = Helper::readFile(fn);
		if (fsCode == "") {
			Log("File %s empty or non existant.\n", fn.data());
			return;
		}
		Helper::FileLastWrite(f_path, fragment_last);
		std::string fShaderCode = version + fsCode;
		f = engine->GetRenderer()->LoadShader(SHADERTYPE::FRAGMENT, fShaderCode.c_str());
		if (f != -1)
			engine->GetRenderer()->AttachShader(program, f);
		else
			Log("Error compiling fragment shader: %s\n", fn.data());
	}
		break;
	}
}
Shader* Shader::LoadShader(std::string_view s) {
	auto shader = ResourceManager::Get<Shader>(s);
	if (shader)
		return shader;
}
void Shader::Use() {
	engine->GetRenderer()->UseProgram(program);
}
void Shader::Finish() {
	engine->GetRenderer()->UseProgram(0);
}
void Shader::Update() {
	namespace fs = std::experimental::filesystem;
	if (v_path.size() > 0) {
		try {
			fs::path p = v_path;
			fs::file_status s = fs::status(p);
			if (fs::status_known(s) && fs::exists(p)) {
				std::chrono::system_clock::time_point time = fs::last_write_time(v_path);
				auto diff = std::chrono::duration_cast<std::chrono::microseconds>(time - vertex_last).count();
				if (diff > 0.01) {
					vertex_last = time;
					RecompileVS();
				}
			}
		}
		catch (const std::exception& e) {
		}

	}
	if (f_path.size() > 0) {
		try {
			fs::path p = f_path;
			fs::file_status s = fs::status(p);
			if (fs::status_known(s) && fs::exists(p)) {
				std::chrono::system_clock::time_point time = fs::last_write_time(p);
				auto diff = std::chrono::duration_cast<std::chrono::microseconds>(time - fragment_last).count();
				if (diff > 0.01) {
					fragment_last = time;
					RecompileFS();
				}
			}
		}
		catch (const std::exception& e) {
		}
	}
}
void Shader::RecompileVS() {
	auto renderer = engine->GetRenderer();
	renderer->DeleteProgram(program);
	program = renderer->CreateProgram();
	LoadShader(VERTEX, v_path);
	if (f != -1) renderer->AttachShader(program, f);
	Link();
}
void Shader::RecompileFS() {
	auto renderer = engine->GetRenderer();
	renderer->DeleteProgram(program);
	program = renderer->CreateProgram();
	LoadShader(FRAGMENT, f_path);
	if (v != -1) renderer->AttachShader(program, v);
	Link();
}
void Shader::Link() {
	engine->mRenderer->LinkProgram(program);
}