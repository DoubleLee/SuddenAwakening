#ifndef STATEGAMEPLAY_H
#define STATEGAMEPLAY_H

#include "State.hpp"

class StateGamePlay : public State
{
public:
	StateGamePlay();
	virtual ~StateGamePlay();

	virtual void Update();
	virtual void Draw();
	virtual void LoadFromXML(const string & file);
	virtual void ProcessEvent(const sf::Event & event);
};

#endif // STATEGAMEPLAY_H
