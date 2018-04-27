# ModularizedGameEngine
A simple proof of concept modular engine with one simple renderer, OpenGL.

Featuring many bugs!

Requirements:
C++17 with modules-ts
Clang 6.0+
buildtool https://github.com/warvstar/buildtool

At the moment I don't see my self adding to this very much, its just a simple proof of concept.

It's missing allot of things a real game engine would use, such as:
- [ ] A proper scenegraph
- [ ] Networking
- [ ] Sound
- [ ] Input(for anything other than windows)


This can easily be ported to msvc, I use my custom tools for convenience and clang for easier Android development.

If someone was going to use this, theyd probably also want to use SDL or something similiar... I personally do all my windowing using native apis.

Oh and did I mention BUGS! I literally put this together over the last 24 hours and have not had allot of time to squash bugs.
