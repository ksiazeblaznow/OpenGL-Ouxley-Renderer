#pragma once
#include <ImGuizmo.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/ext.hpp"

enum class GizmoMode
{
	none,
	translate,
	rotate,
	scale
};

std::shared_ptr<GameObject> GetSelectedGameObject();

class Gizmoes
{
private:
	int screenW, screenH;

public:
	// Calls Init()
	Gizmoes(int screenW, int screenH) {
		Init();
	}

	// called once (in constructor)
	void Init() {


	}

	// note: run under ImGui::NewFrame() or just before ImGui::End()
	void Run(Camera& camera)
	{
		ImGuizmo::BeginFrame();

		std::shared_ptr<GameObject> selectedObject = GetSelectedGameObject();
		if (selectedObject)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();
			float windowW = (float)ImGui::GetWindowWidth();
			float windowH = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x,
				ImGui::GetWindowPos().y, screenW, screenH);

			// camera
			glm::mat4 cameraView = glm::inverse(camera.GetViewMatrix());
			glm::mat4 cameraProjection = glm::perspective(glm::radians(camera.Zoom), (float)screenW / (float)screenH, 0.1f, 100.0f);

			// object transform
			glm::mat4 selectedObjTransform = selectedObject->transform.modelMatrix;
			
		
				
			ImGuizmo::Manipulate(glm::value_ptr(cameraView),
				glm::value_ptr(cameraProjection),
				ImGuizmo::OPERATION::TRANSLATE,
				ImGuizmo::LOCAL,
				glm::value_ptr(selectedObjTransform));
		
		}
		
		
	}
	
};