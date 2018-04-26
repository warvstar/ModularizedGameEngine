module Buffer;
import Engine;
import Renderer;

#define Log(...) printf(__VA_ARGS__)
float g_vertex_buffer_data[] = { 0.0f,  0.5f,  0.0f, 0.5f, -0.5f,  0.0f, -0.5f, -0.5f,  0.0f };
Buffer::Buffer(Engine* e) {
	engine = e;
	engine->mRenderer->GenerateVertexArray(vao);
	//temporary, this should be moved out obviosly to support more type of buffers
	engine->mRenderer->BindVertexArray(vao);
	engine->mRenderer->GenBuffer(buf);
	engine->mRenderer->BindBuffer(buf);
	engine->mRenderer->BufferData(buf, sizeof(g_vertex_buffer_data), g_vertex_buffer_data);
	engine->mRenderer->EnableVertexAttrib(0, 3);
	engine->mRenderer->BindBuffer(0);
	engine->mRenderer->BindVertexArray(0);
}

void Buffer::Bind() {
	engine->GetRenderer()->BindVertexArray(vao);
}
void Buffer::Unbind() {
	engine->GetRenderer()->BindVertexArray(0);
}