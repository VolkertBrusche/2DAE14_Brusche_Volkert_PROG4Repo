#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class GameObject;
	class TextComponent final : public BaseComponent, public std::enable_shared_from_this<TextComponent>
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color color);

		explicit TextComponent(const std::string& text, const std::shared_ptr<Font>& font, std::shared_ptr<GameObject> gameObject);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
		SDL_Color m_Color;
	};
}
