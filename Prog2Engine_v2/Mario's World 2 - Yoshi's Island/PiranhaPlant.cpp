#include "pch.h"
#include "PiranhaPlant.h"

#include "SoundManager.h"
#include "Texture.h"

PiranhaPlant::PiranhaPlant(Point2f position,bool isFlipped):Enemy(false,false,"EnemiesVaried.png",43,32,position),
m_IsFlipped(isFlipped)
{
}

void PiranhaPlant::Draw() const
{
	//Draw Stem
	glPushMatrix();
	{
		// Translate to the origin of the entity
		glTranslatef(m_Position.x + m_TxtWidth, m_Position.y + m_TxtHeight2, 0);

		if (m_IsFlipped == true)
		{
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}
		

		// Draw Entity
		m_EntityTxt->Draw(Rectf(-m_TxtWidth2 - 4, 0 - m_TxtHeight2, float(m_TxtWidth2 * 2), float(m_TxtHeight2 * 2)),
			Rectf(m_XTxtPos2, m_YTxtPos2, m_TxtWidth2, m_TxtHeight2));
	}
	glPopMatrix();

	//Draw Bud?
	glPushMatrix();
	{
		// Translate to the origin of the entity
		
		if (m_IsFlipped == false)
		{
			glTranslatef(m_Position.x + m_TxtWidth, m_Position.y + m_TxtHeight2 * 2, 0);
		}

		else
		{
			glTranslatef(m_Position.x + m_TxtWidth, m_Position.y, 0);
		}
		// Apply rotation around the middle of the entity
		glRotatef(m_AngleDeg, m_AngX, m_AngY, m_AngZ);

		// Apply scaling based on the facing direction
		if (m_IsFacingRight == false) {
			glScalef(m_ScaleX, m_ScaleY, m_ScaleZ);
		}
		else {
			glScalef(-m_ScaleX, m_ScaleY, m_ScaleZ);
		}


		// Draw Entity
		m_EntityTxt->Draw(Rectf(-m_TxtWidth, 0, float(m_TxtWidth * 2), float(m_TxtHeight * 2)),
			Rectf(m_XTxtPos, m_YTxtPos, m_TxtWidth, m_TxtHeight));



	}
	glPopMatrix();
}

void PiranhaPlant::Update(float elapsedSec,Point2f yoshiPos, SoundManager*& soundManager)
{
	m_Hitbox = Rectf(m_Position.x, m_Position.y, float(m_TxtWidth * 2), float(m_TxtHeight * 2));

	Vector2f toPlayer = yoshiPos - m_Position;
	float angleToPlayer = atan2f(toPlayer.y, toPlayer.x);
	m_AngleDeg = angleToPlayer * 180 /M_PI; // Set the Elf's angle to face the player
	m_AngleDeg += 270;
	m_AngZ = 1;

	if (yoshiPos.x > m_Position.x)
	{
		m_ScaleX = -1;
	}
	else
	{
		m_ScaleX = 1;
	}

	if (m_IsSFXReady == true)
	{
		Sound(soundManager);
		m_IsSFXReady = false;
	}

	if (m_SFXTimer > 0.4)
	{
		m_IsSFXReady = true;
		m_SFXTimer = 0;
	}

	m_SFXTimer += elapsedSec;

	//if (m_IsFlipped == true)
	//{
	//	m_ScaleY = -1;
	//}
}

void PiranhaPlant::Sound(SoundManager*& soundManager)
{
	soundManager->PlaySFX(SoundManager::EnemySFX::PiranhaPlantSFX);
}

void PiranhaPlant::Animate(float elapsedSec)
{
	m_FrameTime += elapsedSec;
	m_YTxtPos = 127;
	m_YTxtPos2 = 141;
	m_XTxtPos2 = 19;

	if (m_XTxtPos < 20 || m_XTxtPos > 91)
	{
		m_XTxtPos = 20;
	}

	if (m_FrameTime > 0.3)
	{
		m_XTxtPos += m_TxtWidth + 8;

		m_FrameTime = 0;
	}
}

void PiranhaPlant::Reset()
{
	Enemy::Reset();

	m_IsSFXReady  = false;
	m_SFXTimer   = 0;
}
