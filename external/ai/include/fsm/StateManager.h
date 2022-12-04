#pragma once
#include "../Dll.h"
#include <memory>
#include <functional>
#include <string>

namespace ai {
	namespace fsm {

		class StateManager;
		class State;

		typedef std::shared_ptr<StateManager> ManagerPtr;
		typedef std::shared_ptr<State> StatePtr;
		typedef std::function<void(const float delta_time)> Function;

		class IState {
			virtual void Update(const float delta_time) = 0;
		};

		class State : public IState {
		public:
			State() {};
			State(ManagerPtr manager, std::string name, Function function);
			virtual ~State() {};

			void Update(const float delta_time);
		protected:
			std::string m_StateName;
			ManagerPtr m_Manager;
			Function m_Func;
		};

		class IStateManager {
		public:
			virtual void SetState(StatePtr& state) = 0;
			virtual StatePtr GetState() = 0;
			virtual void KillManager() = 0;
			virtual void Update(const float delta_time) = 0;
		};

		class StateManager : public IStateManager
		{
		public:
			StateManager();

			void SetState(StatePtr& state);
			StatePtr GetState();
			void KillManager();
			void Update(const float delta_time);

		private:
			StatePtr m_CurrentState;
		};

		extern "C++" AI_API ManagerPtr GetStateManager();
		extern "C++" AI_API StatePtr CreateState(ManagerPtr, std::string, Function);

	} // namespace FSM
} // namespace AI