module Renderer;
import std.core;
import glew;
import Engine;
#include "glewdefines.hpp"
#define Log(...) printf(__VA_ARGS__)
#define CheckGLError() _CheckGLError(__FILE__, __LINE__)
void _CheckGLError(const char* file, int line) {
	GLenum err(glGetError());
	while (err != GL_NO_ERROR) {
		std::string error;
		switch (err) {
		case GL_INVALID_OPERATION:  error = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:       error = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:      error = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:      error = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}
		Log("GLError:GL_ %s - %s : %d\n", error.c_str(), file, line);
		err = glGetError();
	}
	return;
}
int Renderer::SetVec2(std::string_view var, const float x, const float y) {
	GLint loc = glGetUniformLocation(shader_program, var.data());
	if (loc != -1) {
		glUniform2f(loc, x, y);
	}
	return loc;
}
int Renderer::SetFloat(std::string_view var, const float x) {
	GLint loc = glGetUniformLocation(shader_program, var.data());
	if (loc != -1) {
		glUniform1f(loc, x);
	}
	return loc;
}
bool Renderer::ValidateProgram(ui32 program) {
	int success = 0;
	std::string stringVer;
	GLint maxLength = 0;
	glValidateProgram(program);
	CheckGLError();
	glGetProgramiv(program, GL_VALIDATE_STATUS, &success);
	CheckGLError();
	if (!success) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		if (maxLength == 0) {
			Log("ValidateProgram error!\n");
			return false;
		}
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
		Log("ValidateProgram error:%s\n", &errorLog[0]);
		return false;
	}
	return true;
}
void Renderer::BufferData(const ui32 buf, const ui32 size, const void* data) {
		glBindBuffer(GL_ARRAY_BUFFER, buf);
		glBufferData(GL_ARRAY_BUFFER, size, (GLvoid*)data, GL_STATIC_DRAW);
		CheckGLError();
}
void Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Renderer::ClearColor(float r, float g, float b, float a) {
	glClearColor(r,g,b,a);
}
void Renderer::GenBuffer(ui32& buf) {
	glGenBuffers(1, &buf);
	CheckGLError();
}

void Renderer::Initialize() {
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { printf("glew failed to init, CRITICAL ERROR!\n"); return false; }
	const GLubyte *GLVersionString = glGetString(GL_VERSION);
	const GLubyte* renderer = glGetString(GL_RENDERER);
	glViewport(0, 0, engine->GetWidth(), engine->GetHeight());
	CheckGLError();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	CheckGLError();
}
Renderer* createRenderer(Engine* engine) {
	auto r = new Renderer();
	r->engine = engine;
	engine->mRenderer = r;
	return r;
}
void Renderer::BindBuffer(const ui32 buf) {
	glBindBuffer(GL_ARRAY_BUFFER, buf);
	CheckGLError();
}
void Renderer::EnableVertexAttrib(ui32 id, ui32 size) {
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, size, GL_FLOAT, GL_FALSE, 0, (void*)0);
	CheckGLError();
}
void Renderer::DrawArrays(ui32 size, int count) {
	glDrawArrays(GL_TRIANGLES, size, count);
	CheckGLError();
}
void Renderer::GenerateVertexArray(ui32& VAO) {
	glGenVertexArrays(1, &VAO);
}
void Renderer::BindVertexArray(const ui32 VAO) {
	glBindVertexArray(VAO);
	CheckGLError();
}
bool Renderer::CheckCompilerErrors(ui32 shader, SHADERTYPE type) {
	GLint success = 0;
	std::string stringVer;
	GLint maxLength = 0;
	switch (type) {
	case SHADERTYPE::VERTEX:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			if (maxLength == 0) {
				Log("vertex error!");
				glDeleteShader(shader);
				return false;
			}
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			glDeleteShader(shader);
		}
		break;
	case SHADERTYPE::FRAGMENT:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			if (maxLength == 0) {
				Log("fragment error!");
				glDeleteShader(shader);
				return false;
			}
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			Log("Error with fragment shader: %s", &errorLog[0]);
			glDeleteShader(shader);
		}
		break;
	case SHADERTYPE::COMPUTE:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success == 0) {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> errorLog(maxLength);
			if (maxLength == 0) {
				Log("compute error!");
				glDeleteShader(shader);
				return false;
			}
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			Log("Error with compute shader: %s", &errorLog[0]);
			glDeleteShader(shader);
		}
		break;
	default:
		break;
	}
	return success > 0;
}
void Renderer::AttachShader(const ui32 program, const ui32 shader) {
	glAttachShader(program, shader);
	CheckGLError();
}
i32 Renderer::LoadShader(SHADERTYPE type, const char* source) {
	GLuint s = -1;
	switch (type) {
	case SHADERTYPE::VERTEX:
		s = glCreateShader(GL_VERTEX_SHADER);
		break;
	case SHADERTYPE::FRAGMENT:
		s = glCreateShader(GL_FRAGMENT_SHADER);
		break;
		//#ifndef __ANDROID__
	case SHADERTYPE::COMPUTE:
		s = glCreateShader(GL_COMPUTE_SHADER);
		break;
		//#endif
	default:
		break;
	}
	glShaderSource(s, 1, &source, nullptr);
	glCompileShader(s);
	CheckGLError();
	if (!CheckCompilerErrors(s, type))
		return -1;
	return s;
}
ui32 Renderer::CreateProgram() {
	auto p = glCreateProgram();
	CheckGLError();
	return p;
}
void Renderer::LinkProgram(ui32 program) {
	CheckGLError();
	glLinkProgram(program);
	CheckGLError();
	GLint success = 0;
	std::string stringVer;
	GLint maxLength = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	CheckGLError();
	if (success == 0) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> errorLog(maxLength);
		if (maxLength == 0) {
			Log("LinkProgram error!\n");
			glDeleteProgram(program);
			CheckGLError();
			return;
		}
		glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);
		Log("Link error:%s\n", &errorLog[0]);
		glDeleteProgram(program);
	}
	CheckGLError();
	ValidateProgram(program);
}
void Renderer::UseProgram(const ui32 program) {
	glUseProgram(program);
	shader_program = program;
}
void Renderer::DeleteProgram(const ui32 program) {
	glDeleteProgram(program);
	shader_program = 0;
}