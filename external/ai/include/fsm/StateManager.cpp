#include "StateManager.h"
#include <memory>
#include <functional>
#include <Windows.h>
#include <iostream>
#include "../Dll.h"

namespace ai {
	namespace fsm {
		State::State(ManagerPtr manager, std::string name, Function function)
		{
			m_Manager = manager;
			m_Func = function;
			m_StateName = name;
		}

		void State::Update(const float delta_time)
		{
			m_Func(delta_time);
		}

		StateManager::StateManager()
		{
			m_CurrentState = std::make_unique<State>();
		}

		void StateManager::SetState(StatePtr& state)
		{
			m_CurrentState = state;
		}

		StatePtr StateManager::GetState()
		{
			return m_CurrentState;
		}

		void StateManager::KillManager()
		{
			m_CurrentState = nullptr;
		}

		void StateManager::Update(const float delta_time)
		{
			if (m_CurrentState) {
				m_CurrentState->Update(delta_time);
			}
		}

		ManagerPtr GetStateManager()
		{
			return std::make_shared<StateManager>();
		}

		StatePtr CreateState(ManagerPtr manager, std::string name, Function function)
		{
			return std::make_shared<State>(manager, name, function);
		}

	} // namespace FSM
} // namespace AI