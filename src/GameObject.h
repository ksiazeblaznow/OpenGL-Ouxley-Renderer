#pragma once
#include <glm/glm.hpp>
#include "Model.h"
#include <list>
#include <memory>
#include <string>

//class Model;

struct Transform
{
	// Local space
	glm::vec3 pos = { 0.f, 0.f, 0.f };		// pozycja
	glm::vec3 rot = { 0.f, 0.f, 0.f };		// rotacja (euler)
	glm::vec3 scale = { 1.f, 1.f, 1.f };	// skala

	// Global space
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	glm::mat4 getLocalModelMatrix()
	{
		const glm::mat4 transformX
			= glm::rotate(glm::mat4(1.0f),
				glm::radians(rot.x),
				glm::vec3(1.f, 0.f, 0.f));
		const glm::mat4 transformY
			= glm::rotate(glm::mat4(1.0f),
				glm::radians(rot.y),
				glm::vec3(0.f, 1.f, 0.f));
		const glm::mat4 transformZ
			= glm::rotate(glm::mat4(1.0f),
				glm::radians(rot.z),
				glm::vec3(0.f, 0.f, 1.f));

		// Y * X * Z
		const glm::mat4 rotationMatrix
			= transformY * transformX * transformZ;

		// translation * rotation * scale (TRS matrix)
		return glm::translate(glm::mat4(1.f), pos) *
			rotationMatrix * glm::scale(glm::mat4(1.f), scale);

	}
};

class GameObject : public Model
{
private:
	//const char* name;			// unikalna nazwa

public:
	GameObject() = default;

	Transform transform;
	GameObject* parent = nullptr;
	std::list<std::unique_ptr<GameObject>> children;

	GameObject(std::string const& path, bool gamma = false)
		: Model(path, gamma) {  }
	//~GameObject();

	template <typename... TArgs>
	void CreateChild(const TArgs&... args)
	{
		children.emplace_back(std::make_unique<GameObject>(args...));
		children.back()->parent = this;
	}

	// own approach to AddChild functions
	// as the higher one doesn't support
	// adding existing child
	void AddChild(GameObject* child)
	{
		children.emplace_back(child);
		children.back()->parent = this;
	}

	void updateSelfAndChildren()
	{
		if (parent)
			transform.modelMatrix = parent->transform.modelMatrix * transform.getLocalModelMatrix();
		else
			transform.modelMatrix = transform.getLocalModelMatrix();

		for (auto&& child : children)
			child->updateSelfAndChildren();
	}

};
