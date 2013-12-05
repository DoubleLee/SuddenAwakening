#pragma once

#ifndef LEVELONE_HPP
#define LEVELONE_HPP

#include "Level.hpp"

class LevelOne : public Level
{
public:
	LevelOne();
	virtual ~LevelOne();

	virtual void Update();
	virtual void Draw();

	virtual void LoadFromXML(const string & file);
	virtual void ProcessEvent(const sf::Event & event);

protected:
};

#endif // LEVELONE_HPP
