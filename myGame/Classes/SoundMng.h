#pragma once
#include <cocos2d.h>
#include <ck/ck.h>
#include <ck/config.h>
#include <ck/bank.h>
#include <ck/sound.h>

#define lpSoundMng SoundMng::GetInstance()

enum SOUND_TYPE
{
	SE,
	BGM
};

class SoundMng
{
public:
	static SoundMng & GetInstance(void)
	{
		return *s_Instance;
	}
	~SoundMng();
	void Init(void);															// CkInit()
	bool AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type);	// »³İÄŞ’Ç‰Á
	void Update(void);															// CkUpDate()
	void PlayBySoundName(std::string soundName);								// “o˜^‚µ‚½»³İÄŞ‚ğ–¼‘O‚©‚çÄ¶‚·‚é
	void ckEnd(void);															// »³İÄŞI—¹—ƒQ[ƒ€I—¹
	void SetPauseAll(bool pauseF);												// »³İÄŞ‚ğ‘S‚Äˆê’â~

private:
	SoundMng();

	CkBank* _bank;
	std::map<std::string,CkSound*>_sound;

	static std::unique_ptr<SoundMng> s_Instance;
};

