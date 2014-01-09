#pragma once
#include <iostream>

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

class MusikSampler
{
private:
	sf::Music m_Music;	// nur OGG
	vector<sf::Sound*> m_vSound; // wird als Vector benötigt, um mehrere gleichzeitig zu starten	und anschließend zu deleten
	vector<sf::SoundBuffer> m_vBuffer; // nur WAV

	string m_Path_full_song;
	string m_Path_sounds;
	vector<string> m_vFull_songs;
	vector<string> m_vShort_sounds;
public:
	MusikSampler(void); 
	~MusikSampler(void);

    bool load_music(int index);		// im hintergrund ausgeführt
	sf::SoundBuffer load_sound(int index); // schon am anfang ausgeführt
    bool play_music(int index);
	bool play_sound(int index);

    void pause();
    void stop();
    int get_duration();
    void set_loop(bool loop);
    void set_pitch(float pitch);
    void set_volume(float volume);

};

