#include "MusikSampler.h"


MusikSampler::MusikSampler(void)
{
	this->m_Loaded_music = false;

	this->m_vFull_songs.push_back("test.ogg");
	this->m_Path_full_song = "Data/Songs/";
}

MusikSampler::~MusikSampler(void)
{
	m_vFull_songs.clear();
	m_vShort_sounds.clear();
}
bool MusikSampler::load_music(int index)
{
	//if(this->full_songs[index].length == 0) // liste hat hier kein element
		//return 0;
	string full_path = m_Path_full_song + m_vFull_songs[index];

	if(!m_Music.openFromFile(full_path)) // kein song an speicherstelle hinterlegt , asonsten song jetzt drin
	{
		cout<<"kein lied da gefunden" << endl;
		return 0;
	}

	m_Loaded_music = 1;
	return 1;
}

bool MusikSampler::play_music()
{
	if (!m_Loaded_music) // keine musik geladen
    {
        return 0;
    }

   m_Music.play();
   return 1;
}


void MusikSampler::pause()
{
    m_Music.pause();
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