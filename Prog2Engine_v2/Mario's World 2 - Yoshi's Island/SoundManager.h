#pragma once
#include "SoundEffect.h"
#include "SoundStream.h"

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	SoundManager(const SoundManager& rhs) = delete;
	SoundManager& operator=(const SoundManager& rhs) = delete;
	SoundManager(SoundManager&& rhs) = delete;

	enum class YoshiSFX
	{
		Null,
		JumpSFX,
		TongueSFX
	};

	enum class ObjectSFX
	{
		Null,
		CoinSFX
	};

	enum class EnemySFX
	{
		Null,
		PiranhaPlantSFX
	};

	enum class LvlMusic
	{
		Null,
		Level1
	};

	void PlaySFX(YoshiSFX yoshiSfx);
	void PlaySFX(ObjectSFX objectSfx);
	void PlaySFX(EnemySFX enemySfx);
	void PlayBGMusic(LvlMusic levelNumber);
	void PauseBGMusic() const;
	void ResumeBGMusic() const;

private:
	YoshiSFX m_YoshiSFX{YoshiSFX::Null};
	ObjectSFX m_ObjectSFX{ ObjectSFX::Null };
	EnemySFX m_EnemySFX{ EnemySFX::Null };
	LvlMusic m_LvlMusic{ LvlMusic::Null };

	SoundEffect m_YoshiJumpSFX{"YISFX/Jump.wav"};
	SoundEffect m_YoshiTongueSFX{"YISFX/Tongue.wav"};
	SoundEffect m_PiranhaPlantSFX{"YISFX/Piranha.wav"};
	SoundStream m_BGMusicLvl1{"YISFX/FlowerGarden.wav"};
};

