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
	/**
	 * @brief ChangeSelectionTo changes the currently selected button to the ID sent in.  Checks for validity.
	 * @param newSelection The ID to which should be set to selected.
	 */
	void ChangeSelectionTo( int newSelection );

	/**
	 * @brief ChangeSelectionBy changes the currently selected button by the number passed in, can be + or -.  Checks for validity.
	 * @param offset The amount to change the selected button by in either + or -.
	 */
	void ChangeSelectionBy( int offset );

	/**
	 * @brief UserMadeSelection is the call that will accept a chosen selection from the user.
	 * This is where this state tells the game switch to a new state.
	 */
	void UserMadeSelection();
	vector< unique_ptr< Button > > mButtons;
	int mSelectedButton;
	unique_ptr<sf::Text> mpTitleText;
};

#endif // STATEMAINMENU_H
