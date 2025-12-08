#include "engine/actors/ActorManager.hpp"
#include <format>
#include <iostream>

using namespace geng;

// Constructor
ActorManager::ActorManager() noexcept : numObjects(0) {}

// Add object, pointer (preferred method)
Actor * ActorManager::add_actor(Actor *a) noexcept {
	// If the ID already exists, we don't add, it's redundant.
	if (a->t.id != -1 && actorMap.find(a->t.id) != actorMap.end())
		return nullptr;
	// If our flag is notempty
	if (!a->tagged())
		std:: cerr << "Actor Tagged."
					<< "\nObject Info:\n"
					<< a->to_string() << std::endl;

	actorMap[a->t.id] = a;
	return a;
}

// Adding an object (non-pointer)
Actor* ActorManager::add_actor(Actor a) noexcept {
	auto* o = new Actor(a);
	return add_actor(o);
}

void ActorManager::add_actors(const std::vector<Actor *>& vec) noexcept {
	for (auto& a: vec)
		add_actor(a);
}

// We have to remove an object by its id
void ActorManager::dissolve(int id) {
	// Exit if the object doesn't exist
	if (actorMap.find(id) == actorMap.end()) return;
	// Otherwise, we grab the id and push it onto the id stack
	stack.push(id);
	// Then, we can remove the object from our map
	delete actorMap[id];
	actorMap.erase(id);
}

// We take in an object and convert it to an id.
void ActorManager::dissolve(const Actor* a) {
	dissolve(a->t.id);
}

// This grabs ids from all actors and removes them.
void ActorManager::dissolve(std::vector<Actor *> vec) {
	for (auto& a: vec)
		dissolve(a->t.id);
}

std::vector<AnimInfo*> ActorManager::update_objects(){
	std::vector<AnimInfo*> ret;
	for (auto& [id, o]: actorMap){
		Actor& actor = *o;
		// Print out a flag for testing purposes.
		if (!actor.flag.empty())
			std:: cerr << "Actor Flagged: " << actor.flag
						<< "\nObject Info:\n"
						<< actor.to_string() << std::endl;
		// Update our object's position
		actor.update();
		// Ticks our object's animation frame
		// SheetManager -> Object's Sheet -> tick_object
		if (actor.anim.update()) {
			ret.push_back(&actor.anim);
		}
	}
	return ret;
}

std::unordered_map<int, Actor*>& ActorManager::get_actor_list() {
	return actorMap;
}

std::string ActorManager::to_string() {
	std::string ret;
	ret += "Printing ObjectManager: ";
	ret += "\n::Num actors: " + std::to_string(actorMap.size());
	ret += "\n::Stack size: " + std::to_string(stack.num_elements());
	ret += "\n::Stack memory: " + std::to_string(stack.size());
	ret += "\n::Stack top: " + std::to_string(stack.top());
	ret += "\n::Next ID: " + std::to_string(nextID);
	ret += "\n";
	return ret;

}
