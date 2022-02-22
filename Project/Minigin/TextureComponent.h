#pragma once
#include "BaseComponent.h"

namespace dae
{
    class Texture2D;
    class TextureComponent :
        public BaseComponent
    {
    public:
        TextureComponent() = default;
        virtual ~TextureComponent();

        TextureComponent(const TextureComponent& other) = delete;
        TextureComponent(TextureComponent&& other) = delete;
        TextureComponent& operator=(const TextureComponent& other) = delete;
        TextureComponent& operator=(TextureComponent&& other) = delete;

        virtual void Update() override {};
        virtual void Render() const override;

        void SetTexture(const std::string& filename);

    private:
        std::shared_ptr<Texture2D> m_pTexture{};
    };
}

