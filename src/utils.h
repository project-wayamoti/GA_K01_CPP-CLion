//
// Created by waya on 2023/07/14.
// Updated on 2023/10/20.
//

#ifndef UTILS_CLASS
#define UTILS_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "vector.h"
using namespace std;

// ##### ベクトルの加算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 加算したVector2
// 注意     : なし
Vector2 addVector(const Vector2& V1, const Vector2& V2) {
    // 加算したベクトルを計算
    Vector2 Result = {
        V1.x + V2.x,
        V1.y + V2.y
    };
    return Result;
}

// ##### ベクトルの減算 #####
// 参考文献 : なし
// 引数     : V1, V2
// 戻り値   : 減算したVector2
// 注意     : なし
Vector2 subVector(const Vector2& V1, const Vector2& V2) {
    // 減算したベクトルを計算
    Vector2 Result = {
        V1.x - V2.x,
        V1.y - V2.y
    };
    return Result;
}

// ##### 外積計算関数 #####
// 参考文献 : ゲームアルゴリズム Z07 7ページ目資料
// 引数     : x1, y1, x2, y2
// 戻り値   : 外積計算されたfloat値
// 注意     : なし
float crossProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.y - V1.y * V2.x;
}

// ##### 内積計算関数 #####
// 参考文献 : ゲームアルゴリズム Z07 12ページ目資料
// 引数     : Vector2 V1, Vector2 V2
// 戻り値   : 内積計算されたfloat値
// 注意     : なし
float dotProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.x + V1.y * V2.y;
}

// ##### 相対ベクター正規化 #####
// 参考文献 : ゲームアルゴリズム Z07 7ページ目資料
// 引数     : V1
// 戻り値   : 相対化されたVector2
// 注意     : なし
static Vector2 normalized(const Vector2& V1) {
    // 正規化した相対ベクトルを計算
    Vector2 Result = {
        V1.x / sqrtf((V1.x * V1.x) + (V1.y * V1.y)),
        V1.y / sqrtf((V1.x * V1.x) + (V1.y * V1.y))
    };
    return Result;
}

// ##### 内積と外積を計算して点と点の間だったらtrueを返す #####
// 参考文献 : なし
// 引数     : Vector2 現在の座標, Vector2 地点A, Vector2 地点B
// 戻り値   : 点と点の間だったらtrue、そうでない場合はfalse
// 注意     : なし
bool pointBetween(const Vector2& posV, const Vector2& V1, const Vector2& V2) {
    // 点と点の間かどうかを判定する
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    // 目的の地点 - 現在の地点
    Vector2 Vs1 = subVector(V2, V1);     // 線分のベクトル
    Vector2 Vs2 = subVector(posV, V1);   // 点と線分の始点のベクトル
    Vector2 Vs3 = subVector(V1, V2);     // 線分のベクトル
    Vector2 Vs4 = subVector(posV, V2);   // 点と線分の終点のベクトル
    float   Vd1 = dotProduct(Vs1, Vs2);  // 内積
    float   Vd2 = dotProduct(Vs3, Vs4);  // 内積
    Vector2 Vn  = normalized(Vs1);       // 正規化
    float   Vc  = crossProduct(Vn, Vs2); // 外積

    // 点と点の間に侵入してきたらtrueを返す
    if (Vd1 > 0 && Vd2 > 0 && Vc >= 1) {
        return true;
    }

    return false;
}

#endif //UTILS_CLASS
