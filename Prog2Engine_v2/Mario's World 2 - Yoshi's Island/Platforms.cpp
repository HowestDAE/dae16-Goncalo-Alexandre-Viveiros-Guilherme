#include "pch.h"
#include "Platforms.h"
#include "Texture.h"
#include "utils.h"
#include "Vector2f.h"

Platforms::Platforms(Point2f position, float txtWidth, float txtHeight, float platformWidth, float platformHeight, const std::string& texturePath, float radius) :
	m_PlatformTxt{ new Texture{ texturePath } },
	m_TxtHeight{ txtHeight },
	m_TxtWidth{ txtWidth },
	m_Position{ position },
	m_PlatformWidth(platformWidth),
	m_PlatformHeight(platformHeight),
	m_Radius{ radius }
{
	m_PlatformPos1.y = m_Position.y + m_Radius;
	m_PlatformPos1.x = m_Position.x;

	m_PlatformPos2.y = m_Position.y;
	m_PlatformPos2.x = m_Position.x + m_Radius;

	m_PlatformPos3.y = m_Position.y - m_Radius;
	m_PlatformPos3.x = m_Position.x;

	m_PlatformPos4.y = m_Position.y;
	m_PlatformPos4.x = m_Position.x - m_Radius;
}

Platforms::~Platforms()
{
	delete m_PlatformTxt;
}

void Platforms::Draw() const
{

	m_PlatformTxt->Draw(Rectf(m_PlatformPos1.x - m_PlatformWidth /2, m_PlatformPos1.y, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));
	m_PlatformTxt->Draw(Rectf(m_PlatformPos2.x - m_PlatformWidth/2, m_PlatformPos2.y, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));
	m_PlatformTxt->Draw(Rectf(m_PlatformPos3.x - m_PlatformWidth/2, m_PlatformPos3.y, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));
	m_PlatformTxt->Draw(Rectf(m_PlatformPos4.x - m_PlatformWidth/2, m_PlatformPos4.y, m_PlatformWidth, m_PlatformHeight),
			Rectf(0, 0, m_TxtWidth, m_TxtHeight));

	utils::DrawPolygon(m_Platform1Vertices);
	utils::DrawPolygon(m_Platform2Vertices);
	utils::DrawPolygon(m_Platform3Vertices);
	utils::DrawPolygon(m_Platform4Vertices);

	
}

void Platforms::Update()
{
	m_Angle += 0.0025;
	m_PlatformPos1 = m_Position + Vector2f(cos(m_Angle), sin(m_Angle)) * m_Radius;
	m_PlatformPos2 = m_Position + Vector2f(cos(m_Angle + (M_PI/2)), sin(m_Angle + (M_PI / 2) ) ) * m_Radius;
	m_PlatformPos3 = m_Position + Vector2f(cos(m_Angle + M_PI), sin(m_Angle + M_PI)) * m_Radius;
	m_PlatformPos4 = m_Position + Vector2f(cos(m_Angle + ((3*M_PI)/2)), sin(m_Angle + ((3 * M_PI) / 2))) * m_Radius;

	m_Platform1Vertices[0] = Point2f(m_PlatformPos1.x - (m_PlatformWidth /2),(m_PlatformPos1.y + m_PlatformHeight));
	m_Platform2Vertices[0] = Point2f(m_PlatformPos2.x - (m_PlatformWidth /2),(m_PlatformPos2.y + m_PlatformHeight));
	m_Platform3Vertices[0] = Point2f(m_PlatformPos3.x - (m_PlatformWidth /2),(m_PlatformPos3.y + m_PlatformHeight));
	m_Platform4Vertices[0] = Point2f(m_PlatformPos4.x - (m_PlatformWidth /2),(m_PlatformPos4.y + m_PlatformHeight));

	m_Platform1Vertices[1] = Point2f(m_PlatformPos1.x + (m_PlatformWidth / 2), (m_PlatformPos1.y + m_PlatformHeight));
	m_Platform2Vertices[1] = Point2f(m_PlatformPos2.x + (m_PlatformWidth / 2), (m_PlatformPos2.y + m_PlatformHeight));
	m_Platform3Vertices[1] = Point2f(m_PlatformPos3.x + (m_PlatformWidth / 2), (m_PlatformPos3.y + m_PlatformHeight));
	m_Platform4Vertices[1] = Point2f(m_PlatformPos4.x + (m_PlatformWidth / 2), (m_PlatformPos4.y + m_PlatformHeight));

	m_PlatformVertices[0] = m_Platform1Vertices;
	m_PlatformVertices[1] = m_Platform2Vertices;
	m_PlatformVertices[2] = m_Platform3Vertices;
	m_PlatformVertices[3] = m_Platform4Vertices;
}

std::vector<std::vector<Point2f>> Platforms::GetPlatformVertices()
{
	return m_PlatformVertices;
}
