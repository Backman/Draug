#pragma once

#include "Core/Event/Event.h"
#include "Log/Log.h"

namespace Draug {
class State;
class App;
class World;

struct StateContext {
	World* world;
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
	State(const StateContext& context, const std::string& name) :
		m_context(context), m_name(name) {
	}
	virtual ~State() = default;

	inline virtual void onStart() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: onStart", m_name);
#endif
	}

	inline virtual void onStop() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: onStart", m_name);
#endif
	}

	inline virtual void onPause() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: onPause", m_name);
#endif
	}

	inline virtual void onResume() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: onResume", m_name);
#endif
	}

	inline virtual StateTransition onEvent(Draug::Event& event) {
		return StateTransition::none();
	}

	inline virtual StateTransition fixedTick() {
		return StateTransition::none();
	}

	inline virtual StateTransition tick(float dt) {
		return StateTransition::none();
	}

	inline virtual void backgroundFixedTick() {}
	inline virtual void backgroundTick(float dt) {}

	inline StateContext& context() { return m_context; }
	inline App* app() { return m_context.app; }
	inline World* world() { return m_context.world; }
	inline std::string& name() { return m_name; }

private:
	StateContext m_context;
	std::string m_name;
};
}
