// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "First.h"

// 画面サイズ定数
#define WIDTH 640
#define HEIGHT 480

// 色定数
#define WHITE GetColor(255, 255, 255)       // 白色取得
#define RED GetColor(255, 255, 255)       // 赤色取得

class Triangle {
public:
    int width = 0; // 図形パラメータ
    int hitPosNumber = -1; // 接触している頂点のナンバー
	float turnD= 0.1; // 回転方向
	VECTOR pos[3]; // 頂点
    // コンストラクタ
    Triangle(VECTOR vec1, VECTOR vec2, VECTOR vec3) :
        pos{ vec1, vec2, vec3 },width(10) {}

    void Turn(VECTOR center); // 回転処理
    VECTOR LineHit(VECTOR center, VECTOR v1, VECTOR v2); // 線分との接触判定
};

/// <summary>
/// 図形の回転処理
/// </summary>
/// <param name="center">回転の中心</param>
void Triangle::Turn(VECTOR center) {
    for (int i = 0; i < 3; i++) {
        VECTOR tmpV = VSub(pos[i], center);
        pos[i] = VAdd(VGet(tmpV.x * cos(turnD) - tmpV.y * sin(turnD), tmpV.x * sin(turnD) + tmpV.y * cos(turnD), 0), center);
    }
}

/// <summary>
/// 線分との接触判定
/// </summary>
/// <param name="center">回転の中心</param>
/// <param name="v1">線分の左端</param>
/// <param name="v2">線分の右端</param>
/// <returns></returns>
VECTOR Triangle::LineHit(VECTOR center, VECTOR v1, VECTOR v2) {
    float V1V2Dot = 0, V3V4Dot = 0;
    int i = 0;
    VECTOR relativeV1 = VSub(v2, v1); // 相対ベクトル,
    for (i = 0; i < 3; i++) {
        VECTOR relativeV2 = VSub(pos[i], v1); // 相対ベクトル

        VECTOR relativeV1Norm = VNorm(relativeV1); // 正規化

        VECTOR V1V2Cross = VCross(relativeV1Norm, relativeV2); // 外積計算

        VECTOR relativeV3 = VSub(v1, v2); // 相対ベクトル
        VECTOR relativeV4 = VSub(pos[i], v2); // 相対ベクトル

        V1V2Dot = VDotXY(relativeV1, relativeV2); // 二次元での内積計算
        V3V4Dot = VDotXY(relativeV3, relativeV4); // 二次元での内積計算

        if (V1V2Cross.z >= 1 && V1V2Dot > 0 && V3V4Dot > 0) {
            // 前回接触した頂点と、現在接触している頂点が同じか
            if (hitPosNumber != i) {
                float  correction = pos[i].y - (HEIGHT / 2); // 現在の接触頂点と線分の差を補正値とする
                for (int j = 0; j < 3; j++) {
                    pos[j].y -= correction; // y座標を補正
                }
                hitPosNumber = i; // 次の接触頂点
                return pos[i]; // 接触頂点を回転の中心とする
            }
        }
    }

    return center; // 線分と頂点の接触がない場合中心を返す
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(true);                 // ウィンドウモード.
    SetWindowSize(WIDTH, HEIGHT);           // ウィンドウサイズ設定

    if (DxLib_Init() == -1)                 // ＤＸライブラリ初期化処理
    {
        return -1;                          // エラーが起きたら終了
    }

    char keyState[256];                             // キー情報格納用変数
    GetHitKeyStateAll(keyState);                    // キー入力情報取得
	VECTOR centerPos = VGet(WIDTH / 2, HEIGHT / 2, 0); // 回転の中心座標
    VECTOR linePosLeft = VGet(0, HEIGHT / 2, 0); // 線分の左端
    VECTOR linePosRight = VGet(WIDTH, HEIGHT / 2, 0); // 線分の右端

	Triangle triangle(VGet(100, 100, 0), VGet(150,200, 0), VGet(200, 100, 0)); // 三角形生成

    while (!ProcessMessage() && !keyState[KEY_INPUT_ESCAPE]) {
        // 画面の更新
        ClearDrawScreen();

        GetHitKeyStateAll(keyState);

        // 左回り
        if (keyState[KEY_INPUT_A]) {
            triangle.turnD = -0.1;
            triangle.Turn(centerPos);
        }

        // 右回り
        if (keyState[KEY_INPUT_D]) {
            triangle.turnD = 0.1;
            triangle.Turn(centerPos);
        }

        centerPos = triangle.LineHit(centerPos, linePosLeft, linePosRight);

        // 描画
        DrawTriangle(triangle.pos[0].x, triangle.pos[0].y, triangle.pos[1].x, triangle.pos[1].y, triangle.pos[2].x, triangle.pos[2].y, WHITE, false);
        DrawCircle(centerPos.x, centerPos.y, 5, RED, true);
        DrawLine(linePosLeft.x, linePosLeft.y, linePosRight.x, linePosRight.y, WHITE);

        Sleep(10);                                      // 遅延させる
        ScreenFlip();                                   // 画面の表と裏を入れ替える
        clsDx();
    }

    DxLib_End();         // ＤＸライブラリ使用の終了処理

    return 0;            // ソフトの終了
}