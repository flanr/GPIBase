// State.h
#include "stdafx.h"
#pragma once



class State
{
public:
	virtual ~State(){};
	/**
	Called upon entering state
	**/
	virtual bool EnterState() = 0;
	/**
	Called when changing state and old state exits
	**/
	virtual void ExitState() = 0;
	/**
	Parameter Deltatime
	Handles State Update
	**/
	virtual bool Update(float p_fDeltatime) = 0;
	/**
	Draws State
	**/
	virtual void Draw() = 0;
	/**
	Changes state to the states default Next State
	**/
	virtual std::string Next() =0 ;
	/**
	Returns True if Type == &p_type is same as State
	**/
	virtual bool IsType(const std::string &p_sType) = 0;
	/**
	Returns Current State
	**/
	virtual std::string GetCurrentState() = 0;

protected:
	std::string m_sCurrentState;

};



