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
#include "globals.h"

using namespace std;

World::World() {
	// --- ROOMS ---
	Room* exterior = new Room(
		"The Exterior",
		"It felt like an eternity since fresh air had filled your lungs. Stepping out of the darkness and finally free, you knew it was time to go home."
	);
	endRoom = exterior;
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
		"The spacious room brimmed with a soft and warm light. There are 3 pedestals, looks like you should place something in there."
	);
	Room* mainChambers = new Room(
		"Main Chambers",
		"A suffocating darkness filled the room. In the center, a single coffin lay still."
	);
	Room* tower = new Room(
		"Tower",
		"A thick blanket of dust coated the room. It was clear that no living soul had entered in decades."
	);
	Room* aisle = new Room(
		"Aisle",
		"The passage served as a silent gallery, crowded with striking portraits that seemed to watch every step."
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

	// --- EXITS ---
	Exit* GHtoEX = new Exit(
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

	entities.push_back(GHtoEX);
	entities.push_back(GHtoLI);
	entities.push_back(GHtoBH);
	entities.push_back(GHtoST);
	entities.push_back(BHtoKI);
	entities.push_back(LItoCH);
	entities.push_back(STtoAI);
	entities.push_back(AItoMC);
	entities.push_back(AItoTO);

	// --- BARRIERS WITHOUT KEYS ---
	Barrier* drawer = new Barrier(
		"drawer",
		"It's a drawer.",
		nullptr,
		false,
		mainChambers
	);
	Barrier* box = new Barrier(
		"box",
		"Maybe it's related to the plates.",
		drawer, // It can't be open by a simple key
		true,
		chapel
	);

	// --- ITEMS ---
	Item* cross = new Item(
		"cross",
		"A cross carved with strange symbols.",
		tower
	);
	Item* sword = new Item(
		"sword",
		"A very old sword, seems useful.",
		banquetHall
	);
	sword->SetItemType(ItemType::WEAPON);
	sword->SetDealingDamage(5);
	Item* garlic = new Item(
		"garlic",
		"It's fresh.",
		kitchen
	);
	Item* stake = new Item(
		"stake",
		"It's sharp.",
		banquetHall
	);
	Item* key = new Item(
		"key",
		"It has a peculiar design.",
		drawer
	);
	Item* book = new Item(
		"book",
		"To kill the inmortal you must find its 3 weaknesses.",
		library
	);
	Item* relic = new Item(
		"relic",
		"It emits a very powerfull energy. A warm sensation comes from it.",
		tower
	);
	Item* gateKey = new Item(
		"gate-key",
		"Looks like the key for the entrance.",
		box
	);
	Barrier* plate1 = new Barrier(
		"cross-pedestal",
		"A marble pedestal with a cross carved into the surface.",
		nullptr,
		false,
		chapel
	);
	plate1->Open();
	Barrier* plate2 = new Barrier(
		"circle-pedestal",
		"A marble pedestal with a circle carved into the surface.",
		nullptr,
		false,
		chapel
	);
	plate2->Open();
	Barrier* plate3 = new Barrier(
		"triangle-pedestal",
		"A marble pedestal with a triangle carved into the surface.",
		nullptr,
		false,
		chapel
	);
	plate3->Open();

	entities.push_back(cross);
	entities.push_back(sword);
	entities.push_back(garlic);
	entities.push_back(stake);
	entities.push_back(key);
	entities.push_back(book);
	entities.push_back(relic);
	entities.push_back(gateKey);
	entities.push_back(plate1);
	entities.push_back(plate2);
	entities.push_back(plate3);

	chapel->SetCustomUpdate([chapel, plate1, plate2, plate3]() {
		Entity* e1 = plate1->Find("cross");
		Entity* e2 = plate2->Find("garlic");
		Entity* e3 = plate3->Find("stake");

		static bool puzzleSolved = false;

		if (e1 && e2 && e3 && !puzzleSolved) {
			Entity* box = chapel->Find("box");
			if (box != nullptr) {
				static_cast<Barrier*>(box)->Unlock();
				PushNotification("Box is unlocked.");
				puzzleSolved = true;
			}
		}
	});

	// --- BARRIERS WITH KEYS ---
	Barrier* towerDoor = new Barrier(
		"door",
		"A very peculiar door.",
		key,
		true,
		AItoTO
	);
	Barrier* trapdoor = new Barrier(
		"trapdoor",
		"A powerfull seal was cast on it a long time ago. A warm sensation comes from it.",
		relic,
		true,
		LItoCH
	);
	Barrier* gate = new Barrier(
		"gate",
		"A big gate, looks like the entrance.",
		gateKey,
		true,
		GHtoEX
	);

	entities.push_back(towerDoor);
	entities.push_back(trapdoor);
	entities.push_back(gate);

	// --- CREATURES ---
	player = new Player(
		"Player",
		"You feel disoriented, wondering how you ended up in this strange castle.",
		greatHall
	);

	Enemy* vampire = new Enemy(
		"Vampire",
		"The vampire was ancient. His visage was gaunt and ruined, unrecognizable compared to the noble face in the portrait.",
		mainChambers
	);
	vampire->SetHealth(1000000000);

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

void World::Update() {
	auto it = entities.begin();
	while (it != entities.end()) {
		Entity* entity = *it;

		if (entity->GetType() == EntityType::ENEMY || entity->GetType() == EntityType::PLAYER) {
			Creature* c = static_cast<Creature*>(entity);
			if (!c->IsAlive()) {
				it = entities.erase(it);
				continue;
			}
		}

		entity->Update();
		++it;

		if (player->GetParent() == endRoom) {
			PushNotification("THE END");
		}
	}
}

Command* World::GetCommandSystem() const {
	return commandSystem;
}