#pragma once
#include "Collider.h"

using sf::RectangleShape;
using sf::Vector2f;
using std::string;

class Door : public Collider
{
public:
	// c-tor
	Door(const Vector2f & size, const string & dest, const Vector2f & destPos);
	// d-tor
	~Door();

	// Inherited via Collider
	virtual void draw(RenderWindow & window) override;
	virtual void setTextureRect(const IntRect & rect) override;
	virtual void setPosition(const Vector2f & pos) override { m_bounds.setPosition(pos); }
	virtual FloatRect getGlobalBounds() const override { return m_bounds.getGlobalBounds(); }
	virtual void handleCollision(Collider & collider) override;
	virtual void handleCollision(Player & player) override;
	virtual void handleCollision(NPC & npc) override;
	virtual void handleCollision(Door & door) override;

	// Getters
	string getDestination() const { return m_destination; }
	Vector2f getDestPos() const { return m_destPos; }

private:
	RectangleShape m_bounds;	// bounds of the door
	string m_destination;		// the destination which the door moves to
	Vector2f m_destPos;			// the position in the new destination
};

