#pragma once
#include <iostream>

#include <vector>
#include <SFML/Audio.hpp>

using namespace std;

class MusikSampler
{
private:
	sf::Music music;	// nur OGG
	sf::Sound sound;	// nur WAV
	bool loaded_music;
	bool loaded_sound;

	string path_full_song;
	string path_sounds;
	vector<string> full_songs;
	vector<string> short_sounds;
public:
	MusikSampler(void); // loaded = 0

    bool load_music(int index);
    bool play_music();

    void pause();
    void stop();
    int get_duration();
    void set_loop(bool loop);
    void set_pitch(float pitch);
    void set_volume(float volume);

};

