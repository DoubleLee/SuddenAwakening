#pragma once

#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#include "State.hpp"

enum class ButtonID
	{
	BeginID = 0,
	NewGameButtonID,
	OptionsButtonID,
	ExitID,
	EndID
	};

class Button;

class StateMainMenu : public State
{
public:
	StateMainMenu();
	virtual ~StateMainMenu();

	virtual void Update();
	virtual void Draw();
	virtual void LoadFromXML(const string & file);
	virtual void ProcessEvent(const sf::Event & event);
private:
	void ChangeSelectionTo( int newSelection );
	void ChangeSelectionBy( int offset );
	void UserMadeSelection();
	vector< unique_ptr< Button > > mButtons;
	int mSelectedButton;
	unique_ptr<sf::Text> mpTitleText;
};

#endif // STATEMAINMENU_H
