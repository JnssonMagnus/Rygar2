// WWiseSoundMan.cpp : Defines the entry point for the application.
//
/*
AkConvolutionReverbFX.lib
AkFlangerFX.lib
AstoundsoundExpanderFX.lib
AkTremoloFX.lib
AkMemoryMgr.lib
AuroHeadphoneFX.lib
IOSONOProximityMixer.lib
AkMotionGenerator.lib
AkSineSource.lib
AkSoundSeedWind.lib
AkStereoDelayFX.lib
AkGuitarDistortionFX.lib
AkRumble.lib
AkSoundEngine.lib
AkSilenceSource.lib
AuroPannerMixer.lib
AkPeakLimiterFX.lib
iZTrashBoxModelerFX.lib
AkSoundSeedImpactFX.lib
AkRoomVerbFX.lib
iZTrashDelayFX.lib
McDSPLimiterFX.lib
McDSPFutzBoxFX.lib
AkParametricEQFX.lib
AstoundsoundFolddownFX.lib
AkToneSource.lib
AkMatrixReverbFX.lib
AkCompressorFX.lib
AkAudioInputSource.lib
AkMusicEngine.lib
AkSoundSeedWoosh.lib
CrankcaseAudioREVModelPlayerFX.lib
iZTrashMultibandDistortionFX.lib
iZHybridReverbFX.lib
AkPitchShifterFX.lib
iZTrashDynamicsFX.lib
iZTrashDistortionFX.lib
AstoundsoundRTIFX.lib
AkDelayFX.lib
AkGainFX.lib
AkVorbisDecoder.lib
AkMeterFX.lib
AstoundsoundShared.lib
iZTrashFiltersFX.lib
AkSynthOne.lib
AkMP3Source.lib
AkStreamMgr.lib
AkHarmonizerFX.lib
AkTimeStretchFX.lib
AkExpanderFX.lib
dxguid.lib
XInput.lib
msacm32.lib
CommunicationCentral.lib
ws2_32.lib
*/
#include "stdafx.h"
#include "wwiseSoundManager.h"

//
//
//int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
//                     _In_opt_ HINSTANCE hPrevInstance,
//                     _In_ LPTSTR    lpCmdLine,
//                     _In_ int       nCmdShow)
//{
//	SoundManager::WWiseSoundManager soundManager;
//	soundManager.Init();
//	soundManager.InitBank("sound/Init.bnk");
//	soundManager.LoadBank("sound/TestBank.bnk");
//	soundManager.PlayEvent("BOOM");
//	
//	while (true)
//	{
//		int nr = rand() % 999;
//		if (nr == 42)
//		{
//			nr = rand() % 9999;
//			if (nr == 12)
//			{
//				soundManager.PlayEvent("RANDOM");
//			}
//		}
//		soundManager.Update();
//	}
//	soundManager.Unload();
//	return 0;
//}
