#pragma once

#include <stdint.h>
#include <stdbool.h>

// for the low-pass/high-pass filters in the SAMPLER screen
#define FILTERS_BASE_FREQ (PAULA_PAL_CLK / 214.0)

enum
{
	AUDIO_NO_OVERSAMPLING = 0,
	AUDIO_2X_OVERSAMPLING = 1
};

typedef struct audio_t
{
	volatile bool locked, isSampling;

	bool ledFilterEnabled, oversamplingFlag;
	
	uint32_t outputRate, audioBufferSize;
	int64_t tickSampleCounter64, samplesPerTick64;
	int64_t samplesPerTickTable[256-32]; // 32.32 fixed-point

	// for audio sampling
	bool rescanAudioDevicesSupported;

	// for audio/video syncing
	bool resetSyncTickTimeFlag;
	uint64_t tickLengthTable[224];
} audio_t;

void updateReplayerTimingMode(void);
void setSyncTickTimeLen(uint32_t timeLen, uint32_t timeLenFrac);
void resetAudioDithering(void);
void generateBpmTable(double dAudioFreq, bool vblankTimingFlag);
uint16_t get16BitPeak(int16_t *sampleData, uint32_t sampleLength);
uint32_t get32BitPeak(int32_t *sampleData, uint32_t sampleLength);
float getFloatPeak(float *fSampleData, uint32_t sampleLength);
double getDoublePeak(double *dSampleData, uint32_t sampleLength);
void normalize16BitTo8Bit(int16_t *sampleData, uint32_t sampleLength);
void normalize32BitTo8Bit(int32_t *sampleData, uint32_t sampleLength);
void normalizeFloatTo8Bit(float *fSampleData, uint32_t sampleLength);
void normalizeDoubleTo8Bit(double *dSampleData, uint32_t sampleLength);
void toggleAmigaPanMode(void);
void lockAudio(void);
void unlockAudio(void);
void audioSetStereoSeparation(uint8_t percentage);
void outputAudio(int16_t *target, int32_t numSamples);
bool setupAudio(void);
void audioClose(void);

extern audio_t audio; // pt2_audio.c
