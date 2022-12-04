#include "Path.h"

namespace ai {
	namespace path {

		void Path::UpdatePath(std::vector<Vector2> waypoints, Vector2 start_pos, float turn_distance, float stopping_distance)
		{
			m_LookPoints = waypoints;
			m_TurnBoundaries.clear();
			m_TurnBoundaries.reserve(m_LookPoints.size());
			m_FinishLineIndex = m_LookPoints.size() - 1;

			Vector2 previous_point = start_pos;
			for (int i = 0; i < m_LookPoints.size(); i++)
			{
				Vector2 current_point = m_LookPoints.at(i);
				Vector2 direction_to_current_point = (current_point - previous_point).Normalize();
				Vector2 turn_boundary_point = i == m_FinishLineIndex ? current_point : current_point - direction_to_current_point * turn_distance;
				m_TurnBoundaries.emplace_back(Line{ turn_boundary_point, previous_point - direction_to_current_point * turn_distance });
				previous_point = turn_boundary_point;
			}

			float distance_from_endpoint = 0.f;
			for (int i = m_LookPoints.size() - 1; i > 0; i--)
			{
				distance_from_endpoint += Vector2::Distance(m_LookPoints.at(i), m_LookPoints.at(i - 1));
				if(distance_from_endpoint > stopping_distance){
					m_SlowDownIndex = i;
					break;
				}
			}
		}

		std::shared_ptr<Path> CreatePath()
		{
			return std::make_shared<Path>();
		}

	} // namespace PATH
} // namespace AI
