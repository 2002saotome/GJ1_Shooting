#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "3046_Formation Shooting";

// ウィンドウ横幅
const int WIN_WIDTH = 1900;

// ウィンドウ縦幅
const int WIN_HEIGHT = 950;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言

	//自機
	int PlayerX = 0;
	int PlayerY = 0;
	int PlayerRadius = 64;
	int PlayerLife = 27;
	int PlayerSpeed = 20;

	//敵             // 1   2   3   4   5   6   7    8    9    10   11   12  13  14  15  16  17   18   19   20   21   22   23  24
	int EnemyX[24] = { 150,300,450,600,750,900,1050,1200,1350,1500,1650,1800,220,370,530,670,820,970,1120,1270,1420,1570,1720,1870};
	int EnemyY[24] = { 0,0,0,0,0,0,0,0,0,0,0,0,400,400,400,400,400, 400, 400, 400, 400, 400, 400,400};
	int EnemyR[24] = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32};
	int EnemyFlag[24] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	//弾
	int PlayerBeamX = 0;
	int PlayerBeamY = 0;
	int PlayerBeamR = 16;
	int PlayerBeamRadius = 0;
	int PlayerBeamSpeed = 30;
	int PlayerBeamFlag = 0;

	//シーン
	int scene = 0;

	//タイマー
	int Timer = 1500;
	
	//弾と敵の当たり判定(宣言)
	int dx;
	int dy;

	//敵とプレイヤーの当たり判定
	int dx2;
	int dy2;

	//敵2(仮)
	int enemyX = 50;
	int enemyY = 200;
	int enemyR = 64;
	int enemyFlag = 1;
	int Dx;
	int Dy;

	


	//リソース
	
	//プレイヤー
	int PlayerGraphHandle;
	PlayerGraphHandle = LoadGraph("Player.png");

	//弾（プレイヤー）
	int PlayerBombGraphHandle;
	PlayerBombGraphHandle = LoadGraph("Bomb.png");

	//ライフ(プレイヤー)
	int PlayerLifeGraphHandle;
	PlayerLifeGraphHandle = LoadGraph("Life.png");

	//敵
	int EnemyGraphHandle;
	EnemyGraphHandle = LoadGraph("Enemy.png");

	//タイトル
	int TitleGraphHandle;
	TitleGraphHandle = LoadGraph("Title.png");

	//ゲーム説明
	int OperationGraphHandle;
	OperationGraphHandle = LoadGraph("Operation_instructions.png");

	//ゲーム背景
	int GraphDrawHandle;
	GraphDrawHandle = LoadGraph("DrawGraph.png");

	//ゲームクリア
	int GameClearGraphHandle;
	GameClearGraphHandle = LoadGraph("Game_Clear.png");

	//ゲームオーバー
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


	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++)
		{
			oldkeys[i] = keys[i];
		}
		// 最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理

		//シーン
		switch (scene)
		{
			//タイトル
		case 0:
			//初期化
			//プレイヤー
			PlayerX = 850;
			PlayerY = 830;
			PlayerLife = 27;
			PlayerBeamFlag = 0;
			PlayerBeamRadius = 64;
			PlayerBeamX = 850;
			PlayerBeamY = 830;
			Timer = 1500;


			//敵
			//BGM(タイトル)
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

			//ゲーム説明
		case 1:
			StopSoundMem(TitleSound);
			if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
			{
				scene = 2;
			}
			break;

			//ゲームプレイ
		case 2:
			PlaySoundMem(GamePlaySound, DX_PLAYTYPE_LOOP, false);
			//プレイヤー移動処理
			if (keys[KEY_INPUT_RIGHT] == 1)
			{
				PlayerX += PlayerSpeed;
			}
			//左
			if (keys[KEY_INPUT_LEFT] == 1)
			{
				PlayerX -= PlayerSpeed;
			}
			//上
			if (keys[KEY_INPUT_UP] == 1)
			{
				PlayerY -= PlayerSpeed;
			}
			//下
			if (keys[KEY_INPUT_DOWN] == 1)
			{
				PlayerY += PlayerSpeed;
			}

			//移動制限
			//右
			if (PlayerX > 1778)
			{
				PlayerX = 1778;
			}

			//左
			if (PlayerX < 0)
			{
				PlayerX = 0;
			}

			//上
			if (PlayerY < 0)
			{
				PlayerY = 0;
			}

			//下
			if (PlayerY > 900)
			{
				PlayerY = 900;
			}
			

			//弾の発射
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				if (PlayerBeamFlag == 0)
				{
					//SE再生
					//PlaySoundMem(ShotSE, DX_PLAYTYPE_BACK, false);

					//プレイヤーの座標を弾に代入
					PlayerBeamX = PlayerX +5;
					PlayerBeamY = PlayerY - 20;
					//弾を存在させる
					PlayerBeamFlag = 1;
				}
			}

			//敵の処理//
			//敵のスピード
			for (int i = 0; i < 24; i++)
			{
				if (EnemyY[i] < 1000)
				{
					//下に10加速
					EnemyY[i] += 10;
				}
				
			}

			for (int i = 0; i < 24; i++)
			{
				if (EnemyY[i] == 1000)
				{
					//一番下に行ったら敵を消す
					EnemyY[i] = 0;
					
				}
				if (EnemyY[i] == 0)
			    {
					EnemyFlag[i] = 1;
			    }
			}
			
			

			
			//ビーム処理//
			if (PlayerBeamFlag == 1)
			{
				//上に移動
				PlayerBeamY = PlayerBeamY - PlayerBeamSpeed;

				//画面外なら
				if (PlayerBeamY < -20)
				{
					//弾を消す
					PlayerBeamFlag = 0;
				}
			}

			//弾と敵の当たり判定
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

			//プレイヤーと敵の当たり判定
			for (int i = 0; i < 24; i++)
			{
				if (EnemyFlag[i] == 1 && PlayerLife <=27)
				{
					dx2 = abs(EnemyX[i] - PlayerX);
					dy2 = abs(EnemyY[i] - PlayerY);
					//半径
					int R = (PlayerRadius + EnemyR[i]) * (PlayerRadius + EnemyR[i]);

					if (dx2<64&&dy2<64)
					{
						//SE再生
						//PlaySoundMem(PlayerDamageSE, DX_PLAYTYPE_NORMAL, false);
						PlayerLife--;
					}
				}
			}

			//リセット(R)
			if (keys[KEY_INPUT_R] == 1 && oldkeys[KEY_INPUT_R] == 0)
			{
				PlayerLife = 27;
			}

			//タイマーの処理//
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

				

			//ゲームクリア・ゲームオーバーシーン切り替え
			//ゲームクリア
			if (Timer == 0)
			{
				scene = 3;
			}

			//ゲームオーバー
			if (PlayerLife <= 0)
			{
				scene = 4;
			}


			break;

			//ゲームクリア
			case 3:
				StopSoundMem(GamePlaySoundHard);
				StopSoundMem(GamePlaySound);
				PlaySoundMem(GameClearSound, DX_PLAYTYPE_LOOP, false);
				if (keys[KEY_INPUT_RETURN] == 1 && oldkeys[KEY_INPUT_RETURN] == 0)
				{
					scene = 0;
				}
			break;

			//ゲームオーバー
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

		// 描画処理
		//プレイヤー

		switch (scene)
		{
			//タイトル
		case 0:
			DrawGraph(0, 0, TitleGraphHandle, true);
			break;

			//ゲーム説明
		case 1:
			DrawGraph(0, 0, OperationGraphHandle, true);
			break;

			//ゲームプレイ
		case 2:
			//背景
			DrawGraph(0, 0, GraphDrawHandle, true);
			if (PlayerLife >= 1)
			{
				//プレイヤー
				DrawGraph(PlayerX-PlayerRadius, PlayerY-PlayerRadius, PlayerGraphHandle, true);
			}

			for (int i = 0; i < 24; i++)
			{
				if (EnemyFlag[i] == 1)
				{
					//敵
					DrawGraph(EnemyX[i]-EnemyR[i], EnemyY[i]-EnemyR[i], EnemyGraphHandle, true);
				}
			}

			//ライフ(プレイヤー)
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

			
			//タイマー//
			if (Timer < 1500 && Timer>1450)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "30秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1450 && Timer>1400)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "29秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1400 && Timer>1350)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "28秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1350 && Timer>1300)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "27秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1300 && Timer>1250)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "26秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1250 && Timer>1200)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "25秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1200 && Timer>1150)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "24秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1150 && Timer>1100)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "23秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1100 && Timer>1050)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "22秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1050 && Timer>1000)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(0, 0, 255), "21秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 1000 && Timer>950)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "20秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 950 && Timer>900)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "19秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 900 && Timer>850)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "18秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 850 && Timer>800)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "17秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 800 && Timer>750)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "16秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 750 && Timer>700)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "15秒", Timer);
				SetFontSize(64);
			}
			
			if (Timer < 700 && Timer>650)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "14秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 650 && Timer>600)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "13秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 600 && Timer>550)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "12秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 550 && Timer>500)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 255, 0), "11秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 500 && Timer>450)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "10秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 450 && Timer>400)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "9秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 400 && Timer>350)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "8秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 350 && Timer>300)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "7秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 300 && Timer>250)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "6秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 250 && Timer>200)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "5秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 200 && Timer>150)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "4秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 150 && Timer>100)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "3秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 100 && Timer>50)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "2秒", Timer);
				SetFontSize(64);
			}

			if (Timer < 50 && Timer>0)
			{
				SetFontSize(64);
				DrawFormatString(1700, 0, GetColor(255, 0, 0), "1秒", Timer);
				SetFontSize(64);
			}
			//ビーム
			if (PlayerBeamFlag == 1)
			{
				DrawGraph(PlayerBeamX-PlayerBeamR, PlayerBeamY-PlayerBeamR, PlayerBombGraphHandle,true);
			}

			

			//SetFontSize(16);
			//DrawFormatString(0, 0, GetColor(255, 0, 0), "PlayerX:%d", PlayerX);
			//DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerY:%d", PlayerY);
			//DrawFormatString(0, 40, GetColor(255, 0, 0), "PlayerBeamX:%d", PlayerBeamX);
			//DrawFormatString(0, 60, GetColor(255, 0, 0), "PlayerBeamY:%d", PlayerBeamY);
			////ビーム(プレイヤー)
			//DrawFormatString(0, 80, GetColor(255, 0, 0), "PlayerBeamFlag:%d", PlayerBeamFlag);
			//DrawFormatString(0, 100, GetColor(255, 0, 0), "Timer:%d", Timer);
			//DrawFormatString(0, 120, GetColor(255, 0, 0), "PlayerLife:%d", PlayerLife);

			break;

			//ゲームクリア
			case 3:
			DrawGraph(0, 0, GameClearGraphHandle, true);
			break;

			//ゲームオーバー
			case 4:
			DrawGraph(0, 0, GameOverGraphHandle, true);
			break;

		}

		//敵
		//DrawGraph(EnemyX)

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
