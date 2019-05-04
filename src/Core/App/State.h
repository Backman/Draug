#pragma once

#include "Core/Event/Event.h"

namespace Draug {
class State;
class App;

struct StateContext {
	App* app;
};

class StateTransition {
public:
	enum Type {
		None,
		Pop,
		Push,
		GoTo,
		Quit
	};

	~StateTransition() = default;

	inline static StateTransition none() {
		return StateTransition(Type::None);
	};

	inline static StateTransition quit() {
		return StateTransition(Type::Quit);
	};

	inline static StateTransition pop() {
		return StateTransition(Type::Pop);
	};

	inline static StateTransition push(State* state) {
		return StateTransition(state, Type::Push);
	};

	inline static StateTransition to(State* state) {
		return StateTransition(state, Type::GoTo);
	};

	Type type;
	State* state;
private:
	StateTransition(Type type) :
		type(type), state(nullptr) {
	}
	StateTransition(State* state, Type type) :
		state(state), type(type) {
	}
};

class State {
public:
	State(const std::string& name) :
		name(name) {
	}
	virtual ~State() = default;

	virtual void onStart() {}
	virtual void onStop() {}
	virtual void onPause() {}
	virtual void onResume() {}

	virtual StateTransition onEvent(Draug::Event& event) {
		return StateTransition::none();
	}

	virtual StateTransition fixedTick() {
		return StateTransition::none();
	}

	virtual StateTransition tick(float dt) {
		return StateTransition::none();
	}

	virtual void backgroundFixedTick() {}
	virtual void backgroundTick(float dt) {}

	std::string name;
};
}
