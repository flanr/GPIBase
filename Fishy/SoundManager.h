// SoundManager.h
#pragma once

struct SoundsStruct
{
	string path;
	sf::Sound* soundData;
	sf::SoundBuffer* buffer;
};
struct MusicStruct
{
	string path;
	sf::Music* soundHandle;
};


class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	bool Initialize(string path);
	void PlaySound(string path);
	void PlayMusic(string path);
	void StopSound();
	void SetMusicVolume(int value);
	void SetSoundVolume(int value);
	int GetMusicVolume();
	int GetSoundVolume();
	void PauseSound();
	vector<SoundsStruct> ReturnSound();
	void MuteSound();
	void MuteMusic();

private:
	vector<SoundsStruct> m_SoundBank;
	vector<MusicStruct> m_MusicBank;
	int m_SoundVolume;
	int m_MusicVolume;
	string m_directory;
	void AddSound(string path);
	void AddMusic(string path);
	int OldVolMusic, OldVolSound;
	bool b_MuteM, b_MuteS;

};

