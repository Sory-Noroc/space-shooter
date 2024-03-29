#pragma once
#include <bitset>
#include <array>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

class Component;
class Entity;
class Manager;
enum OnEdge { ignore, stop };

using ComponentID = std::size_t;

inline ComponentID getComponentID() {
	static ComponentID lastID = 0;
	return lastID++;
}

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component *, maxComponents>;

class Component
{
public:
	Entity* entity = nullptr;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity {
public:
	Manager& manager;
	bool active = true;
	int health = 1;
	int maxHealth;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

	Entity(Manager& mManager) : manager(mManager) {}

	void update() {
		if (health == 0) destroy();
		for (auto& c : components) c->update();
	}

	void draw() {
		for (auto& c : components) c->draw();
	}

	bool isActive() const { return active; }

 	void destroy() { active = false; }

	void wasHit() { 
		health--; 
	}

	template <typename T> bool hasComponent() const {
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;
		
		c->init();
		return *c;
	}
	
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager {
public:
	std::vector<std::unique_ptr<Entity>> entities;

	virtual void update() {
		for (const auto& e : entities) {
			e->update();
		}
	}

	void draw() const {
		for (auto& e : entities) {
			e->draw();
		}
	}

	void refresh() {
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		addEntity(e);
		return *e;
	}

	void addEntity(Entity* e) {
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
	}

	virtual void addEntityToQueue(Entity *e) = 0;

	virtual ~Manager() = default;
};

template <typename T> bool isIn(std::vector<T> &v, T value) {
	return std::find(v.begin(), v.end(), value) != v.end();
}