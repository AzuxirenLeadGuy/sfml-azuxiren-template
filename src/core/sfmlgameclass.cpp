#include "sfmlgameclass.hpp"
#include <thread>

using namespace core;

using Sceneptr = std::unique_ptr<SfmlGameClass::AbstractScene>;

SfmlGameClass::SfmlGameClass(
  SfmlGameSettings &init_settings, Sceneptr &main_scene, Sceneptr &back_scene)
    : Window(
	sf::VideoMode(init_settings.Width, init_settings.Height), init_settings.Title,
	init_settings.WindowStyle, init_settings.Context),
      Config(init_settings)
{
	main.swap(main_scene);
	back.swap(back_scene);
	_exit_called = false;
	_is_loading = false;
	Window.setPosition(sf::Vector2i(0, 0));
	if (init_settings.VerticalSyncEnabled) { Window.setVerticalSyncEnabled(true); }
	else { Window.setFramerateLimit(init_settings.FPS); }
	_main_error = 0;
	_thread_err = 0;
}

SfmlGameClass::~SfmlGameClass() = default;

void SfmlGameClass::ExitCall() { _exit_called = true; }

auto SfmlGameClass::Initialize() -> int { return (main->Load(*this)) & (back->Load(*this)); }

auto SfmlGameClass::ShutDown() -> int
{
	int err = main->Destroy(*this) & back->Destroy(*this);
	main.reset();
	back.reset();
	return err;
}

auto SfmlGameClass::RunFrame() -> int
{
	auto &scene = _is_loading ? back : main;
	sf::Event event;
	int err = 0;
	while (Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) { ExitCall(); }
		else if ((err = scene->PollEvent(*this, event)) != 0) { break; }
	}
	if (err > 0) { return err; }

	Window.clear(Config.ClearColor);

	auto up_result = scene->Update(*this, _time_taken);
	if (up_result.Valid != 0) { return up_result.Valid; }
	if (_is_loading) { goto stop; }
	else if (_thread_err != 0) { return _thread_err; }
	else if (up_result.Next != nullptr)
	{
		_is_loading = true;
		std::thread(
		  [&]()
		  {
			  _thread_err = main->Destroy(*this);
			  if (_thread_err != 0) { return; }
			  main.swap(up_result.Next);
			  up_result.Next.reset();
			  _thread_err = main->Load(*this);
			  _is_loading = false;
		  });
	}

stop:
	Window.display();
	_time_taken = _clock.restart().asMicroseconds();
	return _main_error;
}

auto SfmlGameClass::RunBareGame(SfmlGameClass &game) -> int
{
	game._main_error = game.Initialize();
	while (game._main_error == 0 && !game._exit_called)
	{
		game._main_error = game.RunFrame();
	}
	return game._main_error != 0 ? game._main_error : game.ShutDown();
}
