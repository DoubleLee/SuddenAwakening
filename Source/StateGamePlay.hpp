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

	/**
	 * @brief GetLevel getter for the current level.
	 * @return The current level.
	 */
	Level * GetLevel();

private:
	/**
	 * @brief LoadNewGame is where a new game is loaded starting at level 1.
	 */
	void LoadNewGame();

	unique_ptr<Level> mpLevel;
};

#endif // STATEGAMEPLAY_H
