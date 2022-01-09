#include "Sound.hpp"

Sound::Sound(const char* soundPath)
{
	path = soundPath;
}

Sound::~Sound()
{
	system->release();
}

bool Sound::Init()
{
	/* ==============================================================================

	각 함수마다 함수가 잘 실행됐는지 체크하는 파트 !
	문제가 있다면 return -1 하고 종료
	각 함수가 정상적으로 실행 됐다면 FMOD_OK가 true일 것
	*/

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return false;                  // 첫번째로 꼭 꼭 !! 시스템 객체를 먼저 생성시켜야 한다.

	result = system->getVersion(&version);
	if (result != FMOD_OK) return false;
	else printf("FMOD version %08x\n", version);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);  // 시스템 초기화 : chaneel 32개까지 사용하겠다.
	if (result != FMOD_OK) return false;

	//result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound);
	if(loop)
		result = system->createSound(path, FMOD_LOOP_NORMAL, 0, &sound); // wav 파일로부터 sound 생성
	else
		result = system->createSound(path, FMOD_LOOP_OFF, 0, &sound);
	if (result != FMOD_OK) return false;

	/* ===============================================================================*/
	return true;
}

bool Sound::PlaySound()
{
	result = system->playSound(sound, 0, false, &channel); // 재생. 단 이때 딱 한번만 실행되므로 제대로 사운드가 끝까지 재생되지 않는다.  무한루프 안에서 시스템 객체를 계~~속 업데이트 시켜줘야 함.
	if (result != FMOD_OK) return false;
}

bool Sound::Update()
{
	//시스템을 계속해서 업데이트 해주고 문제가 있나 체크  (사실 이 부분이 없어도 잘 돌아간다. 그치만 해주자)

	result = system->update();
	if (result != FMOD_OK) return false;


	// 1. 이부분 실행해보거나 
	if (channel)
	{
		bool playing = false;
		result = channel->isPlaying(&playing);  // 곡이 재생 중이라면 playing이 true가 되고 재생이 끝났다면 false가 되어 무한 루프 빠져나오고 프로그램 종료 
		if (!playing) return false;
	}

	//// 2. 이 부분 실행해보기  ( 1, 2 중 하나만. 하나는 주석 처리하고 실행시켜 보기. 2에서 퍼즈할거니까 1 주석처리 )

	//std::cout << "Press 0 to pause, 1 to resume, and x to exit" << std::endl;

	//int i = getch(); // 키보드 입력 받아들이기. 이때 i는 아스키 코드로 정수.

	//if (i == '0')                 // 0 키를 눌렀다면 채널을 잠깐 멈추기 퍼즈
	//	channel->setPaused(true);    // 단 channel->setPaused 는 FMOD_LOOP_NORMAL 일때만 사용 가능하다. FMOD_LOOP_NORMAL 로 바꿔주기
	//else if (i == '1')             // 0 키를 눌렀다면 음악을 다시 재생
	//	channel->setPaused(false);
	//else if (i == 'x')               // x 키를 눌렀다면 프로그램 종료 (그냥 무한루프 나가면 됨)
	//	return true;
}
