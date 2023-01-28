#ifndef AUDIO_H
#define AUDIO_H

//Smallest chunk of audio data
typedef struct {
  int Tone;
  int Duration;
}SoundByte;

//Comple sound sample
typedef struct {
    int SampleCount;
    SoundByte* Data;
}SoundSample;

//All available sounds
SoundByte PauseSound[4] = {{600, 100}, {800, 100}, {600, 100}, {800, 100} };
SoundByte ImprintSound[1] = {{600, 30}};
SoundByte MoveSound[1] = {{800, 20}};
SoundByte RotateSound[1] = {{700, 20}};
SoundByte LevelSound[3] = {{900, 20}, {0, 10}, {900, 10}};

SoundSample PauseSoundSample = {
    .SampleCount = 4,
    .Data = &PauseSound[0]
};

SoundSample ImprintSoundSample = {
    .SampleCount = 1,
    .Data = &ImprintSound[0]
};

SoundSample MoveSoundSample = {
    .SampleCount = 1,
    .Data = &MoveSound[0]
};

SoundSample RotateSoundSample = {
    .SampleCount = 1,
    .Data = &RotateSound[0]
};

SoundSample LevelSoundSample = {
    .SampleCount = 4,
    .Data = &LevelSound[0]
};

//Sound device
typedef struct {
    bool Playing;
    int SampleCount;
    SoundByte* Data;
    unsigned long StartMilis;
}Sound;

Sound activeSound = {
    .Playing = false,
    .SampleCount = 0,
    .Data = NULL,
    .StartMilis = 0
};

void PlayAudio(SoundSample Sample);
void StopAudio();
void AudioTick();

#endif