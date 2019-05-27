#pragma once

#include "Core/Event/Event.h"
#include "Log/Log.h"

namespace Draug {
namespace ECS {
class World;
}
}

namespace Draug {
class State;
class App;

struct StateContext {
	ECS::World* world;
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

	inline virtual void on_start() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: on_start", m_name);
#endif
	}

	inline virtual void on_stop() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: on_stop", m_name);
#endif
	}

	inline virtual void on_pause() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: on_pause", m_name);
#endif
	}

	inline virtual void on_resume() {
#ifdef DRAUG_DEBUG
		DRAUG_LOG_CORE_DEBUG("{0}: on_resume", m_name);
#endif
	}

	inline virtual StateTransition on_event(Draug::Event& event) {
		return StateTransition::none();
	}

	inline virtual StateTransition fixed_tick(float fixed_dt) {
		return StateTransition::none();
	}

	inline virtual StateTransition tick(float dt) {
		return StateTransition::none();
	}

	inline virtual void background_fixed_tick(float fixed_dt) {}
	inline virtual void background_tick(float dt) {}

	inline StateContext& context() { return m_context; }
	inline App* app() { return m_context.app; }
	inline ECS::World* world() { return m_context.world; }
	inline std::string& name() { return m_name; }

private:
	StateContext m_context;
	std::string m_name;
};
}
