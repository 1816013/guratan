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
	bool AddSound(std::string bank_p, std::string soundName, SOUND_TYPE type);	// ｻｳﾝﾄﾞ追加
	void Update(void);															// CkUpDate()
	void PlayBySoundName(std::string soundName);								// 登録したｻｳﾝﾄﾞを名前から再生する
	void StopBySoundName(std::string soundName);								// 登録したｻｳﾝﾄﾞを名前から停止する
	void StopAllSound();														// 登録したｻｳﾝﾄﾞをすべて停止する
	void SetVolumeBySoundName(std::string soundName, float volume);				// 登録したｻｳﾝﾄﾞのボリューム変更
	void ckEnd(void);															// ｻｳﾝﾄﾞ終了＠ゲーム終了時
	void SetPauseAll(bool pauseF);												// ｻｳﾝﾄﾞを全て一時停止

private:
	SoundMng();

	CkBank* _bank;
	std::map<std::string,CkSound*>_sound;

	static std::unique_ptr<SoundMng> s_Instance;
};

