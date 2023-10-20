//
// Created by waya on 2023/07/14.
//

#ifndef UTILS_CLASS
#define UTILS_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "DxLib.h"

#define WIDTH 1280
#define HEIGHT 720

using namespace std;

class Triangle {
public:
    int width = 0;
    int hit = 0;
    float turn = 0.0;
    VECTOR pos[3];

    // コンストラクタ
    Triangle(VECTOR vec1, VECTOR vec2, VECTOR vec3) : pos { vec1, vec2, vec3 }, width(10) {}

    void Turn(VECTOR CircleCentral); // 回転処理
    VECTOR Hit(VECTOR CircleCentral, VECTOR V1, VECTOR V2); // 線分との接触判定
};

void Triangle::Turn(VECTOR CircleCentral) {
    for (int i = 0; i < 3; i++) {
        VECTOR V1 = VSub(pos[i], CircleCentral);
        pos[i] = VAdd(VGet(V1.x * cos(turn) - V1.y * sin(turn), V1.x * sin(turn) + V1.y * cos(turn), 0), CircleCentral);
    }
}

VECTOR Triangle::Hit(VECTOR CircleCentral, VECTOR V1, VECTOR V2) {
    int i = 0;
    VECTOR RelativeV1 = VSub(V2, V1);
    for (i = 0; i < 3; i++) {
        VECTOR RelativeV2 = VSub(pos[i], V1);
        VECTOR RelativeV1Norm = VNorm(RelativeV1);
        VECTOR V1CrossV2 = VCross(RelativeV1Norm, RelativeV2);

        VECTOR RelativeV3 = VSub(V1, V2);
        VECTOR RelativeV4 = VSub(pos[i], V2);

        float V1DotV2 = RelativeV1.x * RelativeV2.x + RelativeV1.y * RelativeV2.y;
        float V3DotV4 = RelativeV3.x * RelativeV4.x + RelativeV3.y * RelativeV4.y;

        // 判定チェック
        if (V1DotV2 > 0 && V3DotV4 > 0 && V1CrossV2.z >= 1) {
            if (hit != i) {
                int fixPos = pos[i].y - HEIGHT / 2;
                for (int j = 0; j < 3; j++) {
                    pos[j].y -= fixPos;
                }
                hit = i;
                return pos[i];
            }
        }
    }
    return CircleCentral;
}

#endif //UTILS_H
