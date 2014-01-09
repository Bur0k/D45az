#include "MusikSampler.h"


MusikSampler::MusikSampler(void)
{
	this->loaded_music = false;

	this->full_songs.push_back("test.ogg");
	this->path_full_song = "Data/Songs/";
}

bool MusikSampler::load_music(int index)
{
	//if(this->full_songs[index].length == 0) // liste hat hier kein element
		//return 0;
	string full_path = this->path_full_song + this->full_songs[index];

	if(!this->music.openFromFile(full_path)) // kein song an speicherstelle hinterlegt , asonsten song jetzt drin
	{
		cout<<"kein lied da gefunden" << endl;
		return 0;
	}

	this->loaded_music = 1;
	return 1;
}

bool MusikSampler::play_music()
{
	if (!this->loaded_music) // keine musik geladen
    {
        return 0;
    }

   this-> music.play();
   return 1;
}


void MusikSampler::pause()
{
    this->music.pause();
}

/*
void MusikSampler::stop()
{
    if (!loaded)
    {
        return;
    }

    samples.Stop();
}

int MusikSampler::get_duration()
{
    if (!loaded)
    {
        return -1;
    }

    return samples.GetDuration();
}

void MusikSampler::set_loop(bool loop)
{
    if (!loaded)
    {
        return;
    }

    samples.SetLoop(loop);
}


void MusikSampler::set_pitch(float pitch)
{
    if (!loaded)
    {
        return;
    }

    samples.SetPitch(pitch);
}

void MusikSampler::set_volume(float volume)
{
    if (!loaded)
    {
        return;
    }

    if (volume >= 0.0f && volume <= 100.0f)
    {
        samples.SetVolume(volume);
    }
}
*/