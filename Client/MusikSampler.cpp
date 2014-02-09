#include "MusikSampler.h"

bool MusikSampler::instanceFlag = false;

MusikSampler* MusikSampler::single = NULL;
MusikSampler* MusikSampler::getInstance()
{
    if(! instanceFlag)
    {
        single = new MusikSampler();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

MusikSampler::MusikSampler(void)
{
	m_SongPath = "Data/Songs/";
	m_vSongFiles.push_back("login.ogg");
	m_vSongFiles.push_back("menu2.ogg");
	m_vSongFiles.push_back("menu.ogg");
	m_vSongFiles.push_back("1_Steps.ogg"); //songnamen manuell einfügen
	m_vSongFiles.push_back("2_Fallen.ogg");
	m_vSongFiles.push_back("3_Archangel.ogg");
	m_vSongFiles.push_back("4_Requium.ogg");

	m_Songnumber = 3; // vorinitialisieren, dann 1. track gespielt

	m_Soundpath = "Data/Sounds/";
	m_vSoundFiles.push_back("chat_open.wav");
	m_vSoundFiles.push_back("chat_close.wav");
	m_vSoundFiles.push_back("commit.wav");
	m_vSoundFiles.push_back("turn.wav");
	m_vSoundFiles.push_back("lose.wav");
	m_vSoundFiles.push_back("win.wav");
	// Sounds gleich in Buffer laden, um dann Buffer schnell an angeforderten sound zu hängen
	for(unsigned int i = 0; i < m_vSoundFiles.size(); i++)
		m_vBuffer.push_back(preload_soundbuffer(i));


	// Lautstärke am Anfang 100%
	m_BgVolume = 80.0;
	m_SoVolume = 100.0;
}

MusikSampler::~MusikSampler(void)
{
		// Adresslisten freigeben
	for (unsigned int i = 0; i < m_vSongFiles.size(); i++)
		m_vSongFiles[i].clear();
	for(unsigned int i = 0; i < m_vSoundFiles.size(); i++)
		m_vSoundFiles[i].clear();

		// Bufferliste freigeben
	for (unsigned int i = 0; i < m_vBuffer.size(); i++)
		m_vBuffer.clear();

	for (unsigned int i = 0; i < m_vSound.size() ; i++)	// noch-abspielende Sounds löschen
	{
		try
		{
				delete m_vSound[i];
		}
		catch(int e)
		{
			cout << "FehlerKarre " << e << '\n';
		}
	}

	instanceFlag = false;
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

	m_Songnumber = index;
	m_Music.setVolume(m_BgVolume);
	m_Music.play();
	return 1;
}

bool MusikSampler::play_sound(int index)
{
	sf::Sound* tmp_sound = new sf::Sound();
	
	if (static_cast<unsigned int>(index) >= m_vBuffer.size() ) // sicher gehen, dass index innerhalb gültigen bereichs
		return 0;

	tmp_sound->setBuffer(m_vBuffer[index]); // sound abholen

	tmp_sound->setVolume(m_SoVolume);
	tmp_sound->play();	

	for (unsigned int i = 0; i < m_vSound.size() ; i++)
		if(m_vSound[i]->getStatus() == 0) // enum 0 == stopped
		{
			//cout << "vector size vorher:" << m_vSound.size() << endl;
			delete m_vSound[i];					// Abgespielte Sounds aufräumen
			m_vSound.erase(m_vSound.begin()+i);
			//cout << "löschung" << endl << "vector size nachher:" << m_vSound.size() << endl;
		}

	m_vSound.push_back(tmp_sound); // Referenz speichern, um später zu löschen


   return 1;
}

void MusikSampler::next_song()
{
	if(static_cast<unsigned int>(m_Songnumber) >= m_vSongFiles.size() - 1 || static_cast<unsigned int>(m_Songnumber) < menumusiken) // wenn letzter song gespielt wurde zurück
		m_Songnumber = menumusiken; // dann dahinter gestellt
	else 
		m_Songnumber ++;

	play_music(m_Songnumber);
}

void MusikSampler::play_song_again()
{
	if(m_Music.getStatus() != 2) // nur Song wechseln, wenn alter fertig
		play_music(m_Songnumber);
}

void MusikSampler::set_volume(int type, float volume)
{
	switch(type)
	{
		case sound_noise: m_SoVolume = volume; // für neue ändern
			for (unsigned int i = 0; i < m_vSound.size() ; i++) // alle aktiven ändern
			{
				m_vSound[i]->setVolume(volume);
			}	break;
		case song_noise:  m_BgVolume = volume; 
			m_Music.setVolume(volume); break;
		case generel_noise: set_volume(sound_noise,volume); 
							set_volume(song_noise,volume); break;
	}
}

float MusikSampler::get_BGV()
{
	return m_BgVolume;
}
	
float MusikSampler::get_SOV()
{
	return m_SoVolume;
}
