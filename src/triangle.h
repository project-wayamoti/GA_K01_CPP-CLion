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

// ##### �O�p�`�N���X #####
// # �ł��邱��
// - �O�p�`�̒��_���W��ݒ�
// - �O�p�`�̒��_���W���擾
// - �O�p�`�̉�]����
// - �O�p�`�̓����蔻��
// �Q�l���� : ���ѓċL�A���ѕ������N���X�ŏ������悤�Ƃ����������܂����B
// ����     : �Ȃ�
class CircleClass {
    public:
        int hit = 114514; // �����蔻��̃t���O (���W�P��) 114514�̓_�~�[�B�����̂͋C�̏���
        Vector2 pos[3];   // �O�p�̒��_���W (�z��i�[)

        // �R���X�g���N�^ & �f�X�g���N�^
        CircleClass(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3) : pos{pos1, pos2, pos3} {
            cout << "calling constructor." << endl;
        }
        ~CircleClass() {
            cout << "calling destructor." << endl;
        }

        // ##### ��]���� #####
        // �Q�l���� : ���ѓċL����]��̍��W����̕����������������܂����B
        // ����     : Vector2 ���S���W, float ��]���x
        // �߂�l   : �_�Ɠ_�̊Ԃ�������true
        // ����     : �Ȃ�
        void Rotate(const Vector2& CircleCentral, float turnSpeed) {
            // �O�p�̒��_����
            for (auto & po : pos) {
                // ���S����̑��΃x�N�g��
                Vector2 V1 = subVector(po, CircleCentral);

                // ��]��̍��W����
                po = addVector(
                    Vector2(
                        V1.x * cos(turnSpeed) - V1.y * sin(turnSpeed), // ��]���x���W cos�� * x - sin�� * y
                        V1.x * sin(turnSpeed) + V1.y * cos(turnSpeed)  // ��]���y���W sin�� * x + cos�� * y
                    ),
                    CircleCentral
                );
            }
        }

        // ##### �����蔻�� #####
        // �Q�l���� : �Ȃ�
        // ����     : Vector2 �~�̒��S���W, Vector2 ����n�_A, Vector2 ����n�_B
        // �߂�l   : �������Ă�����A����O�̓����蔻��ƈႤ�Ȃ�A�Y�����z�������ύX��̐ڐG���_Vector2��Ԃ�
        // ����     : pos�̔z��Ԃ�񂷂��ƂɂȂ��Ă���̂ŁApos�̔z��̐���ς�����A���̊֐����ς���K�v������B
        Vector2 Hit(const Vector2& circleCenter, const Vector2& V1, const Vector2& V2) {
            // �O�p�̒��_����
            for (int i = 0; i < 3; i++) {
                // ����Ƃ̓����蔻��
                if (pointBetween (pos[i], V1, V2)) {
                    // ��O�̓����蔻��ƈႤ�Ȃ�
                    if (hit != i) {
                        // �ڐG�������_�̃Y����␳����
                        for (auto &po: pos) po.y -= pos[i].y - HEIGHT / 2;

                        // ���������̂ŐڐG���_���X�V
                        hit = i;

                        // �ڐG�������_��Ԃ�
                        return pos[i];
                    }
                }
            }

            // ����������Ȃ�������󂯎�������S���W�����̂܂ܕԋp����
            return circleCenter;
        }
};

#endif //TRIANGLES_CLASS
