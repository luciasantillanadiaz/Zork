#pragma once

#include <functional>
#include "entity.h"

class Exit;
class Item;

class Room : public Entity {
public:
	Room(const std::string& name, const std::string& description);
	~Room();

	void Look() const override;
	Entity* Find(const std::string& targetName) override;
	Entity* FindInExit(const std::string& targetName);
	Entity* FindInBarrier(const std::string& targetName);
	void FindAllTakeable(std::list<Item*>& items);
	void Update() override;
	void SetCustomUpdate(std::function<void()> updateLogic);

	const Exit* GetExit(const Direction direction);

private:
	std::function<void()> customUpdate;
};