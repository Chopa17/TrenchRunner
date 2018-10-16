///////////////////////////////////////////////////////////////////////////////////////////////////
//																								 //
// TR_Entity.h by Sam Brind																         //
//		- The base entity class											                         //
//		- By Sam Brind																			 //
//																								 //
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef TR_ENTITY_H
#define TR_ENTITY_H

#include "SFML/System/Vector2.hpp"

class TR_Entity
{
public:
	inline bool IsDead() { return m_bIsDead; }
	inline void MakeDead() { m_bIsDead = true; }


private:
	bool m_bIsDead;
	sf::Vector2f m_xPosition;
	//TODO : a collision box
};

#endif
