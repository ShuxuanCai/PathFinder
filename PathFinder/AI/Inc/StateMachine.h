#pragma once

#include "State.h"

namespace AI
{
	template <class AgentType>
	class StateMachine
	{
	public:
		using StateType = State<AgentType>;

		StateMachine(AgentType& agent)
			: mAgent(agent)
		{}

		template <class NewStateType>
		void AddState(std::string stateName)
		{
			static_assert(std::is_base_of<StateType, NewStateType>::value, "[StateMachine] Can only add state for AgentType.");
			auto [iter, success] = mStates.emplace(std::move(stateName), std::make_unique<NewStateType>());
			if (!mCurrentState)
			{
				mCurrentStateName = iter->first;
				mCurrentState = iter->second.get();
				mCurrentState->Enter(mAgent);
			}
		}

		void Update(float deltaTime)
		{
			mCurrentState->Update(mAgent, deltaTime);
		}

		void ChangeState(const std::string& stateName)
		{
			auto iter = mStates.find(stateName);
			if (iter == mStates.end())
				return;

			mCurrentState->Exit(mAgent);
			mCurrentStateName = iter->first;
			mCurrentState = iter->second.get();
			mCurrentState->Enter(mAgent);
		}

		const char* GetStateName() const
		{
			return mCurrentStateName.c_str();
		}

	private:
		using StateMap = std::unordered_map<std::string, std::unique_ptr<StateType>>;

		AgentType& mAgent;
		std::string mCurrentStateName;
		StateType* mCurrentState = nullptr;
		StateMap mStates;
	};
}


/*
#include <XEngine.h>

void Test()
{
	// Array
	// - Indexed using number
	// - Internally stored as an array
	std::vector<std::string> myContactList;
	myContactList.push_back("abc123@hotmail.com");
	myContactList.push_back("knightrider@gmail.com");
	myContactList.push_back("quiksilver88@outlook.com");

	// Associative Array (ordered/sorted)
	// - Indexed using a key
	// - Internally stored as a binary tree
	std::map<std::string, std::string> myContactList2;
	myContactList2["Peter"] = "abc123@hotmail.com";
	myContactList2["John"] = "knightrider@gmail.com";
	myContactList2["Ann"] = "quiksilver88@outlook.com";

	// Associative Array (unordered/not sorted)
	// - Indexed using a key
	// - Internally stored as a hashtable
	// - Uses more memory, but faster lookup
	// - Introduced in C++17
	std::unordered_map<std::string, std::string> myContactList3;
	myContactList3["Peter"] = "abc123@hotmail.com";
	myContactList3["John"] = "knightrider@gmail.com";
	myContactList3["Ann"] = "quiksilver88@outlook.com";
}
*/