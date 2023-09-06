#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "Shooting!!";

// �E�B���h�E����
const int WIN_WIDTH = 1900;

// �E�B���h�E�c��
const int WIN_HEIGHT = 950;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	//���@
	int PlayerX = 0;
	int PlayerY = 0;
	int PlayerRadius = 0;
	int PlayerLife = 3;
	int PlayerSpeed = 20;

	//�G
	int Enemy[10];
	int EnemyX = 0;
	int EnemyY = 0;
	int EnemyFlag = 0;

	//�e
	int PlayerBeamX = 0;
	int PlayerBeamY = 0;
	int PlayerBeamRadius = 0;
	int PlayerBeamSpeed = 30;
	int PlayerBeamFlag = 0;

	//�V�[��
	int scene = 0;


	//���\�[�X
	
	//�v���C���[
	int PlayerGraphHandle;
	PlayerGraphHandle = LoadGraph("Player.png");

	//�e�i�v���C���[�j
	int PlayerBombGraphHandle;
	PlayerBombGraphHandle = LoadGraph("Bomb.png");

	//�G
	int EnemyGraphHandle;
	EnemyGraphHandle = LoadGraph("Enemy.png");

	//�^�C�}�[
	int TimerGraphHandle;
	TimerGraphHandle = LoadGraph("");

	//�^�C�g��
	int TitleGraphHandle;
	TitleGraphHandle = LoadGraph("");

	//�Q�[���w�i
	int GraphDrawHandle;
	GraphDrawHandle = LoadGraph("DrawGraph.png");


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����

		//�V�[��
		switch (scene)
		{
			//�^�C�g��
		case 0:
			//������
			//�v���C���[
			PlayerX = 850;
			PlayerY = 830;
			EnemyX = 500;
			EnemyY = 0;
			PlayerLife = 3;
			PlayerBeamFlag = 0;
			PlayerBeamRadius = 16;
			PlayerBeamX = 850;
			PlayerBeamY = 830;
			EnemyFlag = 1;

			//�G

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 1;
			}
			break;

			//�Q�[������
		case 1:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 2;
			}
			break;

			//�Q�[���v���C
		case 2:
			//�v���C���[�ړ�����
			if (keys[KEY_INPUT_RIGHT] == 1)
			{
				PlayerX += PlayerSpeed;
			}
			//��
			if (keys[KEY_INPUT_LEFT] == 1)
			{
				PlayerX -= PlayerSpeed;
			}
			//��
			if (keys[KEY_INPUT_UP] == 1)
			{
				PlayerY -= PlayerSpeed;
			}
			//��
			if (keys[KEY_INPUT_DOWN] == 1)
			{
				PlayerY += PlayerSpeed;
			}

			//�ړ�����
			//�E
			if (PlayerX > 1778)
			{
				PlayerX = 1778;
			}

			//��
			if (PlayerX < 0)
			{
				PlayerX = 0;
			}

			//��
			if (PlayerY < 0)
			{
				PlayerY = 0;
			}

			//��
			if (PlayerY > 830)
			{
				PlayerY = 830;
			}
			

			//�e�̔���
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{

				if (PlayerBeamFlag == 0)
				{
					//�v���C���[�̍��W��e�ɑ��
					PlayerBeamX = PlayerX + 50;
					PlayerBeamY = PlayerY - 20;
					//�e�𑶍݂�����
					PlayerBeamFlag = 1;
				}
			}

			if (EnemyY < 1000)
			{
				EnemyY += 20;
			}

			if (EnemyY == 1000)
			{
				EnemyFlag = 0;
			}

			

			if (PlayerBeamFlag == 1)
			{
				//��Ɉړ�
				PlayerBeamY = PlayerBeamY - PlayerBeamSpeed;

				//��ʊO�Ȃ�
				if (PlayerBeamY < -20)
				{
					//�e������
					PlayerBeamFlag = 0;
				}
			}
			break;
		}

		// �`�揈��
		//�v���C���[

		switch (scene)
		{
			//�^�C�g��
		case 0:
			DrawGraph(0, 0, TitleGraphHandle, true);
			DrawFormatString(0, 0, GetColor(255, 0, 0), "Title", scene);
			break;

			//�Q�[������
		case 1:
			DrawFormatString(0, 0, GetColor(255, 0, 0), "Explanation", scene);
			break;

			//�Q�[���v���C
		case 2:
			//�w�i
			DrawGraph(0, 0, GraphDrawHandle, true);
			//�v���C���[
			DrawGraph(PlayerX, PlayerY, PlayerGraphHandle, true);

			if (EnemyFlag == 1)
			{
				//�G
				DrawGraph(EnemyX, EnemyY, EnemyGraphHandle, true);
			}

			DrawFormatString(0, 0, GetColor(255, 0, 0), "PlayerX:%d", PlayerX);
			DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerY:%d", PlayerY);
			DrawFormatString(0, 40, GetColor(255, 0, 0), "PlayerBeamX:%d", PlayerBeamX);
			DrawFormatString(0, 60, GetColor(255, 0, 0), "PlayerBeamY:%d", PlayerBeamY);
			//�r�[��(�v���C���[)
			DrawFormatString(0, 80, GetColor(255, 0, 0), "PlayerBeamFlag:%d", PlayerBeamFlag);
			if (PlayerBeamFlag == 1)
			{
				DrawGraph(PlayerBeamX, PlayerBeamY, PlayerBombGraphHandle,true);
			}
			break;
		}

		//�G
		//DrawGraph(EnemyX)

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
