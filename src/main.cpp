// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")
#include "utils.h"

//## 環境に応じて設定
using namespace std;

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32); // 画面サイズ設定
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    unsigned int white = GetColor(255,255,255);

    //int LinePosX = 0, LinePosY = 480;
    VECTOR CenterPos = VGet(WIDTH / 2, HEIGHT / 2, 0);
    VECTOR LinePosLeft = VGet(0, HEIGHT / 2, 0);
    VECTOR LinePosRight = VGet(WIDTH, HEIGHT / 2, 0);

    // 三角形の頂点
    Triangle triangle(VGet(500, 500, 0), VGet(600,650, 0), VGet(700, 600, 0));

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    //##### メインループ（描画処理） #####//
    while (ProcessMessage() == 0) {
        ClearDrawScreen(); // 画面の更新

        printfDx("Hello World!");
        if (CheckHitKey(KEY_INPUT_A) == 1) floatRotateOrientation = -0.1; // Aキーが押されたら左回転
        if (CheckHitKey(KEY_INPUT_D) == 1) floatRotateOrientation = 0.1;  // Dキーが押されたら右回転

        // Aキー、Dキーのいずれかが押されていたら上で設定された値を使って回転
        if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
            circleMAN.Rotate (circleCentralPos, floatRotateOrientation);
        }

        }

        CenterPos = triangle.Hit(CenterPos, LinePosLeft, LinePosRight);

        DrawTriangle(triangle.pos[0].x, triangle.pos[0].y, triangle.pos[1].x, triangle.pos[1].y, triangle.pos[2].x, triangle.pos[2].y, white, true);
        DrawCircle(CenterPos.x, CenterPos.y, 5, white, true);
        DrawLine(LinePosLeft.x, LinePosLeft.y, LinePosRight.x, LinePosRight.y, white);

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}
