#pragma once
#include "fmod.hpp"
#include <iostream>
#include <conio.h>
//https://ansohxxn.github.io/c++%20games/chapter1-5/

class Sound
{
public:
	Sound(const char* soundPath);
	~Sound();
	bool Init();
	bool PlaySound();
	bool Update();

	void SetLoop(bool isLoop) { loop = isLoop; }

private:
	FMOD::System* system = nullptr;
	FMOD::Sound* sound = nullptr;
	FMOD::Channel* channel = nullptr;
	FMOD_RESULT result;
	unsigned int version;
	void* extradriverdata = nullptr;  // 본 예제에서는 사용 x

private:
	const char* path;
	bool loop = false;
};

