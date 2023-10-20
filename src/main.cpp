// Program     : 三角形の回転と当たり判定
// Author      : KASHIWAYA Rikuto (waya0125@wayamoti2015)
// Created     : 2023/10/21
// Updated     : 2023/10/21
// Description : 三角形を回転させて当たり判定と当たった部分を基準とした回転を行うプログラム
// URL         : https://github.com/project-wayamoti/GA_K01_CPP-Clion/

//## 環境に応じて設定
#pragma comment(linker, "/subsystem:windows") // CLionで動かす際、このコードがないとコンパイルが通らない
#include "triangle.h" // 三角形クラスヘッダー + ベクトルクラスヘッダー + ユーティリティヘッダー
using namespace std;

//## 変数
float floatRotateOrientation = 0.0; // 回転方向 0.1 = 右, -0.1 = 左

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32); // 画面サイズ設定
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    unsigned int white = GetColor(255, 255, 255);
    unsigned int red = GetColor(255, 0, 0);

    Vector2 circleCentralPos = Vector2(WIDTH / 2, HEIGHT / 2); // 中心座標
    Vector2 linesPosLeft = Vector2(0, HEIGHT / 2);             // 基準線の左座標
    Vector2 linesPosRight = Vector2(WIDTH, HEIGHT / 2);        // 基準線の右座標

    // 円の頂点座標
    CircleClass circleMAN = {
        Vector2(400, 250),
        Vector2(600, 250),
        Vector2(500, 200)
    };

    // ################################################################################

    // DXライブラリ初期化処理でエラーが起きたら終了
    if (DxLib_Init() == -1) return -1;

    //##### メインループ（描画処理） #####//
    while (ProcessMessage() == 0) {
        ClearDrawScreen(); // 画面の更新
        printfDx("Hello World! "); // なんとなく残ってるけど意味はない

        if (CheckHitKey(KEY_INPUT_A) == 1) floatRotateOrientation = -0.1; // Aキーが押されたら左回転
        if (CheckHitKey(KEY_INPUT_D) == 1) floatRotateOrientation = 0.1;  // Dキーが押されたら右回転

        // Aキー、Dキーのいずれかが押されていたら上で設定された値を使って回転
        if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
            circleMAN.Rotate (circleCentralPos, floatRotateOrientation);
        }

        // 回転後に回転方向をリセット
        floatRotateOrientation = 0.0;

        // 三角形の当たり判定 & 中心座標の更新
        circleCentralPos = circleMAN.Hit(
            circleCentralPos,
            linesPosLeft,
            linesPosRight
        );

        // 三角の頂点描画 頂点分だけ回す
        for (auto & i : circleMAN.pos) {
            // 三角形の頂点の描画
            DrawCircle((int)i.x, (int)i.y, 5, white, true);
        }

        // 三角形の描画
        DrawTriangle((int)circleMAN.pos[0].x, (int)circleMAN.pos[0].y, (int)circleMAN.pos[1].x, (int)circleMAN.pos[1].y, (int)circleMAN.pos[2].x, (int)circleMAN.pos[2].y, white, false);

        // 回転中心部の描画
        DrawCircle((int)circleCentralPos.x, (int)circleCentralPos.y, 5, red, true);

        // 基準線の描画
        DrawLine((int)linesPosLeft.X(), (int)linesPosLeft.Y(), (int)linesPosRight.X(), (int)linesPosRight.Y(), white);

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}
