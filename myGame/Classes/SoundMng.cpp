#include "SoundMng.h"
#include "CricketJni.h"

std::unique_ptr<SoundMng>SoundMng::s_Instance(new SoundMng);

SoundMng::SoundMng()
{
}

SoundMng::~SoundMng()
{

}

void SoundMng::Init(void)
{
#ifdef CK_PLATFORM_ANDROID

#else
	CkConfig config;
	CkInit(&config);
#endif
	
}

bool SoundMng::AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type)
{
#ifdef CK_PLATFORM_ANDROID
	_bank = CkBank::newBank(bank_p.c_str());
#else
	_bank = CkBank::newBank(("Resources/" + bank_p).c_str(), kCkPathType_ExeDir);
#endif // CK_PLATFORM_ANDROID
	if (_bank == nullptr)
	{
		return false;
	}
	if (_sound.find(soundName) == _sound.end())
	{
		_sound[soundName] = CkSound::newBankSound(_bank, soundName.c_str());
		if (type == SOUND_TYPE::BGM)
		{
			_sound[soundName]->setLoop(0, _sound[soundName]->getLength());
			_sound[soundName]->setLoopCount(-1);
		}
	}
	return true;
}

void SoundMng::Update(void)
{
	CkUpdate();
}

void SoundMng::PlayBySoundName(std::string soundName)
{
	if (_sound.find(soundName) != _sound.end())
	{
		_sound[soundName]->play();
	}
}

void SoundMng::ckEnd(void)
{
	for (auto sound : _sound)
	{
		sound.second->destroy();
	}
	_bank->destroy();

	CkShutdown();
}

void SoundMng::SetPauseAll(bool pauseF)
{
	for (auto sound : _sound)
	{
		sound.second->setPaused(pauseF);
	}
}
