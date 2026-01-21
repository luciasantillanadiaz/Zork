#pragma once

#include <functional>
#include "entity.h"

class Exit;

class Room : public Entity {
public:
	Room(const std::string& name, const std::string& description);
	~Room();

	void Look() const override;
	Entity* Find(const std::string& targetName) const override;
	void Update() override;
	void SetCustomUpdate(std::function<void()> updateLogic);

	Exit* GetExit(Direction direction) const;

private:
	std::function<void()> customUpdate;
};