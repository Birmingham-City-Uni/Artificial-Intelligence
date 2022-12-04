#include "Blackboard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

namespace ai {

	void Blackboard::Initialize(std::string filename)
	{
		m_Filename = filename;
		ReadFile();
#ifdef LOGGING
		PrintBoard();
#endif // LOGGING
	}

	FloatPtr Blackboard::GetFloat(std::string name, float default_value)
	{
		if(m_Floats.find(name) == m_Floats.end()) {
			m_Floats.emplace(name, std::make_shared<float>(default_value));
			WriteFile();
		}
		return m_Floats[name];
	}

	BoolPtr Blackboard::GetBool(std::string name, bool default_value)
	{
		if (m_Bools.find(name) == m_Bools.end()) {
			m_Bools.emplace(name, std::make_shared<bool>(default_value));
			WriteFile();
		}
		return m_Bools[name];
	}

	ai::IntPtr Blackboard::GetInt(std::string name, int default_value)
	{
		if (m_Ints.find(name) == m_Ints.end()) {
			m_Ints.emplace(name, std::make_shared<int>(default_value));
			WriteFile();
		}
		return m_Ints[name];
	}

	void Blackboard::ReadFile()
	{
		std::vector<std::string> row;
		std::string line, word;

		std::fstream file(m_Filename, std::ios::in);
		if (file.is_open())
		{
			while (std::getline(file, line))
			{
				row.clear();
				std::stringstream str(line);

				while (getline(str, word, ',')) {
					row.push_back(word);
				}
				if (row[0] == "float") {
					FloatPtr value = std::make_shared<float>(std::stof(row[2]));
					m_Floats.emplace(row[1], value);
				}
				if (row[0] == "bool") {
					bool value = row[2] == "true" ? true : false;
					BoolPtr value2 = std::make_shared<bool>(value);
					m_Bools.emplace(row[1], value2);
				}
				if (row[0] == "int") {
					IntPtr value = std::make_shared<int>(std::stoi(row[2]));
					m_Ints.emplace(row[1], value);
				}
			}
		}
		else {
			std::cerr << "Could not open the file - " << m_Filename << "\n";
		}
		file.close();
	}

	void Blackboard::WriteFile()
	{
		std::vector<std::string> row;
		std::string line, word;

		std::ofstream file(m_Filename, std::ios::out);
		if (file.is_open())
		{
			std::cout << "Float dictionary writing...\n";
			for (const auto& element : m_Floats)
			{
				std::stringstream ss;
				ss << "float," << element.first << "," << *element.second << "\n";
				std::string line = ss.str();
				file << line;
			}
			std::cout << "Bool dictionary writing...\n";
			for (const auto& element : m_Bools)
			{
				std::stringstream ss;
				ss << "bool," << element.first << "," << *element.second << "\n";
				std::string line = ss.str();
				file << line;
			}
			std::cout << "Int dictionary writing...\n";
			for (const auto& element : m_Ints)
			{
				std::stringstream ss;
				ss << "int," << element.first << "," << *element.second << "\n";
				std::string line = ss.str();
				file << line;
			}
		}
		else {
			std::cerr << "Could not open the file - " << m_Filename << "\n";
		}
		file.close();
	}

	void Blackboard::PrintBoard()
	{
		std::cout << "Float dictionary: \n";
		for (const auto& element : m_Floats)
		{
			std::cout << element.first << " " << *element.second << "\n";
		}
		std::cout << "Bool dictionary: \n";
		for (const auto& element : m_Bools)
		{
			std::cout << element.first << " " << *element.second << "\n";
		}
	}

	BlackboardPtr CreateBlackboard(std::string filename)
	{
		BlackboardPtr value = std::make_shared<Blackboard>();
		value->Initialize(filename);
		return value;
	}

} // namespace ai