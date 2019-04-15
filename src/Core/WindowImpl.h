#pragma once

#if DRAUG_SFML
#include "Core/WindowImpl/SFML/SFMLWindowImpl.h"
namespace Draug {
	namespace details {
		class WindowImpl : public SFMLWindowImpl {
		};
	}
}
#endif
