#include "pch.h"
#include "SoundManager.h"

#include <iostream>

SoundManager::SoundManager()
= default;

SoundManager::~SoundManager()
= default;

void SoundManager::PlaySFX(YoshiSFX yoshiSfx)
{
	m_YoshiSFX = yoshiSfx;

	if (m_YoshiSFX == YoshiSFX::JumpSFX)
	{
		m_YoshiJumpSFX.Play(0);
	}

	else if (m_YoshiSFX == YoshiSFX::TongueSFX)
	{
		m_YoshiTongueSFX.Play(0);
	}
}

void SoundManager::PlaySFX(ObjectSFX objectSfx)
{
}

void SoundManager::PlaySFX(EnemySFX enemySfx)
{
	m_EnemySFX = enemySfx;

	if (m_EnemySFX == EnemySFX::PiranhaPlantSFX)
	{
		m_PiranhaPlantSFX.Play(0);
	}
}

void SoundManager::PlayBGMusic(LvlMusic levelNumber)
{
	m_LvlMusic = levelNumber;

	if (m_LvlMusic == LvlMusic::Level1)
	{
		m_BGMusicLvl1.Play(true);
		std::cout << m_BGMusicLvl1.IsLoaded();
	}
}

void SoundManager::PauseBGMusic() const
{
	m_BGMusicLvl1.Pause();
}

void SoundManager::ResumeBGMusic() const
{
	m_BGMusicLvl1.Resume();
}
