//This file contains audio routines

//Hardbeat of the Audio system
void AudioTick(){
  //Check if a sample should be playing
  if((!activeSound.Playing) || (activeSound.SampleCount < 1))return;

  //Check if sample is ready to be played
  if(activeSound.StartMilis + activeSound.Data->Duration > millis())return;

  //Play the tone
  Piezo.tone(activeSound.Data->Tone, activeSound.Data->Duration);

  //Prepare for the next sound byte, if any
  activeSound.SampleCount--;
  activeSound.StartMilis = millis();
  activeSound.Data++;
}

//Play audio sample
void PlayAudio(SoundSample Sample){
    activeSound.Playing = false;
    activeSound.StartMilis = millis();
    activeSound.SampleCount = Sample.SampleCount;
    activeSound.Data = Sample.Data;
    activeSound.Playing = true;
}

void StopAudio(){
  activeSound.Playing = false;
}
