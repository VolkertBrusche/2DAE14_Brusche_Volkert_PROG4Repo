#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : 
		public BaseComponent
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z = 0.0f);
	private:
		glm::vec3 m_Position;
	};
}

