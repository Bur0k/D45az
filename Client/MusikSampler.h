#pragma once
#include <iostream>

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

class MusikSampler
{
private:
	sf::Music m_Music;	// nur OGG
	sf::Sound m_Sound;	// nur WAV
	bool m_Loaded_music;
	bool m_Loaded_sound;

	string m_Path_full_song;
	string m_Path_sounds;
	vector<string> m_vFull_songs;
	vector<string> m_vShort_sounds;
public:
	MusikSampler(void); 
	~MusikSampler(void);

    bool load_music(int index);
    bool play_music();

    void pause();
    void stop();
    int get_duration();
    void set_loop(bool loop);
    void set_pitch(float pitch);
    void set_volume(float volume);

};

