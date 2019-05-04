#pragma once

#include "Draug.h"

namespace Draug {
struct Event;
class App;

struct AppStateContext {
	App* app;
};

class AppState {
public:
	AppState() = delete;
	AppState(const AppStateContext& context, const std::string& state_name) :
		context(context), state_name(state_name) {
	}
	virtual ~AppState() {}

	inline virtual void init() {}
	inline virtual void shutdown() {}
	inline virtual void tick() {}
	inline virtual bool onEvent(const Event& event) { return false; }

	std::string state_name;
	AppStateContext context;
};
}
