#pragma once
#include "Dll.h"
#include <map>
#include <string>
#include <memory>

namespace ai{

	class Blackboard;
	typedef std::shared_ptr<Blackboard> BlackboardPtr;
	typedef std::shared_ptr<bool> BoolPtr;
	typedef std::shared_ptr<float> FloatPtr;
	typedef std::shared_ptr<int> IntPtr;

	class IBlackboard {
	public:
		virtual FloatPtr GetFloat(std::string name, float default_value) = 0;
		virtual BoolPtr GetBool(std::string name, bool default_value) = 0;
		virtual IntPtr GetInt(std::string name, int default_value) = 0;
	};

	class Blackboard : public IBlackboard {
	public:
		Blackboard() {}
		void Initialize(std::string filename);

		FloatPtr GetFloat(std::string name, float default_value);
		BoolPtr GetBool(std::string name, bool default_value);
		IntPtr GetInt(std::string name, int default_value);

	private:
		void ReadFile();
		void WriteFile();
		void PrintBoard();

	private:
		std::map<std::string, FloatPtr> m_Floats;
		std::map<std::string, BoolPtr> m_Bools;
		std::map<std::string, IntPtr> m_Ints;
		std::string m_Filename;
	};

	extern "C++" AI_API BlackboardPtr CreateBlackboard(std::string filename);
} // namespace ai