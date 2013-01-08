#pragma once

namespace nMech
{
	namespace nJC_SOUND
	{

		class CSoundSystemCommon : public ISoundSystem
		{
		public:

			CSoundSystemCommon();
			virtual ~CSoundSystemCommon();
			bool DebuggingSound();

			//enable playback of sounds
			nMech::nCONSOLE::ICVar *m_pCVARSoundEnable;

			nMech::nCONSOLE::ICVar *m_pCVARDummySound;

			//max sound distance
			nMech::nCONSOLE::ICVar *m_pCVarMaxSoundDist;

			nMech::nCONSOLE::ICVar	*m_pCVarDopplerEnable;
			nMech::nCONSOLE::ICVar	*m_pCVarDopplerValue;

			nMech::nCONSOLE::ICVar	*m_pCVarSFXVolume;
			nMech::nCONSOLE::ICVar	*m_pCVarMusicVolume;
			nMech::nCONSOLE::ICVar	*m_pCVarSampleRate;
			nMech::nCONSOLE::ICVar *m_pCVarSpeakerConfig;
			nMech::nCONSOLE::ICVar	*m_pCVarEnableSoundFX;
			nMech::nCONSOLE::ICVar	*m_pCVarDebugSound;
			nMech::nCONSOLE::ICVar *m_pCVarSoundInfo;
			nMech::nCONSOLE::ICVar *m_pCVarInactiveSoundIterationTimeout;
			nMech::nCONSOLE::ICVar *m_pCVarMinHWChannels;
			nMech::nCONSOLE::ICVar *m_pCVarMaxHWChannels;
			nMech::nCONSOLE::ICVar *m_pCVarVisAreaProp;
			nMech::nCONSOLE::ICVar *m_pCVarMaxSoundSpots;
			nMech::nCONSOLE::ICVar *m_pCVarMinRepeatSoundTimeout;
			nMech::nCONSOLE::ICVar *m_pCVarCompatibleMode;
			nMech::nCONSOLE::ICVar *m_pCVarCapsCheck;
		};

	} //nJC_SOUND
}//nMech

