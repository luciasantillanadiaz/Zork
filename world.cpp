#include <iostream>
#include "world.h"
#include "entity.h"
#include "creature.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "barrier.h"
#include "command.h"
#include "enemy.h"

using namespace std;

World::World() {
	// Rooms
	Room* exterior = new Room(
		"The Exterior",
		"It felt like ages since the fresh smell filled your lungs. Now finally free, it's time to go home."
	);
	Room* greatHall = new Room(
		"Great Hall", 
		"The lights flickered to life. They revealed a large hall, smelling of dust and decay. Above, a massive chandelier swayed with an ominous sound."
	);
	Room* library = new Room(
		"Library",
		"Countless rows of books lined the room, though most had been claimed by decay, their words lost to time."
	);
	Room* banquetHall = new Room(
		"Banquet Hall",
		"Two parallel dining tables spanned the entire room, which was filled with decorations still clinging to the stone walls."
	);
	Room* stairs = new Room(
		"Stairs",
		"In front of you, a grandiose staircase led to the second floor. Watching over the ascent was a large portrait of a man, his expression frozen in solemn judgment."
	);
	Room* kitchen = new Room(
		"Kitchen",
		"The horrible smell hovered through the kitchen. Plates and saucepans scattered as if someone was supposed to clean it up."
	);
	Room* chapel = new Room(
		"Chapel",
		"The spacious room brimmed with a soft and warm light."
	);
	Room* mainChambers = new Room(
		"Main Chambers",
		"Main Chambers"
	);
	Room* tower = new Room(
		"Tower",
		"Tower"
	);
	Room* aisle = new Room(
		"Aisle",
		"Aisle"
	);

	entities.push_back(exterior);
	entities.push_back(greatHall);
	entities.push_back(library);
	entities.push_back(banquetHall);
	entities.push_back(stairs);
	entities.push_back(kitchen);
	entities.push_back(chapel);
	entities.push_back(mainChambers);
	entities.push_back(tower);
	entities.push_back(aisle);

	// Exists
	Exit* GHtoEx = new Exit(
		Direction::SOUTH, greatHall, exterior, false
	);
	Exit* GHtoLI = new Exit(
		Direction::EAST, greatHall, library, true
	);
	Exit* GHtoBH = new Exit(
		Direction::WEST, greatHall, banquetHall, true
	);
	Exit* GHtoST = new Exit(
		Direction::NORTH, greatHall, stairs, true
	);
	Exit* BHtoKI = new Exit(
		Direction::NORTH, banquetHall, kitchen, true
	);
	Exit* LItoCH = new Exit(
		Direction::DOWN, library, chapel, true
	);
	Exit* STtoAI = new Exit(
		Direction::NORTH, stairs, aisle, true
	);
	Exit* AItoMC = new Exit(
		Direction::WEST, aisle, mainChambers, true
	);
	Exit* AItoTO = new Exit(
		Direction::EAST, aisle, tower, true
	);

	entities.push_back(GHtoEx);
	entities.push_back(GHtoLI);
	entities.push_back(GHtoBH);
	entities.push_back(GHtoST);
	entities.push_back(BHtoKI);
	entities.push_back(LItoCH);
	entities.push_back(STtoAI);
	entities.push_back(AItoMC);
	entities.push_back(AItoTO);

	// Items
	Item* cross = new Item(
		"Cross",
		"A carved cross with strange symbols. When touched a wave of calmness spreads through your body, it felt warm.",
		chapel
	);
	entities.push_back(cross);

	// Creatures
	player = new Player(
		"Player",
		"A disoriented person who ended up in a strange castle.",
		greatHall
	);

	Enemy* vampire = new Enemy(
		"Vampire",
		"An old man.",
		mainChambers
	);

	entities.push_back(player);
	entities.push_back(vampire);

	commandSystem = new Command();
	commandSystem->RegisterCommands(player);
}

World::~World() {
	for (Entity* entity : entities) {
		delete entity;
	}

	entities.clear();

	delete commandSystem;
}

Command* World::GetCommandSystem() const {
	return commandSystem;
}