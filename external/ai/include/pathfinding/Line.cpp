#include "Line.h"
namespace ai {
	namespace path {

		Line::Line(Vector2 point_on_line, Vector2 point_perpendiculat_to_line)
		{
			float dx = point_on_line.x - point_perpendiculat_to_line.x;
			float dy = point_on_line.y - point_perpendiculat_to_line.y;

			m_PerpendiculatGradient = dx == 0 ? m_VerticalLineGradient : dy / dx;
			m_Gradient = m_PerpendiculatGradient == 0 ? m_VerticalLineGradient : -1 / m_PerpendiculatGradient;

			m_InterceptY = point_on_line.y - m_Gradient * point_on_line.x;
			m_Point1 = point_on_line;
			m_Point2 = point_on_line + Vector2{ 1, m_Gradient };

			m_ApproachSide = GetSide(point_perpendiculat_to_line);
		}

		bool Line::GetSide(Vector2 point)
		{
			return (point.x - m_Point1.x) * (m_Point2.y - m_Point1.y) > (point.y - m_Point1.y) * (m_Point2.x - m_Point1.x);
		}

		bool Line::HasCrossedLine(Vector2 point)
		{
			return GetSide(point) != m_ApproachSide;
		}

		float Line::DistanceFromPoint(Vector2 point)
		{
			float y_intercept_perpendicular = point.y - m_PerpendiculatGradient * point.x;
			float x_intersect = (y_intercept_perpendicular - m_InterceptY) / (m_Gradient - m_PerpendiculatGradient);
			float y_intersect = m_Gradient * x_intersect * m_InterceptY;
			return Vector2::Distance(point, { x_intersect, y_intersect });
		}

	} // namespace PATH
} // namespace AI