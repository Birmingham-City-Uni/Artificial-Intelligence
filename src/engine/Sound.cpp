#include "Sound.h"
#include "Globals.h"

namespace sound {

	namespace {
		std::string g_SoundDirectory = "Not yet initialized!\n";
		std::string g_MusicDirectory = "Not yet initialized!\n";
	}

	bool InitializeSound()
	{
		g_SoundDirectory = globals::GetAssetDirectory();
		g_SoundDirectory += "sfx/";

		g_MusicDirectory = globals::GetAssetDirectory();
		g_MusicDirectory += "music/";

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			std::cout << "SDL_Mix could not initialize! SDL_Mix error: " << Mix_GetError() << "\n";
			return false;
		}
#ifdef LOGGING
		std::cout << "Sound Initialized!\n";
#endif // LOGGING
		return true;
	}

	void UninitalizeSound()
	{
		Mix_Quit();
	}

	Mix_Chunk* LoadSfx(const char* filename)
	{
#ifdef LOGGING
		std::cout << "Loading sound: " << filename << "\n";
#endif // LOGGING
		try {
			Mix_Chunk* result = Mix_LoadWAV((g_SoundDirectory + std::string(filename)).c_str());
			if (result == nullptr) throw SoundError();
			return result;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << "\n";
			std::cout << "\t" << e.what() << "\t" << Mix_GetError() << "\n";
			return nullptr;
		}
	}

	Mix_Music* LoadMusic(const char* filename) {
#ifdef LOGGING
		std::cout << "Loading music: " << filename << "\n";
#endif // LOGGING
		try {
			Mix_Music* result = Mix_LoadMUS((g_MusicDirectory + std::string(filename)).c_str());
			if (result == nullptr) throw SoundError();
			return result;
		}
		catch (std::exception& e) {
			std::cout << "An exception was thrown." << std::endl;
			std::cout << "\t" << e.what() << "\t" << Mix_GetError() << "\n";
			return nullptr;
		}
	}
} // namespace Sound

SoundEffect::SoundEffect()
{
	m_Sound = nullptr;
}

SoundEffect::~SoundEffect()
{
	if(m_Sound) Mix_FreeChunk(m_Sound);
}

void SoundEffect::Initialize(const char* filename)
{
	m_Sound = sound::LoadSfx(filename);
}

void SoundEffect::PlaySound()
{
	Mix_PlayChannel(-1, m_Sound, 0);
}

Music::Music()
{
	m_Music = nullptr;
}

Music::~Music()
{
	if(m_Music) Mix_FreeMusic(m_Music);
}

void Music::Initialize(const char* filename)
{
	m_Music = sound::LoadMusic(filename);
}

void Music::PlayMusic()
{
	if (Mix_PlayingMusic() == 0) {
		Mix_PlayMusic(m_Music, -1);
	}
}