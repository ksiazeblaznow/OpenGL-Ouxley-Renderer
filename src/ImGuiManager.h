#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameObject.h"
#include <vector>

class ImGuiManager
{
private:
	std::vector<GameObject*> gameObjectsList;	// lista obiektów

public:
	void Draw();


};