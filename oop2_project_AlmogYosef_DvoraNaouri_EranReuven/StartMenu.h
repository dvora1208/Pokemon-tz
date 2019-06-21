#pragma once
#include "Screen.h"
#include "Menu.h"
#include "Player.h"


using std::unique_ptr;

class StartMenu :	public Screen
{
public:
	StartMenu(Player& player);
	~StartMenu();

	// Inherited via Screen
	virtual void draw(RenderWindow & window) override;
	virtual void keyReleasedHandler(const Event & event) override;

private:
	sf::View m_view;
	sf::Sprite m_backGround;
	Menu m_menu;
	Player& m_player;
	unique_ptr<Screen> m_subScreen;
	sf::Music m_music;
	
};

