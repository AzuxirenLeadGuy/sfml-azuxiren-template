#include "core/sfmlgameclass.hpp"
#include "scene/scene.hpp"

using namespace core;

auto Cwd(char *str) -> std::string
{
	std::string base(str);
	unsigned long idx = base.find_last_of('/');
	return idx < base.length() ? base.substr(0, idx) : std::string(".");
}

auto main(int argc, char *argv[]) -> int
{
	if (argc <= 0) { return 1; }
	const int fps = 60;
	const int width = 800;
	const int height = 600;
	const sf::Color clear = {35, 5, 15, 255};
	std::unique_ptr<SfmlGameClass::AbstractScene> scene1 = scenes::GetStarter();
	std::unique_ptr<SfmlGameClass::AbstractScene> scene2 = scenes::GetLoader();
	auto config = MyGameSettings{};
	auto settings = SfmlGameSettings{
	  fps,
	  false,
	  width,
	  height,
	  "My SFML Game",
	  clear,
	  sf::Style::Default,
	  sf::ContextSettings{},
	  Cwd(argv[0]),
	  config};
	SfmlGameClass game(settings, scene1, scene2);
	return SfmlGameClass::RunBareGame(game);
}
