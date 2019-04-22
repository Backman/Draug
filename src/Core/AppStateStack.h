#pragma once

#include "Draug.h"
#include "Core/Types.h"

namespace Draug {
class AppState;

class AppStateStack {
public:
	using Iterator = std::vector<AppState*>::iterator;
	using ConstIterator = std::vector<AppState*>::const_iterator;

	AppStateStack() = default;
	~AppStateStack() {
		deleteAll();
	}

	inline void deleteAll() {
		while (m_states.empty() == false) {
			AppState* state = m_states.back();
			delete state;
			m_states.pop_back();
		}
	}

	inline void addState(AppState* state) {
		m_states.emplace(m_states.begin() + m_state_index, state);
		m_state_index++;
	}

	inline void addPriorityState(AppState* state) {
		m_states.emplace_back(state);
	}

	inline void removeState(AppState* state) {
		if (remove(state)) {
			m_state_index--;
		}
	}

	inline void removePriorityState(AppState* state) {
		remove(state);
	}

	inline Iterator begin() {
		return m_states.begin();
	}

	inline Iterator end() {
		return m_states.end();
	}

	inline ConstIterator begin() const {
		return m_states.begin();
	}

	inline ConstIterator end() const {
		return m_states.end();
	}
private:
	bool remove(AppState* state) {
		auto it = std::find(m_states.begin(), m_states.end(), state);
		if (it == m_states.end()) {
			return false;
		}
		m_states.erase(it);
		return true;
	}

	std::vector<AppState*> m_states;
	uint32 m_state_index = 0;
};
}
