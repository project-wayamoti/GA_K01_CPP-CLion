//
// Created by waya on 2023/07/14.
//

#ifndef UTILS_CLASS_H_
#define UTILS_CLASS_H_

#pragma once
#include <cmath>
#include <random>
#include "vector.h"
using namespace std;

/**
 * 2�̉~�̒��S���W�̋������v�Z����֐�\n
 * �Q�l����: https://www.geisya.or.jp/~mwm48961/math/distance1j.htm
 * @param v1 �Ώۂɂ������~�̒������W1
 * @param v2 �Ώۂɂ������~�̒������W2
 * @return 2�̉~�̒��S���W�̋���
 * @notes sqrt�֐����g�p���邽�߁A���̊֐��𑼂Ŏg���ꍇ��"math.h"or"cmath"��include����K�v������
 * @notes ����������̏ꍇfloat�ŕԂ��K�v�����邽�߁Asqrtf�֐����g�p���Ă���B
 */
float getBallDistance(const Vector2& v1, const Vector2& v2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    // �ړI�̒n�_ - ���݂̒n�_
    Vector2 diff = { v1.x - v2.x, v1.y - v2.y };
    // 2�̉~�̒��S���W�̋������v�Z
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2));
}

/**
 * �O�ς��v�Z����\n
 * �Q�l����: �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
 * @param start �n�_�̍��W
 * @param end �I�_�̍��W
 * @return �O��(float)
 */
float mathCross(const Vector2& start, const Vector2& end) {
    return (float)start.x * end.y - start.y * end.x;
}

/**
 * ���ς��v�Z����\n
 * �Q�l����: �Q�[���A���S���Y�� Z07 12�y�[�W�ڎ���
 * @param start �n�_�̍��W
 * @param end �I�_�̍��W
 * @return ����(float)
 */
float mathDot(const Vector2& start, const Vector2& end) {
    return (float)start.x * end.x + start.y * end.y;
}

/**
 * �_�Ɠ_�̊Ԃ��ǂ����𔻒肷��\n
 * �Q�l����: �Ȃ�
 * @param start �n�_�̍��W
 * @param end �I�_�̍��W
 * @param point �_�̍��W
 * @return �_�Ɠ_�̊Ԃ�������true
 */
bool isPointBetween(const Vector2& start, const Vector2& end, const Vector2& point) {
    // �_�Ɠ_�̊Ԃ��ǂ����𔻒肷��
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    // �ړI�̒n�_ - ���݂̒n�_
    Vector2 v4 = {end.x - start.x, end.y - start.y };
    Vector2 v5 = {point.x - start.x, point.y - start.y };
    // �_�Ɠ_�̊Ԃ̕��O��100�ɐN�����Ă�����true��Ԃ�
    if (mathCross (v4, v5) >= -10 || mathCross (v4, v5) <= 10) {
        return true;
    }
        // ���ςƊO�ς��v�Z���ē_�Ɠ_�̊Ԃ�������true��Ԃ�
    else return false;
}

/**
 * �����_���Ȓl��ԋp����\n
 * �Q�l����: http://vivi.dyndns.org/tech/cpp/random.html
 * @param min �ŏ��l
 * @param max �ő�l
 * @return min�ȏ�max�ȉ��̃����_���Ȓl
 * @note random�֐����g�p���邽�߁Arandom���C���N���[�h����K�v������
 */
int getRandom(int min, int max) {
    random_device rnd;      // �񌈒�I�ȗ���������𐶐�
    mt19937 mt(rnd()); // �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
    uniform_int_distribution<> rand100(min, max); // �͈͎w��̗���
    return rand100(mt);  // �����_���Ȓl��ԋp����
}

/**
 *
 * @param v1
 * @param v2
 * @return
 */
Vector2 findDistance(const Vector2& v1, const Vector2& v2) {
    // ���΃x�N�g���𐳋K��
    Vector2 relativeVector = {
        (v1.x - v2.x) / getBallDistance (v1, v2),
        (v1.y - v2.y) / getBallDistance (v1, v2)
    };

    // return ���ɓ���ւ�������@���킩��Ȃ��̂�POWER IS POWER
    Vector2 tmp = { relativeVector.y, -relativeVector.x };

    // �������́i���́j�̐i�s�����x�N�g����ԋp
    return tmp;
}

// ##### ���΃x�N�^�[�v�Z�֐� #####
/**
 * ���΃x�N�g�����v�Z����\n
 * �Q�l����: �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
 * @param target �ړI�̒n�_
 * @param point ���݂̒n�_
 * @return ���΃x�N�g��
 */
Vector2 getRelativeVector(const Vector2& target, const Vector2& point) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    // �ړI�̒n�_ - ���݂̒n�_
    return {target.x - point.x, target.y - point.y};
}

/**
 * �x�N�g�������擾����\n
 * �Q�l����: Siro_256
 * @param v1 ����������肽���x�N�g��
 * @return sqrtf�ŕ������������Float�l
 */
float getVectorLength(const Vector2& v1) {
    return sqrtf(v1.x * v1.x + v1.y * v1.y);
}

/**
 * ���΃x�N�g���𐳋K������
 * �Q�l����: �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
 * @param v1 ���΃x�N�g�����������x�N�g��
 * @return ���΃x�N�g�������ꂽ�x�N�g��
 */
Vector2 getNormalizedVector(const Vector2& v1) {
    // ���΃x�N�g���𐳋K������
    float length = getVectorLength(v1);
    // ���K���������΃x�N�g����ԋp����
    return {v1.x / length, v1.y / length};
}

/**
 * �ŋߖT�_��T��\n
 * �Q�l����: �Q�[���A���S���Y�� Z10 7�y�[�W�ڎ���
 * @param start �n�_�̍��W
 * @param end �I�_�̍��W
 * @param V2 V1�Ƃ̌�_��T���_�̍��W
 * @return ��_�̍��W
 */
Vector2 getNearestNeighbor(Vector2 start, Vector2 end, Vector2 V2) {
    Vector2 line = {end.x - start.x, end.y - start.y};
    Vector2 normalizedLine = getNormalizedVector(line);
    Vector2 startToV2 = {V2.x - start.x, V2.y - start.y};
    float dot = mathDot (normalizedLine, startToV2);
    Vector2 point = {start.x + normalizedLine.x * dot, start.y + normalizedLine.y * dot};
    return point;
}

/**
 * ����\�ȃI�u�W�F�N�g���ړ�������\n
 * �Q�l����: �Ȃ�
 * @param playerPos �ړ����������I�u�W�F�N�g�̍��W
 * @param moveSpeed �ړ����x
 * @param mode ���샂�[�h 1: �\���L�[ 2: WASD�L�[
 */
void moveBall(Vector2 *playerPos, const Vector2& moveSpeed, int mode) {
    if (mode == 1) {
        // �\���L�[��pPos2���ړ�������
        if (CheckHitKey(KEY_INPUT_UP)) {
            playerPos->y -= moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_DOWN)) {
            playerPos->y += moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_LEFT)) {
            playerPos->x -= moveSpeed.x;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT)) {
            playerPos->x += moveSpeed.x;
        }
    }
    else if (mode == 2) {
        // WASD�L�[��pPos1���ړ�������
        if (CheckHitKey(KEY_INPUT_W)) {
            playerPos->y -= moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_S)) {
            playerPos->y += moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_A)) {
            playerPos->x -= moveSpeed.x;
        }
        if (CheckHitKey(KEY_INPUT_D)) {
            playerPos->x += moveSpeed.x;
        }
    }
}

#endif //UTILS_CLASS_H_
