#include "Player.h"
#include "Map.h"
#include "Door.h"
#include "GameManager.h"

using sf::Keyboard;

Player::Player() : m_animation(*this, Resource::texture("player"), Vector2u(3, 4), 4.f)
{
	m_sprite.setTexture(Resource::texture("player"), true);
	m_sprite.setTextureRect(sf::IntRect(16, 0, 16, 19));
	m_animation.addAnimation("down", 0);
	m_animation.addAnimation("up", 1);
	m_animation.addAnimation("right", 2);
	m_animation.addAnimation("left", 3);
	m_pov.setSize(Vector2f(1.f, 1.f));
}

Player & Player::instance()
{
	static Player inst;
	return inst;
}

Player::~Player()
{
}

void Player::update(GameManager & gm)
{
	bool inGrass = false;
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		m_direction = Vector2f(0, -m_moveSpeed);	// up = {0, -y}
		move(inGrass);
		m_animation.play("up");
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX / 2, -sizeY / 8.f));
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		m_direction = Vector2f(0, m_moveSpeed);	// down = {0, y}
		move(inGrass);
		m_animation.play("down");
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX / 2, sizeY * 1.12f));
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		m_direction = Vector2f(-m_moveSpeed, 0);	// left = {-x, 0}
		move(inGrass);
		m_animation.play("left");
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(-sizeX / 8, sizeY / 2));
		if (inGrass)
			gm.wildPokemonBattle();
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		m_direction = Vector2f(m_moveSpeed, 0);	// right = {x, 0}
		move(inGrass);
		m_animation.play("right");
		m_pov.setPosition(m_sprite.getPosition() + Vector2f(sizeX * 1.12f, sizeY / 2));
		if (inGrass)
			gm.wildPokemonBattle();
	}
}

void Player::setMap(const Map * map)
{
	Character::setMap(map);
	m_map = map->getName();
}

void Player::handleCollision(Collider & collider)
{
	collider.handleCollision(*this);
}

void Player::handleCollision(Player & player)
{
}

void Player::handleCollision(NPC & npc)
{
	stop();
}

void Player::handleCollision(Pokemon & pokemon)
{
}

void Player::handleCollision(Door & door)
{
	m_map = door.getDestination();
	m_sprite.setPosition(door.getDestPos());
}
