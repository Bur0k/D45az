#include "MusikSampler.h"


MusikSampler::MusikSampler(void)
{
	m_SongPath = "Data/Songs/";
	m_vSongFiles.push_back("1_example.ogg"); //songnamen manuell einf�gen
	m_vSongFiles.push_back("2_bullet.ogg");

	m_Songnumber = 0; // vorinitialisieren, dann 1. track gespielt

	m_Soundpath = "Data/Sounds/";
	m_vSoundFiles.push_back("sound1.wav");
	m_vSoundFiles.push_back("sound2.wav");
	// Sounds gleich in Buffer laden, um dann Buffer schnell an angeforderten sound zu h�ngen
	for(unsigned int i = 0; i < m_vSoundFiles.size(); i++)
		m_vBuffer.push_back(preload_soundbuffer(i));
}

MusikSampler::~MusikSampler(void)
{
		// Adresslisten freigeben
	for ( int i = 0; i < m_vSongFiles.size(); i++)
		m_vSongFiles[i].clear();
	for( int i = 0; i < m_vSoundFiles.size(); i++)
		m_vSoundFiles[i].clear();

		// Bufferliste freigeben
	for (int i = 0; i < m_vBuffer.size(); i++)
		m_vBuffer.clear();

	for (unsigned int i = 0; i < m_vSound.size() ; i++)	// noch-abspielende Sounds l�schen
	{
		try
		{
				delete m_vSound[i];
		}
		catch(int e)
		{
		}
	}
}

bool MusikSampler::load_music(int index)
{
	if(m_vSongFiles.size() == 0) // liste leer-> fehler im konstruktor
	{
		cout<<"Fehler, Code 17"<<  endl;
		return 0;
	}
	string full_path = m_SongPath + m_vSongFiles[index];

	if(!m_Music.openFromFile(full_path)) // kein song an speicherstelle hinterlegt , asonsten song jetzt drin
	{
		cout<<"kein lied gefunden: "<< full_path << endl;
		return 0;
	}

	return 1;
}

sf::SoundBuffer MusikSampler::preload_soundbuffer(int index)
{
	sf::SoundBuffer tmp_buffer;

	if(m_vSoundFiles.size() == 0)	// liste leer-> fehler im konstruktor
	{
		cout<<"Fehler, Code 18"<<  endl;
		return tmp_buffer;
	}


	string full_path = m_Soundpath + m_vSoundFiles[index];

	if(!tmp_buffer.loadFromFile(full_path)) // kein sound an speicherstelle hinterlegt , ansonsten song jetzt drin
	{
		cout<<"Keinen sound gefunden:" << full_path << endl;
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
	
	tmp_sound->setBuffer(m_vBuffer[index]); // sound abholen

	tmp_sound->play();	

	for (int i = 0; i < m_vSound.size() ; i++)
		if(m_vSound[i]->getStatus() == 0) // enum 0 == stopped
		{
			//cout << "vector size vorher:" << m_vSound.size() << endl;
			delete m_vSound[i];					// Abgespielte Sounds aufr�umen
			m_vSound.erase(m_vSound.begin()+i);
			//cout << "l�schung" << endl << "vector size nachher:" << m_vSound.size() << endl;
		}

	m_vSound.push_back(tmp_sound); // Referenz speichern, um sp�ter zu l�schen


   return 1;
}

void MusikSampler::pause()
{
    m_Music.pause();
}

void MusikSampler::next_song()
{
	/*
	if(m_Music.getStatus() == 0) // nur Song wechseln, wenn alter fertig
		return;
	*/

	if(m_Songnumber >= m_vSongFiles.size() ) // wenn letzter song gespielt wurde zur�ck
		m_Songnumber = 1;
	else 
		m_Songnumber ++;

	load_music(m_Songnumber-1);

	m_Music.play();
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