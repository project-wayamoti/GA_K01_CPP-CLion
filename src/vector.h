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

// ##### 2�����x�N�g���N���X #####
// # �ł��邱��
// - Vector2�\���̂̃C���X�^���X���쐬
// - Vector2�\���̂̃C���X�^���X��x, y�̒l��ݒ�
// - Vector2�\���̂̃C���X�^���X��x, y�̒l���擾
// �Q�l���� : �Ȃ�
// ����     : �Ȃ�
class Vector2 {
    public:
        // x, y�̒l��ێ�����ϐ�
        float x, y;

        // �R���X�g���N�^ & �f�X�g���N�^
        // �Ȃ��R���X�g���N�^��explicit������ƈÖق̌^�ϊ����ł��Ȃ��Ȃ邽�ߌ���͂��Ȃ��B
        Vector2(float x = 0, float y = 0) : x(x), y(y) {
            cout << "calling constructor." << endl;
        }
        ~Vector2() {
            cout << "calling destructor." << endl;
        }

        // x, y�̒l��ݒ肷��֐�
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
