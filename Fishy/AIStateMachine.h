//AIStateMachine.h

#pragma once

template <class entity_type>
class AIStateMachine
{
	AIStateMachine(entity_type* owner): m_pOwner(owner),
										m_pCurrentState(nullptr),
										m_pPreviousState(nullptr),
										m_pGlobalState(nullptr)
	{}

	void SetCurrentState(State<entity_type>* s)		{m_pCurrentState = s;}
	void SetPreviousState(State<entity_type>* s)	{m_pPreviousState = s;}
	void SetGlobalState(State<entity_type>* s)		{m_pGlobalState = s;}

	void Update() const
	{
		if (m_pGlobalState) m_pGlobalState->Execute(m_pOwner);

		if (m_pCurrent state) m_pCurrentstate->Execute(m_pOwner);
	}
	void ChangeState(State<entity_type>* pNewState)
	{
		assert(m_pNewState && "<StateMachine::ChangeState>: trying to change to a nullptr State");
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->Exit(m_pOwner);
		m_pCurrentState = m_pNewstate;
		m_pCurrentState->Enter(m_pOwner);
	}
	void RevertToPreviousState()
	{
		ChangeState(m_pPreviousState);
	}

	State<entity_type>* CurrentState() const {return m_pCurrentState;}
	State<entity_type>* PreviousState() const {return m_pPreviousState;}
	State<entity_type>* GlobalState() const {return m_pGlobalState;}

	bool isInState(const State<entity_type>& st)const;
private:
	entity_type* m_pOwner;
	State<entity_type>* m_pCurrentState;
	State<entity_type>* m_pPreviousState;
	State<entity_type>* m_pGlobalState;
};