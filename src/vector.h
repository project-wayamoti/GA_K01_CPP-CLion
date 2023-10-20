//
// Created by waya on 2023/06/10.
//
#ifndef VECTOR_H
#define VECTOR_H

#pragma once
#include <iostream>
using namespace std;

// Vector2�\����
// �y�ł��邱�Ɓz
// �EVector2�\���̂̃C���X�^���X���쐬
// �EVector2�\���̂̃C���X�^���X��x, y�̒l��ݒ�
// �EVector2�\���̂̃C���X�^���X��x, y�̒l���擾
// �E2�̉~�̒��S���W�̋������v�Z
class Vector2 {
public:
    // x, y�̒l��ێ�����ϐ�
    float x, y;
    float size;

    // �R���X�g���N�^
    Vector2(float x = 0, float y = 0, float size = 0) : x(x), y(y), size(size) {
        cout << "calling constructor." << endl;
    }
    ~Vector2() {
        cout << "calling destructor." << endl;
    }

    // x, y�̒l��ݒ肷��֐�
    inline float X() const {
        return x;
    }
    inline float X(float x) {
        return this->x = x;
    }
    inline float Y() const {
        return y;
    }
    inline float Y(float y) {
        return this->y = y;
    }
    inline float Size() const {
        return size;
    }
    inline float Size(float size) {
        return this->size = size;
    }
    // Q. ����͂Ȃ�ł����H
    // A. ����́A�C�����C���֐��ƌĂ΂����̂ł��B
    //    ���̊֐��́A�֐��̒��g���Ăяo�����ɓW�J���Ă����֐��ł��B
    //    �܂�A���̊֐����Ăяo���ƁA
    //    �ureturn x;�v�Ɓureturn this->x = x;�v���Ăяo�����ɓW�J����܂��B
    //    ���̊֐��́A�֐��̌Ăяo���ɔ����I�[�o�[�w�b�h���팸���邽�߂Ɏg�p����܂��B
    //    �܂��A�֐��̌Ăяo���ɔ����I�[�o�[�w�b�h���팸���邱�ƂŁA
    //    �v���O�����̎��s���x�����コ���邱�Ƃ��ł��܂��B
    //    �Ȃ��A�C�����C���֐��́A�֐��̒��g���Z���ꍇ�Ɏg�p���邱�Ƃ���������܂��B
    //    �Ȃ��Ȃ�A�֐��̒��g�������ꍇ�A
    //    �C�����C���֐����g�p���邱�ƂŁA�v���O�����̎��s���x���ቺ����\�������邩��ł��B
    //    �Ȃ��A�C�����C���֐��́A�֐��̑O�Ɂuinline�v��t���邱�ƂŁA
    //    �C�����C���֐��Ƃ��Ē�`���邱�Ƃ��ł��܂��B
};

#endif //VECTOR_H
