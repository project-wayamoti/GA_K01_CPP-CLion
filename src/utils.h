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

// ##### �x�N�g���̉��Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ���Z����Vector2
// ����     : �Ȃ�
Vector2 addVector(const Vector2& V1, const Vector2& V2) {
    // ���Z�����x�N�g�����v�Z
    Vector2 Result = {
        V1.x + V2.x,
        V1.y + V2.y
    };
    return Result;
}

// ##### �x�N�g���̌��Z #####
// �Q�l���� : �Ȃ�
// ����     : V1, V2
// �߂�l   : ���Z����Vector2
// ����     : �Ȃ�
Vector2 subVector(const Vector2& V1, const Vector2& V2) {
    // ���Z�����x�N�g�����v�Z
    Vector2 Result = {
        V1.x - V2.x,
        V1.y - V2.y
    };
    return Result;
}

// ##### �O�όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : �O�όv�Z���ꂽfloat�l
// ����     : �Ȃ�
float crossProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.y - V1.y * V2.x;
}

// ##### ���όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 12�y�[�W�ڎ���
// ����     : Vector2 V1, Vector2 V2
// �߂�l   : ���όv�Z���ꂽfloat�l
// ����     : �Ȃ�
float dotProduct(const Vector2& V1, const Vector2& V2) {
    return V1.x * V2.x + V1.y * V2.y;
}

// ##### ���΃x�N�^�[���K�� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : V1
// �߂�l   : ���Ή����ꂽVector2
// ����     : �Ȃ�
static Vector2 normalized(const Vector2& V1) {
    // ���K���������΃x�N�g�����v�Z
    Vector2 Result = {
        V1.x / sqrtf((V1.x * V1.x) + (V1.y * V1.y)),
        V1.y / sqrtf((V1.x * V1.x) + (V1.y * V1.y))
    };
    return Result;
}

// ##### ���ςƊO�ς��v�Z���ē_�Ɠ_�̊Ԃ�������true��Ԃ� #####
// �Q�l���� : �Ȃ�
// ����     : Vector2 ���݂̍��W, Vector2 �n�_A, Vector2 �n�_B
// �߂�l   : �_�Ɠ_�̊Ԃ�������true�A�����łȂ��ꍇ��false
// ����     : �Ȃ�
bool pointBetween(const Vector2& posV, const Vector2& V1, const Vector2& V2) {
    // �_�Ɠ_�̊Ԃ��ǂ����𔻒肷��
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    // �ړI�̒n�_ - ���݂̒n�_
    Vector2 Vs1 = subVector(V2, V1);     // �����̃x�N�g��
    Vector2 Vs2 = subVector(posV, V1);   // �_�Ɛ����̎n�_�̃x�N�g��
    Vector2 Vs3 = subVector(V1, V2);     // �����̃x�N�g��
    Vector2 Vs4 = subVector(posV, V2);   // �_�Ɛ����̏I�_�̃x�N�g��
    float   Vd1 = dotProduct(Vs1, Vs2);  // ����
    float   Vd2 = dotProduct(Vs3, Vs4);  // ����
    Vector2 Vn  = normalized(Vs1);       // ���K��
    float   Vc  = crossProduct(Vn, Vs2); // �O��

    // �_�Ɠ_�̊ԂɐN�����Ă�����true��Ԃ�
    if (Vd1 > 0 && Vd2 > 0 && Vc >= 1) {
        return true;
    }

    return false;
}

#endif //UTILS_CLASS
