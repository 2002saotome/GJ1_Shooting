#include "DxLib.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "3046_Formation Shooting";

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
	int PlayerRadius = 64;
	int PlayerLife = 27;
	int PlayerSpeed = 20;

	//�G             // 1   2   3   4   5   6   7    8    9    10   11   12  13  14  15  16  17   18   19   20   21   22   23  24
	int EnemyX[24] = { 150,300,450,600,750,900,1050,1200,1350,1500,1650,1800,220,370,530,670,820,970,1120,1270,1420,1570,1720,1870};
	int EnemyY[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,400,400,400,400,400, 400, 400, 400, 400, 400, 400,400};
	int EnemyR[24] = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
	int EnemyFlag[24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	//�e
	int PlayerBeamX = 0;
	int PlayerBeamY = 0;
	int PlayerBeamR = 16;
	int PlayerBeamRadius = 0;
	int PlayerBeamSpeed = 30;
	int PlayerBeamFlag = 0;

	//�V�[��
	int scene = 0;

	//�^�C�}�[
	int Timer = 1500;
	
	//�e�ƓG�̓����蔻��(�錾)
	int dx;
	int dy;

	//�G�ƃv���C���[�̓����蔻��
	int dx2;
	int dy2;

	//�G2(��)
	int enemyX = 50;
	int enemyY = 200;
	int enemyR = 64;
	int enemyFlag = 1;
	int Dx;
	int Dy;

	


	//���\�[�X
	
	//�v���C���[
	int PlayerGraphHandle;
	PlayerGraphHandle = LoadGraph("Player.png");

	//�e�i�v���C���[�j
	int PlayerBombGraphHandle;
	PlayerBombGraphHandle = LoadGraph("Bomb.png");

	//���C�t(�v���C���[)
	int PlayerLifeGraphHandle;
	PlayerLifeGraphHandle = LoadGraph("Life.png");

	//�G
	int EnemyGraphHandle;
	EnemyGraphHandle = LoadGraph("Enemy.png");

	//�^�C�g��
	int TitleGraphHandle;
	TitleGraphHandle = LoadGraph("Title.png");

	//�Q�[������
	int OperationGraphHandle;
	OperationGraphHandle = LoadGraph("Operation_instructions.png");

	//�Q�[���w�i
	int GraphDrawHandle;
	GraphDrawHandle = LoadGraph("DrawGraph.png");

	//�Q�[���N���A
	int GameClearGraphHandle;
	GameClearGraphHandle = LoadGraph("Game_Clear.png");

	//�Q�[���I�[�o�[
	int GameOverGraphHandle;
	GameOverGraphHandle = LoadGraph("Game_Over.png");


	//BGM,SE
	//BGM
	int TitleSound = LoadSoundMem("BGM/Title.mp3");
	int GamePlaySound = LoadSoundMem("BGM/GamePlay.mp3");
	int GameClearSound = LoadSoundMem("BGM/GameClear.mp3");
	int GameOverSound = LoadSoundMem("BGM/GameOver.mp3");
	int GamePlaySoundHard = LoadSoundMem("BGM/BattleBGM.mp3");

	//SE
	int ShotSE = LoadSoundMem("BGM/Shot.mp3");
	int PlayerDamageSE = LoadSoundMem("BGM/PlayerDamage.mp3");


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
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
			PlayerLife = 27;
			PlayerBeamFlag = 0;
			PlayerBeamRadius = 64;
			PlayerBeamX = 850;
			PlayerBeamY = 830;
			Timer = 1500;


			//�G
			//BGM(�^�C�g��)
			StopSoundMem(GameClearSound);
			StopSoundMem(GamePlaySoundHard);
			StopSoundMem(GameOverSound);
			StopSoundMem(GamePlaySound);
			PlaySoundMem(TitleSound, DX_PLAYTYPE_LOOP, false);
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				scene = 1;
			}
			break;

			//�Q�[������
		case 1:
			StopSoundMem(TitleSound);
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				scene = 2;
			}
			break;

			//�Q�[���v���C
		case 2:
			PlaySoundMem(GamePlaySound, DX_PLAYTYPE_LOOP, false);
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
			if (PlayerY > 900)
			{
				PlayerY = 900;
			}
			

			//�e�̔���
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				if (PlayerBeamFlag == 0)
				{
					//SE�Đ�
					//PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK, false);

					//�v���C���[�̍��W��e�ɑ��
					PlayerBeamX = PlayerX +5;
					PlayerBeamY = PlayerY - 20;
					//�e�𑶍݂�����
					PlayerBeamFlag = 1;
				}
			}

			//�G�̏���//
			//�G�̃X�s�[�h
			for (int i = 0; i < 24; i++)
			{
				if (EnemyY[i] < 1000)
				{
					//����10����
					EnemyY[i] += 10;
				}
				
			}

			for (int i = 0; i < 24; i++)
			{
				if (EnemyY[i] == 1000)
				{
					//��ԉ��ɍs������G������
					EnemyY[i] = 0;
					
				}
				if (EnemyY[i] == 0)
			    {
					EnemyFlag[i] = 1;
			    }
			}
			
			

			
			//�r�[������//
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

			//�e�ƓG�̓����蔻��
			for (int i = 0; i < 24; i++)
			{
				if (EnemyFlag[i] == 1 && PlayerBeamFlag == 1)
				{
					dx = abs(EnemyX[i] - PlayerBeamX);
					dy = abs(EnemyY[i] - PlayerBeamY);

					if (dx < 50 && dy < 50)
					{
						EnemyFlag[i] = 0;
						PlayerBeamFlag = 0;
					}
			    }
			}

			//�v���C���[�ƓG�̓����蔻��
			for (int i = 0; i < 24; i++)
			{
				if (EnemyFlag[i] == 1 && PlayerLife <=27)
				{
					dx2 = abs(EnemyX[i] - PlayerX);
					dy2 = abs(EnemyY[i] - PlayerY);
					//���a
					int R = (PlayerRadius + EnemyR[i]) * (PlayerRadius + EnemyR[i]);

					if (dx2<64&&dy2<64)
					{
						//SE�Đ�
						//PlaySoundMem(PlayerDamageSE, DX_PLAYTYPE_NORMAL, false);
						PlayerLife--;
					}
				}
			}

			//���Z�b�g(R)
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0)
			{
				PlayerLife = 27;
			}

			//�^�C�}�[�̏���//
			Timer-=1;
			
				for (int i = 0; i < 24; i++)
				{
					if (Timer < 1000)
					{
						EnemyX[i] += 5;
					}
					if (EnemyX[i] > 1900)
					{
						EnemyX[i] = 0;
					}
					if (Timer < 500)
					{
						EnemyX[i] -= 10;
					}
					if (EnemyX[i] < 0)
					{
						EnemyX[i] = 1850;
					}
					
					if (Timer < 750)
					{
						StopSoundMem(GamePlaySound);
						PlaySoundMem(GamePlaySoundHard, DX_PLAYTYPE_LOOP, false);
					}
				}

				

			//�Q�[���N���A�E�Q�[���I�[�o�[�V�[���؂�ւ�
			//�Q�[���N���A
			if (Timer == 0)
			{
				scene = 3;
			}

			//�Q�[���I�[�o�[
			if (PlayerLife <= 0)
			{
				scene = 4;
			}


			break;

			//�Q�[���N���A
			case 3:
				StopSoundMem(GamePlaySoundHard);
				StopSoundMem(GamePlaySound);
				PlaySoundMem(GameClearSound, DX_PLAYTYPE_LOOP, false);
				if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
				{
					scene = 0;
				}
			break;

			//�Q�[���I�[�o�[
			case 4:
				StopSoundMem(GamePlaySoundHard);
				StopSoundMem(GamePlaySound);
				PlaySoundMem(GameOverSound, DX_PLAYTYPE_LOOP, false);
				if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
				{
					scene = 0;
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
			break;

			//�Q�[������
		case 1:
			DrawGraph(0, 0, OperationGraphHandle, true);
			break;

			//�Q�[���v���C
		case 2:
			//�w�i
			DrawGraph(0, 0, GraphDrawHandle, true);
			if (PlayerLife >= 1)
			{
				//�v���C���[
				DrawGraph(PlayerX-PlayerRadius, PlayerY-PlayerRadius, PlayerGraphHandle, true);
			}

			for (int i = 0; i < 24; i++)
			{
				if (EnemyFlag[i] == 1)
				{
					//�G
					DrawGraph(EnemyX[i]-EnemyR[i], EnemyY[i]-EnemyR[i], EnemyGraphHandle, true);
				}
			}

			//���C�t(�v���C���[)
			if (PlayerLife <= 27&&PlayerLife>18)
			{
				DrawGraph(0, 50, PlayerLifeGraphHandle, true);
				DrawGraph(50, 50, PlayerLifeGraphHandle, true);
				DrawGraph(100, 50, PlayerLifeGraphHandle, true);
			}

			if (PlayerLife<=18&&PlayerLife>9)
			{
				DrawGraph(0, 50, PlayerLifeGraphHandle, true);
				DrawGraph(50, 50, PlayerLifeGraphHandle, true);
			}

			if (PlayerLife<=9)
			{
				DrawGraph(0, 50, PlayerLifeGraphHandle, true);
			}

			
			//�^�C�}�[//
			if (Timer < 1500 && Timer>1450)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "30�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1450 && Timer>1400)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "29�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1400 && Timer>1350)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "28�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1350 && Timer>1300)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "27�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1300 && Timer>1250)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "26�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1250 && Timer>1200)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "25�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1200 && Timer>1150)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "24�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1150 && Timer>1100)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "23�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1100 && Timer>1050)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "22�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1050 && Timer>1000)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "21�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 1000 && Timer>950)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "20�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 950 && Timer>900)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "19�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 900 && Timer>850)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "18�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 850 && Timer>800)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "17�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 800 && Timer>750)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "16�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 750 && Timer>700)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "15�b", Timer);
				SetFontSize(64);
			}
			
			if (Timer < 700 && Timer>650)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "14�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 650 && Timer>600)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "13�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 600 && Timer>550)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "12�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 550 && Timer>500)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "11�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 500 && Timer>450)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "10�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 450 && Timer>400)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "9�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 400 && Timer>350)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "8�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 350 && Timer>300)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "7�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 300 && Timer>250)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "6�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 250 && Timer>200)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "5�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 200 && Timer>150)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "4�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 150 && Timer>100)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "3�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 100 && Timer>50)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "2�b", Timer);
				SetFontSize(64);
			}

			if (Timer < 50 && Timer>0)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "1�b", Timer);
				SetFontSize(64);
			}
			//�r�[��
			if (PlayerBeamFlag == 1)
			{
				DrawGraph(PlayerBeamX-PlayerBeamR, PlayerBeamY-PlayerBeamR, PlayerBombGraphHandle,true);
			}

			

			//SetFontSize(16);
			//DrawFormatString(0, 0, GetColor(255, 0, 0), "PlayerX:%d", PlayerX);
			//DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerY:%d", PlayerY);
			//DrawFormatString(0, 40, GetColor(255, 0, 0), "PlayerBeamX:%d", PlayerBeamX);
			//DrawFormatString(0, 60, GetColor(255, 0, 0), "PlayerBeamY:%d", PlayerBeamY);
			////�r�[��(�v���C���[)
			//DrawFormatString(0, 80, GetColor(255, 0, 0), "PlayerBeamFlag:%d", PlayerBeamFlag);
			//DrawFormatString(0, 100, GetColor(255, 0, 0), "Timer:%d", Timer);
			//DrawFormatString(0, 120, GetColor(255, 0, 0), "PlayerLife:%d", PlayerLife);

			break;

			//�Q�[���N���A
			case 3:
			DrawGraph(0, 0, GameClearGraphHandle, true);
			break;

			//�Q�[���I�[�o�[
			case 4:
			DrawGraph(0, 0, GameOverGraphHandle, true);
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
