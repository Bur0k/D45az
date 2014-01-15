#pragma once
#include <iostream>

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

class MusikSampler
{
private:
	sf::Music m_Music;	// OGG - immer nur 1 Song geladen
	int m_Songnumber;

	vector<sf::Sound*> m_vSound; // wird als Vector benötigt, um mehrere gleichzeitig zu starten	und anschließend zu deleten
	vector<sf::SoundBuffer> m_vBuffer; // nur WAV

	string m_SongPath;
	string m_Soundpath;
	vector<string> m_vSongFiles;
	vector<string> m_vSoundFiles;
public:
	//ctor & dtor
	MusikSampler(void); 
	~MusikSampler(void);

	// lade und abspielfunktionen
    bool load_music(int index);		// im hintergrund ausgeführt
	sf::SoundBuffer preload_soundbuffer(int index); // schon am anfang ausgeführt
    bool play_music(int index);
	bool play_sound(int index);
	void next_song();


	// noch nicht verwendet
    void pause();
    void stop();
    int get_duration();
    void set_loop(bool loop);
    void set_pitch(float pitch);
    void set_volume(float volume);

};

