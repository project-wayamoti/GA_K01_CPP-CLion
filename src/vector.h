//
// Created by waya on 2023/06/10.
// Updated on 2023/10/20.
//
#ifndef VECTOR_H
#define VECTOR_H

#pragma once
#include <cmath>
#include <iostream>
using namespace std;

// ##### 2次元ベクトルクラス #####
// # できること
// - Vector2構造体のインスタンスを作成
// - Vector2構造体のインスタンスのx, yの値を設定
// - Vector2構造体のインスタンスのx, yの値を取得
// 参考文献 : なし
// 注意     : なし
class Vector2 {
    public:
        // x, yの値を保持する変数
        float x, y;

        // コンストラクタ & デストラクタ
        // なおコンストラクタにexplicitをつけると暗黙の型変換ができなくなるため現状はつけない。
        Vector2(float x = 0, float y = 0) : x(x), y(y) {
            cout << "calling constructor." << endl;
        }
        ~Vector2() {
            cout << "calling destructor." << endl;
        }

        // x, yの値を設定する関数
        [[nodiscard]]
        inline float X() const {
            return x;
        }
        inline float X(float d) {
            return this->x = d;
        }
        [[nodiscard]]
        inline float Y() const {
            return y;
        }
        inline float Y(float d) {
            return this->y = d;
        }
};

#endif //VECTOR_H
