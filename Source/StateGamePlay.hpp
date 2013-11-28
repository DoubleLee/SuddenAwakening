#pragma once

#ifndef STATEGAMEPLAY_H
#define STATEGAMEPLAY_H

#include "State.hpp"

class Level;

class StateGamePlay : public State
{
public:
	StateGamePlay();
	virtual ~StateGamePlay();

	virtual void Update();
	virtual void Draw();
	virtual void LoadFromXML(const string & file);
	virtual void ProcessEvent(const sf::Event & event);

	Level * GetLevel();

private:
	void LoadNewGame();

	unique_ptr<Level> mpLevel;
};

#endif // STATEGAMEPLAY_H
