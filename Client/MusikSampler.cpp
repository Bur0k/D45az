#include "MusikSampler.h"


MusikSampler::MusikSampler(void)
{
	m_Path_full_song = "Data/Songs/";
	m_vFull_songs.push_back("test.ogg");

	m_Path_sounds = "Data/Sounds/";
	m_vShort_sounds.push_back("sound1.wav");
	m_vShort_sounds.push_back("sound2.wav");
	// Sounds gleich in Buffer laden, um dann Buffer schnell an angeforderten sound zu hängen
	for(int i = 0; i < m_vShort_sounds.size(); i++)
		m_vBuffer.push_back(load_sound(i));
}

MusikSampler::~MusikSampler(void)
{
		// Adresslisten freigeben
	m_vFull_songs.clear();

	m_vShort_sounds.clear();

		// Bufferliste freigeben
	m_vBuffer.clear(); 


	for (int i = 0; i < m_vSound.size() ; i++)	// noch-abspielende Sounds löschen
		delete m_vSound[i];
}

bool MusikSampler::load_music(int index)
{
	//if(m_vFull_songs[index].length == 0) // liste hat hier kein element
		//return 0;
	string full_path = m_Path_full_song + m_vFull_songs[index];

	if(!m_Music.openFromFile(full_path)) // kein song an speicherstelle hinterlegt , asonsten song jetzt drin
	{
		cout<<"kein lied gefunden: "<< full_path << endl;
		return 0;
	}

	return 1;
}

sf::SoundBuffer MusikSampler::load_sound(int index)
{
	//if(m_vShort_sounds[index].length == 0) // liste hat hier kein element
		//return 0;

	sf::SoundBuffer tmp_buffer;

	string full_path = m_Path_sounds + m_vShort_sounds[index];

	if(!tmp_buffer.loadFromFile(full_path)) // kein sound an speicherstelle hinterlegt , asonsten song jetzt drin
	{
		cout<<"keinen sound gefunden:" << full_path << endl;
		return tmp_buffer;
	}

	return tmp_buffer;
}

bool MusikSampler::play_music(int index)
{

	if (!load_music(index)) // keine musik geladen
    {
        return 0;
    }

   m_Music.play();
   return 1;
}

bool MusikSampler::play_sound(int index)
{
	sf::Sound* tmp_sound = new sf::Sound();

	tmp_sound->setBuffer(m_vBuffer[index]);

	tmp_sound->play();	

	for (int i = 0; i < m_vSound.size() ; i++)
		if(m_vSound[i]->getStatus() == 0) // enum 0 == stopped
			m_vSound[i] = tmp_sound; // neuen sound dahin, um speicher zu sparen
		else
			m_vSound.push_back(tmp_sound); // neu erzeugten sound normal anreihen

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