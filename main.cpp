#include "DxLib.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "Shooting!!";

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
	int PlayerRadius = 0;
	int PlayerLife = 3;
	int PlayerSpeed = 20;

	//敵
	int Enemy[10];
	int EnemyX = 0;
	int EnemyY = 0;
	int EnemyFlag = 0;

	//弾
	int PlayerBeamX = 0;
	int PlayerBeamY = 0;
	int PlayerBeamRadius = 0;
	int PlayerBeamSpeed = 30;
	int PlayerBeamFlag = 0;

	//シーン
	int scene = 0;


	//リソース
	
	//プレイヤー
	int PlayerGraphHandle;
	PlayerGraphHandle = LoadGraph("Player.png");

	//弾（プレイヤー）
	int PlayerBombGraphHandle;
	PlayerBombGraphHandle = LoadGraph("Bomb.png");

	//敵
	int EnemyGraphHandle;
	EnemyGraphHandle = LoadGraph("Enemy.png");

	//タイマー
	int TimerGraphHandle;
	TimerGraphHandle = LoadGraph("");

	//タイトル
	int TitleGraphHandle;
	TitleGraphHandle = LoadGraph("");

	//ゲーム背景
	int GraphDrawHandle;
	GraphDrawHandle = LoadGraph("DrawGraph.png");


	// 最新のキーボード情報用
	char keys[256] = {0};

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = {0};

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
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
			EnemyX = 500;
			EnemyY = 0;
			PlayerLife = 3;
			PlayerBeamFlag = 0;
			PlayerBeamRadius = 16;
			PlayerBeamX = 850;
			PlayerBeamY = 830;
			EnemyFlag = 1;

			//敵

			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 1;
			}
			break;

			//ゲーム説明
		case 1:
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{
				scene = 2;
			}
			break;

			//ゲームプレイ
		case 2:
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
			if (PlayerY > 830)
			{
				PlayerY = 830;
			}
			

			//弾の発射
			if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
			{

				if (PlayerBeamFlag == 0)
				{
					//プレイヤーの座標を弾に代入
					PlayerBeamX = PlayerX + 50;
					PlayerBeamY = PlayerY - 20;
					//弾を存在させる
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
				//上に移動
				PlayerBeamY = PlayerBeamY - PlayerBeamSpeed;

				//画面外なら
				if (PlayerBeamY < -20)
				{
					//弾を消す
					PlayerBeamFlag = 0;
				}
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
			DrawFormatString(0, 0, GetColor(255, 0, 0), "Title", scene);
			break;

			//ゲーム説明
		case 1:
			DrawFormatString(0, 0, GetColor(255, 0, 0), "Explanation", scene);
			break;

			//ゲームプレイ
		case 2:
			//背景
			DrawGraph(0, 0, GraphDrawHandle, true);
			//プレイヤー
			DrawGraph(PlayerX, PlayerY, PlayerGraphHandle, true);

			if (EnemyFlag == 1)
			{
				//敵
				DrawGraph(EnemyX, EnemyY, EnemyGraphHandle, true);
			}

			DrawFormatString(0, 0, GetColor(255, 0, 0), "PlayerX:%d", PlayerX);
			DrawFormatString(0, 20, GetColor(255, 0, 0), "PlayerY:%d", PlayerY);
			DrawFormatString(0, 40, GetColor(255, 0, 0), "PlayerBeamX:%d", PlayerBeamX);
			DrawFormatString(0, 60, GetColor(255, 0, 0), "PlayerBeamY:%d", PlayerBeamY);
			//ビーム(プレイヤー)
			DrawFormatString(0, 80, GetColor(255, 0, 0), "PlayerBeamFlag:%d", PlayerBeamFlag);
			if (PlayerBeamFlag == 1)
			{
				DrawGraph(PlayerBeamX, PlayerBeamY, PlayerBombGraphHandle,true);
			}
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
