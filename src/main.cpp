// Program     : �O�p�`�̉�]�Ɠ����蔻��
// Author      : KASHIWAYA Rikuto (waya0125@wayamoti2015)
// Created     : 2023/10/21
// Updated     : 2023/10/21
// Description : �O�p�`����]�����ē����蔻��Ɠ���������������Ƃ�����]���s���v���O����
// URL         : https://github.com/project-wayamoti/GA_K01_CPP-Clion/

//## ���ɉ����Đݒ�
#pragma comment(linker, "/subsystem:windows") // CLion�œ������ہA���̃R�[�h���Ȃ��ƃR���p�C�����ʂ�Ȃ�
#include "triangle.h" // �O�p�`�N���X�w�b�_�[ + �x�N�g���N���X�w�b�_�[ + ���[�e�B���e�B�w�b�_�[
using namespace std;

//## �ϐ�
float floatRotateOrientation = 0.0; // ��]���� 0.1 = �E, -0.1 = ��

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ݒ�
    SetGraphMode(WIDTH, HEIGHT, 32); // ��ʃT�C�Y�ݒ�
    SetWaitVSyncFlag(TRUE); // ����������L���ɂ���

    unsigned int white = GetColor(255, 255, 255);
    unsigned int red = GetColor(255, 0, 0);

    Vector2 circleCentralPos = Vector2(WIDTH / 2, HEIGHT / 2); // ���S���W
    Vector2 linesPosLeft = Vector2(0, HEIGHT / 2);             // ����̍����W
    Vector2 linesPosRight = Vector2(WIDTH, HEIGHT / 2);        // ����̉E���W

    // �~�̒��_���W
    CircleClass circleMAN = {
        Vector2(400, 250),
        Vector2(600, 250),
        Vector2(500, 200)
    };

    // ################################################################################

    // DX���C�u���������������ŃG���[���N������I��
    if (DxLib_Init() == -1) return -1;

    //##### ���C�����[�v�i�`�揈���j #####//
    while (ProcessMessage() == 0) {
        ClearDrawScreen(); // ��ʂ̍X�V
        printfDx("Hello World! "); // �Ȃ�ƂȂ��c���Ă邯�ǈӖ��͂Ȃ�

        if (CheckHitKey(KEY_INPUT_A) == 1) floatRotateOrientation = -0.1; // A�L�[�������ꂽ�獶��]
        if (CheckHitKey(KEY_INPUT_D) == 1) floatRotateOrientation = 0.1;  // D�L�[�������ꂽ��E��]

        // A�L�[�AD�L�[�̂����ꂩ��������Ă������Őݒ肳�ꂽ�l���g���ĉ�]
        if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
            circleMAN.Rotate (circleCentralPos, floatRotateOrientation);
        }

        // ��]��ɉ�]���������Z�b�g
        floatRotateOrientation = 0.0;

        // �O�p�`�̓����蔻�� & ���S���W�̍X�V
        circleCentralPos = circleMAN.Hit(
            circleCentralPos,
            linesPosLeft,
            linesPosRight
        );

        // �O�p�̒��_�`�� ���_��������
        for (auto & i : circleMAN.pos) {
            // �O�p�`�̒��_�̕`��
            DrawCircle((int)i.x, (int)i.y, 5, white, true);
        }

        // �O�p�`�̕`��
        DrawTriangle((int)circleMAN.pos[0].x, (int)circleMAN.pos[0].y, (int)circleMAN.pos[1].x, (int)circleMAN.pos[1].y, (int)circleMAN.pos[2].x, (int)circleMAN.pos[2].y, white, false);

        // ��]���S���̕`��
        DrawCircle((int)circleCentralPos.x, (int)circleCentralPos.y, 5, red, true);

        // ����̕`��
        DrawLine((int)linesPosLeft.X(), (int)linesPosLeft.Y(), (int)linesPosRight.X(), (int)linesPosRight.Y(), white);

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}
