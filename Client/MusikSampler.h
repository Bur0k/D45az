#pragma once
#include <iostream>

#include <vector>
#include <SFML/Audio.hpp>

#define sound_noise 0  
#define song_noise  1 
#define generel_noise 2 

#define CHAT_OPEN 0
#define CHAT_CLOSE 1
#define COMMIT_SOUND 2


#define login 0
#define menu 1
#define test 2
#define menumusiken 3


using namespace std;

class MusikSampler
{
private:
	//SINGLETON PATTERN
	static bool instanceFlag;
    static MusikSampler *single;

	// Member
	sf::Music m_Music;	// OGG - immer nur 1 Song geladen
	int m_Songnumber;

	vector<sf::Sound*> m_vSound; // wird als Vector benötigt, um mehrere gleichzeitig zu starten	und anschließend zu deleten
	vector<sf::SoundBuffer> m_vBuffer; // nur WAV

	string m_SongPath;
	string m_Soundpath;
	vector<string> m_vSongFiles;
	vector<string> m_vSoundFiles;

	// Lautstärkeeinstellungen
	float m_BgVolume; //backgound, also songs
	float m_SoVolume; // so = sounds, also geräusche

public:
	//SINGLETONM PATTERN
	static MusikSampler* getInstance();

	//ctor & dtor
	MusikSampler(void); 
	~MusikSampler(void);

	// lade und abspielfunktionen
    bool load_music(int index);		// im hintergrund ausgeführt
	sf::SoundBuffer preload_soundbuffer(int index); // schon am anfang ausgeführt
    bool play_music(int index);
	bool play_sound(int index);
	void next_song();
	void play_song_again();

	//einstellungen
	void set_volume(int type, float volume);

	// noch nicht verwendet
    void pause();
    void stop();
    int get_duration();
    void set_loop(bool loop);
    void set_pitch(float pitch);
};