#pragma once
#include <iostream>
#include "bt/Node.h"
#include "bt/BehaviorTree.h"

class DerviedNode : public ai::bt::NodeWrapper {
public:
	ai::bt::Status Update() {
		std::cout << "Derived called!\n";
		return ai::bt::Status::Success;
	}
};

class BtTesting {
public:

	// Can be treated as an application entry point, called once.
	void Initialize() {
		std::cout << "\n\nBtTesting cout\n";

		ai::bt::BtPtr bt = ai::bt::CreateBt(); // Stores root as Node

		DerviedNode derived_node;
		derived_node.Update();	// Called derived node explicitly on the node; displays "Derived Called!"

		bt->SetRoot(derived_node);
		bt->Update();			// Called update on base class which stores derived node; displays "Node!"
	}
};