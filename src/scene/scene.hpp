#ifndef SCENE
#define SCENE
#include "../core/sfmlgameclass.hpp"

using namespace core;
using ScenePtr = std::unique_ptr<SfmlGameClass::AbstractScene>;
struct core::MyGameSettings
{
	// Define custom game parameters here
};
namespace scenes
{
	auto GetStarter() -> ScenePtr;
	auto GetLoader() -> ScenePtr;
} // namespace scenes

#endif
