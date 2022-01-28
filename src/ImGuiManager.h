#pragma once
#include "../../thirdparty/imgui/imgui.h"
#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
//#include "GameObject.h"
#include <vector>
#include <memory>

class GameObject;

class ImGuiManager
{
public:
	std::vector<std::shared_ptr<GameObject>> gameObjectsList;	// lista obiektów

public:
	ImGuiManager() {  }

	void PushObject(std::shared_ptr<GameObject> obj)
	{
		gameObjectsList.push_back(obj);
	}

	// 0 - no object
	// 1 - success
	// Draws model to the screen
	bool Draw(Shader& shader, int index)
	{
		if (index < gameObjectsList.size()) return false;
		else {
			//gameObjectsList[index]->transform.pos = { 0.f, 4.f, 0.f };
			gameObjectsList[index]->updateSelfAndChildren();
			shader.setMat4("model", gameObjectsList[0]->transform.modelMatrix);
			gameObjectsList[0]->Draw(shader);
		}
	}

	void getSelectedObject();  // #todo

};