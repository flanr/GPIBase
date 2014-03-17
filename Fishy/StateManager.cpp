// StateManager.cpp
#include "stdafx.h"
#include "StateManager.h"
#include "State.h"

StateManager::StateManager()
{
	m_pCurrentState = nullptr;

}

StateManager::~StateManager()
{
	auto it = m_aStates.begin();
	while (it != m_aStates.end())
	{
		delete (*it);
		it++;
	}
	m_aStates.clear();
}

State *StateManager::GetCurrentState()
{
	return m_pCurrentState;
}


string StateManager::CurrentState()
{
	return m_pCurrentState->GetCurrentState();
}

void StateManager::Attach(State *p_pState)
{
	m_aStates.push_back(p_pState);
}

void StateManager::Update(float p_fDeltatime)
{
	if (m_aStates.empty())
	{
		return;
	}
	if (!m_pCurrentState->Update(p_fDeltatime))
	{
		cout << "asdasd" << endl;
		ChangeState();
	}
}

void StateManager::Draw()
{
	if (m_pCurrentState == nullptr)
	{
		return;
	}
	m_pCurrentState->Draw();
}

void StateManager::SetState(const string &p_sType)
{
	for (unsigned int i = 0; i < m_aStates.size(); i++)
	{
		if (m_aStates[i]->IsType(p_sType))
		{
			m_pCurrentState = m_aStates[i];
			m_pCurrentState->EnterState();
			return;
		}
	}
}

void StateManager::ChangeState()
{
	cout << "StateManager::ChangeState()" << endl;
	string next = m_pCurrentState->Next();
	if (m_pCurrentState != nullptr)
	{
		m_pCurrentState->ExitState();
		m_pCurrentState = nullptr;

	}
	for (unsigned int i = 0; i < m_aStates.size(); i++)
	{
		if (m_aStates[i]->IsType(next))
		{
			m_pCurrentState = m_aStates[i];
			m_pCurrentState->EnterState();
			return;
		}
	}
}

bool StateManager::IsRunning()
{
	return m_pCurrentState != nullptr;
}
