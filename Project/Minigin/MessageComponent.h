#pragma once
#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class MessageComponent final:
		public BaseComponent
	{
	public:
		MessageComponent(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~MessageComponent();

		MessageComponent(const MessageComponent& other) = delete;
		MessageComponent(MessageComponent&& other) = delete;
		MessageComponent& operator=(const MessageComponent& other) = delete;
		MessageComponent& operator=(MessageComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};
}

