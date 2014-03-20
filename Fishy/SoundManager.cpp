// SoundManager.cpp
#include "stdafx.h"
#include "SoundManager.h"



SoundManager::SoundManager()
{
	int m_SoundVolume = 100;
	int m_MusicVolume = 100;
	m_SoundBank.reserve(2);
	m_MusicBank.reserve(2);
	b_MuteM = false;
	b_MuteS = false;
}

SoundManager::~SoundManager()
{
}	


void SoundManager::PlaySound(string path)
{
	for (SoundsStruct sound : m_SoundBank)
	{
		if (sound.path == path)
		{
			sound.soundData->play();
			sound.soundData->setVolume(m_SoundVolume);
			//			cout << "Sound was found, playing : " << path << endl;

			return;
		}
	}
	//cout << "Sound not found, adding sound : " << path << endl;
	AddSound(path);
	PlaySound(path);
}

void SoundManager::PlayMusic(string path)
{

	if(m_MusicBank.size() > 0)
	{
		for (MusicStruct music : m_MusicBank)
		{
			if (music.path == path)
			{

				music.soundHandle->play();
				music.soundHandle->setVolume(m_MusicVolume);
				music.soundHandle->setLoop(true);
				//cout << "Music was found, playing : " << path << endl;
				return;
			}


		}
	}


	cout << "[" << __FILE__ << ":" << __LINE__ << "] Music not found, adding sound : " << path << endl;
	AddMusic(path);
	PlayMusic(path);
}

vector<SoundsStruct> SoundManager::ReturnSound()
{
	return m_SoundBank;
}



void SoundManager::StopSound()
{

}

bool SoundManager::Initialize(string directory)
{
	m_directory = directory;
	AddSound("Upgrade.wav");
	AddSound("sound_ToggleLight.wav");
	AddSound("FishyDeathChoir.ogg");
	AddSound("chew_sound2.wav");
	AddSound("dashSound1.wav");
	AddSound("dashSound2.wav");
	AddSound("HungerAlert.wav");

	return true;
}

void SoundManager::SetMusicVolume(int value)
{
	m_SoundVolume = value;
	for (MusicStruct music : m_MusicBank)
	{
		music.soundHandle->setVolume(value);
	}
}

void SoundManager::SetSoundVolume(int value)
{
	m_MusicVolume = value;
	m_SoundVolume = value;
	for (SoundsStruct sound : m_SoundBank)
	{
		sound.soundData->setVolume(value);
	}
}


int SoundManager::GetMusicVolume()
{
	return m_MusicVolume;
}

int SoundManager::GetSoundVolume()
{
	return m_SoundVolume;
}


void SoundManager::PauseSound()
{

}

void SoundManager::AddSound(string path )
{

	SoundsStruct soundstruct;
	sf::Sound* thesound = new sf::Sound;
	sf::SoundBuffer* thebuffer = new sf::SoundBuffer;

	thebuffer->loadFromFile(m_directory + path);

	thesound->setBuffer(*thebuffer);

	soundstruct.path = path;
	soundstruct.soundData = thesound;
	soundstruct.buffer = thebuffer;

	m_SoundBank.push_back(soundstruct);

}

void SoundManager::AddMusic(string path)
{

	MusicStruct musicstruct;
	sf::Music* themusic = new sf::Music;

	themusic->openFromFile(m_directory + path);
	musicstruct.path = path;
	musicstruct.soundHandle = themusic;

	m_MusicBank.push_back(musicstruct);

}
void SoundManager::MuteMusic()
{
	if (b_MuteM)
	{
		SetMusicVolume(OldVolMusic);

		b_MuteM = false;
	}else
	{
		OldVolMusic = GetMusicVolume();

		SetMusicVolume(0);
		b_MuteM = true;
	}



}
void SoundManager::MuteSound()
{
	if (b_MuteS)
	{



	}else
	{

	}
	SetSoundVolume(0);
}

void SoundManager::StopMusic()
{
	for(MusicStruct music : m_MusicBank)
	{
		music.soundHandle->stop();
	}

}

