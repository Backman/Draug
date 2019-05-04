#pragma once

#include "State.h"
#include "Log/Log.h"

namespace Draug {
class StateMachine {
public:
	StateMachine() = default;
	~StateMachine() = default;

	inline void init(State* start_state) {
		m_state_stack.emplace_back(start_state);
	}

	inline void start() {
		if (m_state_stack.empty()) {
			DRAUG_LOG_CORE_ERROR("Starting state machine without a start state");
			return;
		}
		if (m_running) {
			return;
		}
		State* start_state = m_state_stack.back();
		start_state->onStart();
		m_running = true;
	}

	inline bool isRunning() const { return m_running; }

	inline void tick(float dt) {
		if (m_state_stack.empty()) {
			return;
		}
		State* curr_state = m_state_stack.back();
		StateTransition t = curr_state->tick(dt);
		for (size_t i = 0; i < m_state_stack.size(); i++) {
			m_state_stack[i]->backgroundTick(dt);
		}
		transition(t);
	}

	inline void fixedTick() {
		if (m_state_stack.empty()) {
			return;
		}
		State* curr_state = m_state_stack.back();
		StateTransition t = curr_state->fixedTick();
		for (size_t i = 0; i < m_state_stack.size(); i++) {
			m_state_stack[i]->backgroundFixedTick();
		}
		transition(t);
	}

	inline void onEvent(Draug::Event& event) {
		if (m_state_stack.empty()) {
			return;
		}
		StateTransition t = m_state_stack.back()->onEvent(event);
		transition(t);
	}

	inline void transition(const StateTransition& transition) {
		switch (transition.type) {
			case StateTransition::Type::GoTo:
			{
				goTo(transition.state);
			}
			break;
			case StateTransition::Type::Push:
			{
				push(transition.state);
			}
			break;
			case StateTransition::Type::Pop:
			{
				pop();
			}
			break;
			case StateTransition::Type::Quit:
			{
				stop();
			}
			break;
			case StateTransition::Type::None:
			default:
				break;
		}
	}

	inline State* top() { return m_state_stack.back(); }

private:
	inline void stop() {
		while (m_state_stack.empty() == false) {
			popAndDelete();
		}
		m_running = false;
	}

	inline void goTo(State* state) {
		popAndDelete();
		m_state_stack.emplace_back(state);
		state->onStart();
	}

	inline void push(State* state) {
		if (m_state_stack.empty() == false) {
			State* curr_state = m_state_stack.back();
			curr_state->onPause();
		}
		m_state_stack.emplace_back(state);
		state->onStart();
	}

	inline void pop() {
		popAndDelete();
		if (m_state_stack.empty() == false) {
			State* curr_state = m_state_stack.back();
			curr_state->onResume();
		}
		else {
			m_running = false;
		}
	}

	inline void popAndDelete() {
		if (m_state_stack.empty()) {
			return;
		}
		State* state = m_state_stack.back();
		state->onStop();
		m_state_stack.pop_back();
		delete state;
	}

	bool m_running;
	std::vector<State*> m_state_stack;
};
}
