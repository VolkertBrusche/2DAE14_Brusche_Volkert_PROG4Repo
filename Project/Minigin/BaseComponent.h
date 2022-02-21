#pragma once
class BaseComponent
{
public:
	BaseComponent() = default;
	virtual ~BaseComponent() = default;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) = delete;

	virtual void Update() = 0;
	virtual void Render() const = 0;
};

