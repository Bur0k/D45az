#include "MusikSampler.h"


MusikSampler::MusikSampler(void)
{
	this->loaded_music = false;

	this->full_songs.push_back("test.ogg");
}

bool MusikSampler::load_music(int index)
{
	//if(this->full_songs[index].length == 0) // liste hat hier kein element
		//return 0;

	if(!this->music.openFromFile(this->full_songs[index])) // kein song an speicherstelle hinterlegt , asonsten song jetzt drin
		return 0;

	this->loaded_music = 1;
	return 1;
}

bool MusikSampler::play_music()
{
	if (!this->loaded_music)
    {
        return 0;
    }

   this-> music.play();
   return 1;
}



/*
void MusikSampler::pause()
{
    if (!loaded)
    {
        return;
    }

    samples.Pause();
}

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