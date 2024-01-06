#include "../core/sfmlgameclass.hpp"
#include "../utils/utils.hpp"
#include "scene.hpp"

using namespace core;
using namespace utils;
using KlPtr = std::unique_ptr<KeyListener>;
namespace scenes
{
	class Starter : public SfmlGameClass::AbstractScene
	{
		KlPtr listener;

	  public:
		Starter() = default;
		auto Load(SfmlGameClass &game) -> int override;
		auto PollEvent(SfmlGameClass &game, sf::Event event) -> int override;
		auto Update(SfmlGameClass &game, long time) -> UpdateResult override;
		auto Destroy(SfmlGameClass &game) -> int override;
	};
} // namespace scenes

using namespace scenes;

auto Starter::Load(SfmlGameClass & /*unused*/) -> int
{
	auto init = {sf::Keyboard::Key::Escape, sf::Keyboard::Key::Enter};
	listener = std::make_unique<KeyListener>(init);
	return 0;
}

auto Starter::PollEvent(SfmlGameClass & /*unused*/, sf::Event event) -> int
{
	if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
	{
		listener->Update(event.key.code, event.type == sf::Event::KeyPressed);
	}
	return 0;
}

auto Starter::Update(SfmlGameClass &game, const long /*unused*/) -> Starter::UpdateResult
{
	if (listener->ViewKey(sf::Keyboard::Escape) == KeyState::Just_Release)
	{
		game.ExitCall();
	}
	listener->FrameEnd();
	return Starter::UpdateResult{0, nullptr};
}

auto Starter::Destroy(SfmlGameClass & /*unused*/) -> int
{
	listener.reset();
	return 0;
}

auto scenes::GetStarter() -> ScenePtr { return std::make_unique<Starter>(); }
