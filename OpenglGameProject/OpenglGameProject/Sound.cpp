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

	�� �Լ����� �Լ��� �� ����ƴ��� üũ�ϴ� ��Ʈ !
	������ �ִٸ� return -1 �ϰ� ����
	�� �Լ��� ���������� ���� �ƴٸ� FMOD_OK�� true�� ��
	*/

	result = FMOD::System_Create(&system);
	if (result != FMOD_OK) return false;                  // ù��°�� �� �� !! �ý��� ��ü�� ���� �������Ѿ� �Ѵ�.

	result = system->getVersion(&version);
	if (result != FMOD_OK) return false;
	else printf("FMOD version %08x\n", version);

	result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);  // �ý��� �ʱ�ȭ : chaneel 32������ ����ϰڴ�.
	if (result != FMOD_OK) return false;

	//result = system->createSound("singing.wav", FMOD_LOOP_NORMAL, 0, &sound);
	if(loop)
		result = system->createSound(path, FMOD_LOOP_NORMAL, 0, &sound); // wav ���Ϸκ��� sound ����
	else
		result = system->createSound(path, FMOD_LOOP_OFF, 0, &sound);
	if (result != FMOD_OK) return false;

	/* ===============================================================================*/
	return true;
}

bool Sound::PlaySound()
{
	result = system->playSound(sound, 0, false, &channel); // ���. �� �̶� �� �ѹ��� ����ǹǷ� ����� ���尡 ������ ������� �ʴ´�.  ���ѷ��� �ȿ��� �ý��� ��ü�� ��~~�� ������Ʈ ������� ��.
	if (result != FMOD_OK) return false;
}

bool Sound::Update()
{
	//�ý����� ����ؼ� ������Ʈ ���ְ� ������ �ֳ� üũ  (��� �� �κ��� ��� �� ���ư���. ��ġ�� ������)

	result = system->update();
	if (result != FMOD_OK) return false;


	// 1. �̺κ� �����غ��ų� 
	if (channel)
	{
		bool playing = false;
		result = channel->isPlaying(&playing);  // ���� ��� ���̶�� playing�� true�� �ǰ� ����� �����ٸ� false�� �Ǿ� ���� ���� ���������� ���α׷� ���� 
		if (!playing) return false;
	}

	//// 2. �� �κ� �����غ���  ( 1, 2 �� �ϳ���. �ϳ��� �ּ� ó���ϰ� ������� ����. 2���� �����ҰŴϱ� 1 �ּ�ó�� )

	//std::cout << "Press 0 to pause, 1 to resume, and x to exit" << std::endl;

	//int i = getch(); // Ű���� �Է� �޾Ƶ��̱�. �̶� i�� �ƽ�Ű �ڵ�� ����.

	//if (i == '0')                 // 0 Ű�� �����ٸ� ä���� ��� ���߱� ����
	//	channel->setPaused(true);    // �� channel->setPaused �� FMOD_LOOP_NORMAL �϶��� ��� �����ϴ�. FMOD_LOOP_NORMAL �� �ٲ��ֱ�
	//else if (i == '1')             // 0 Ű�� �����ٸ� ������ �ٽ� ���
	//	channel->setPaused(false);
	//else if (i == 'x')               // x Ű�� �����ٸ� ���α׷� ���� (�׳� ���ѷ��� ������ ��)
	//	return true;
}
