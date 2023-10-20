//
// Created by waya on 2023/10/20.
//

#ifndef TRIANGLES_CLASS
#define TRIANGLES_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "DxLib.h"
#include "vector.h"
#include "utils.h"
#define WIDTH 1280.0f
#define HEIGHT 720.0f

using namespace std;

// ##### 三角形クラス #####
// # できること
// - 三角形の頂点座標を設定
// - 三角形の頂点座標を取得
// - 三角形の回転処理
// - 三角形の当たり判定
// 参考文献 : 小林篤記、小林歩夢よりクラスで処理しようとご教示頂きました。
// 注意     : なし
class CircleClass {
    public:
        int hit = 114514; // 当たり判定のフラグ (座標単位) 114514はダミー。汚いのは気の所為
        Vector2 pos[3];   // 三角の頂点座標 (配列格納)

        // コンストラクタ & デストラクタ
        CircleClass(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3) : pos{pos1, pos2, pos3} {
            cout << "calling constructor." << endl;
        }
        ~CircleClass() {
            cout << "calling destructor." << endl;
        }

        // ##### 回転処理 #####
        // 参考文献 : 小林篤記より回転後の座標代入の部分をご教示頂きました。
        // 引数     : Vector2 中心座標, float 回転速度
        // 戻り値   : 点と点の間だったらtrue
        // 注意     : なし
        void Rotate(const Vector2& CircleCentral, float turnSpeed) {
            // 三角の頂点分回す
            for (auto & po : pos) {
                // 中心からの相対ベクトル
                Vector2 V1 = subVector(po, CircleCentral);

                // 回転後の座標を代入
                po = addVector(
                    Vector2(
                        V1.x * cos(turnSpeed) - V1.y * sin(turnSpeed), // 回転後のx座標 cosθ * x - sinθ * y
                        V1.x * sin(turnSpeed) + V1.y * cos(turnSpeed)  // 回転後のy座標 sinθ * x + cosθ * y
                    ),
                    CircleCentral
                );
            }
        }

        // ##### 当たり判定 #####
        // 参考文献 : なし
        // 引数     : Vector2 円の中心座標, Vector2 基準線地点A, Vector2 基準線地点B
        // 戻り値   : 当たっていたら、かつ一つ前の当たり判定と違うなら、ズレを吸収した変更後の接触頂点Vector2を返す
        // 注意     : posの配列ぶん回すことになっているので、posの配列の数を変えたら、この関数も変える必要がある。
        Vector2 Hit(const Vector2& circleCenter, const Vector2& V1, const Vector2& V2) {
            // 三角の頂点分回す
            for (int i = 0; i < 3; i++) {
                // 基準線との当たり判定
                if (pointBetween (pos[i], V1, V2)) {
                    // 一つ前の当たり判定と違うなら
                    if (hit != i) {
                        // 接触した頂点のズレを補正する
                        for (auto &po: pos) po.y -= pos[i].y - HEIGHT / 2;

                        // 当たったので接触頂点を更新
                        hit = i;

                        // 接触した頂点を返す
                        return pos[i];
                    }
                }
            }

            // もし当たらなかったら受け取った中心座標をそのまま返却する
            return circleCenter;
        }
};

#endif //TRIANGLES_CLASS
