export module Object;
import std.core;

export {
class Engine;
class iO {
public:
	iO(){ };
	iO(Engine* engine){ };
};
class Object : public iO {
public:
	std::string id;
	ui32 buf = 0;
	Engine* engine = nullptr;
	Object();
	Object(Engine* engine);
	virtual void Update() {};
	virtual void Draw() {};
	std::string_view GetID() { return id; };
};
class Runner : public Object {
public:
	int time = 0;
	int speed = 0;
	int distance = 0;
	Runner();
	void Update();
};
class Runner_Slow : public Runner {
public:
	Runner_Slow(Engine* rm);
	void Update();
};
class Runner_Fast : public Runner {
public:
	Runner_Fast(Engine* rm);
	void Update();
};
}