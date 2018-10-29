//g++ base.cpp -lasound;./a.out;rm a.out;
//This program should respond to the user saying a voice command

#include <alsa/asoundlib.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
	snd_pcm_t *handle;
	unsigned char buffer[16*1024];

	//give the buffer data
	for(int i=0;i<sizeof(buffer);i++)buffer[i]=random()&0xff;
	for(int i=0;i<sizeof(buffer);i++)buffer[i]=sin(2*i)*0xff;

	//opens the audio device
	snd_pcm_open(&handle,"default",SND_PCM_STREAM_PLAYBACK,0);

	//set parameters of the audio device
	snd_pcm_set_params(handle,SND_PCM_FORMAT_U8,SND_PCM_ACCESS_RW_INTERLEAVED,1,48000,1,500000);

	//play the audio buffer 10 times
	for(int i=0;i<10;i++)
		snd_pcm_writei(handle,buffer,sizeof(buffer));

	snd_pcm_close(handle);
	return 0;
}
