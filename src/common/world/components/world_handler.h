#pragma once

#include "common/world/entity_id.h"
#include "common/util/hash.h"

#include <algorithm>
#include <vector>
#include <set>

class World;

template <typename T, typename D> class WorldHandler {
public:
	WorldHandler();

	T *get(EntityId);
	void add(const T&);
	virtual void remove(EntityId);
	virtual void handleDead(const std::set<EntityId>&);

	virtual void tick(float, World&);
	virtual ~WorldHandler();

	const std::vector<T>& components() const;
	std::vector<T>& components();
	uint32_t hash() const;

protected:
	std::vector<T> mComponents;
};

template <typename T, typename D> WorldHandler<T,D>::WorldHandler():
	mComponents()
{
}

template <typename T, typename D>
void WorldHandler<T, D>::handleDead(const std::set<EntityId>& r)
{
	for (EntityId id : r)
		remove(id);
}

template <typename T, typename D>
void WorldHandler<T, D>::tick(float, World&)
{
}

template <typename T, typename D> T *WorldHandler<T, D>::get(EntityId eid)
{
	for (T& c : mComponents)
		if (c.eid() == eid)
			return &c;
	return nullptr;
}

template <typename T, typename D> void WorldHandler<T, D>::add(const T& c)
{
	mComponents.push_back(c);
}

template <typename T, typename D> WorldHandler<T, D>::~WorldHandler()
{
}

template <typename T, typename D>
std::vector<T>& WorldHandler<T, D>::components()
{
	return mComponents;
}

template <typename T, typename D>
const std::vector<T>& WorldHandler<T, D>::components() const
{
	return mComponents;
}

template <typename T, typename D> uint32_t WorldHandler <T, D>::hash() const
{
	uint32_t h = 5381;
	for (const T& c : mComponents)
		h ^= thash(c);
	return h;
}
