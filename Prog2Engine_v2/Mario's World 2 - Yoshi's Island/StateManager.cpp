#include "pch.h"
#include "StateManager.h"

#include "Texture.h"

StateManager::StateManager() :
	m_CurrentState(States::LevelSelector),
	m_LevelSelTex1(new Texture{ "Map.png" }),
	m_LevelSelTex2(new Texture{ "LevelSelectorTab.png" }),
	m_PauseScreenBG(new Texture{ "PauseMenu.png" }),
	m_PauseScreenIcons(new Texture{"PauseIcons.png"}),
	m_DeathScreen(new Texture{"DeathScreen.png"})
{
}

StateManager::~StateManager()
{
	delete m_LevelSelTex1;
	delete m_LevelSelTex2;
	delete m_PauseScreenBG;
	delete m_PauseScreenIcons;
	delete m_DeathScreen;
}

StateManager::States StateManager::GetState()
{
	return m_CurrentState;
}

void StateManager::SetState(States state)
{
	m_CurrentState = state;
}

void StateManager::Draw() const
{
	if (m_CurrentState == States::LevelSelector)
	{
		glPushMatrix();
		{
			glScalef(2, 2, 1);
			m_LevelSelTex1->Draw(Point2f(0,0));
			m_LevelSelTex2->Draw(Point2f(35,125));
		}
		glPopMatrix();
	}

	if (m_CurrentState == States::Pause)
	{
		//Draws the BG for the pause menu
		m_PauseScreenBG->Draw();

		//Draws The amount of Stars,Flowers and Red Coins Collected
		glPushMatrix();
		{
			glScalef(2, 2, 1);

			//Draws Stars
			const int firstDigitStars = m_Stars / 10;
			const int secondDigitStars = m_Stars % 10;

			if (firstDigitStars > 0)
			{
				m_PauseScreenIcons->Draw(Point2f{ 155,170 }, Rectf{ float(9 * firstDigitStars),15,9,15 });
			}
			m_PauseScreenIcons->Draw(Point2f{ 155 + 9,170 }, Rectf{ float(9 * secondDigitStars),15,9,15 });
			

			//Draws Red Coins
			const int firstDigitRedCoins = m_RedCoins / 10;
			const int secondDigitRedCoins = m_RedCoins % 10;

			if (firstDigitRedCoins > 0)
			{
				m_PauseScreenIcons->Draw(Point2f{ 155,140 }, Rectf{ float(9 * firstDigitRedCoins),15,9,15 });
			}
			m_PauseScreenIcons->Draw(Point2f{ 155 + 9,140}, Rectf{ float(9 * secondDigitRedCoins),15,9,15 });
			

			//Draws Flowers
			const int firstDigitFlowers = m_Flowers / 10;
			const int secondDigitFlowers = m_Flowers % 10;

			if (firstDigitFlowers > 0)
			{
				m_PauseScreenIcons->Draw(Point2f{ 165,115 }, Rectf{ float(9 * firstDigitFlowers),15,9,15 });
			}
			m_PauseScreenIcons->Draw(Point2f{ 165 + 9,115 }, Rectf{ float(9 * secondDigitFlowers),15,9,15 });
			

			//Draws Coins
			const int firstDigitCoins  = m_Coins / 10;
			const int secondDigitCoins = m_Coins % 10;

			if (firstDigitCoins > 0)
			{
				m_PauseScreenIcons->Draw(Point2f{75,15 }, Rectf{ float(9 * firstDigitCoins), 88 ,9,7 });
			}																							 
			m_PauseScreenIcons->Draw(Point2f{ 75 + 9,15 }, Rectf{ float(9 * secondDigitCoins),88,9,7 });

			//Draws Lives
			const int firstDigitLives =  m_Lives / 10;
			const int secondDigitLives = m_Lives % 10;

			if (firstDigitLives > 0)
			{
				m_PauseScreenIcons->Draw(Point2f{ 25,15 }, Rectf{ float(9 * firstDigitLives), 88 ,9,7 });
			}
			m_PauseScreenIcons->Draw(Point2f{ 25 + 9,15 }, Rectf{ float(9 * secondDigitLives),88,9,7 });

		}
		glPopMatrix();
	}


	if (m_CurrentState == States::DeathMenu)
	{
		//Draws the screen
		m_DeathScreen->Draw(Point2f{190,250 }, Rectf{ 15, 0 ,229,150 });

	glPushMatrix();
	{
		glScalef(2, 2, 1);
		//DrawsLives
		const int firstDigitLives = m_Lives / 10;
		const int secondDigitLives = m_Lives % 10;

		if (firstDigitLives > 0)
		{
			m_PauseScreenIcons->Draw(Point2f{ 150,15 }, Rectf{ float(9 * firstDigitLives),15 ,9,15 });
		}																						  
		m_PauseScreenIcons->Draw(Point2f{ 150 + 9,180 }, Rectf{ float(9 * secondDigitLives),15,9,15 });
	}
	glPopMatrix();
		//Draws the Pointer
		m_DeathScreen->Draw(Point2f{ float(m_PointerPosX), 250 }, Rectf{ 254, 93 ,16,25 });
	}

}

void StateManager::Update(int coins, int redCoins, int flowers, int stars,bool hasYoshiLost)
{
	m_Coins = coins;
	m_RedCoins = redCoins;
	m_Flowers = flowers;
	m_Stars = stars;

	if (m_CurrentState != States::DeathMenu)
	{
		if (hasYoshiLost == true)
		{
			m_Lives -= 1;
			m_CurrentState = States::DeathMenu;
		}
	}
	
	
}

void StateManager::SetPointerPosition(int pointerPosX)
{
	m_PointerPosX = pointerPosX;
}

int StateManager::GetPointerPositionX() const
{
	return m_PointerPosX;
}


