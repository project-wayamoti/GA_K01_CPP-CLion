// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "utils.h"

//## ���ɉ����Đݒ�
using namespace std;

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ݒ�
    SetGraphMode(WIDTH, HEIGHT, 32); // ��ʃT�C�Y�ݒ�
    SetWaitVSyncFlag(TRUE); // ����������L���ɂ���

    unsigned int white = GetColor(255,255,255);

    //int LinePosX = 0, LinePosY = 480;
    VECTOR CenterPos = VGet(WIDTH / 2, HEIGHT / 2, 0);
    VECTOR LinePosLeft = VGet(0, HEIGHT / 2, 0);
    VECTOR LinePosRight = VGet(WIDTH, HEIGHT / 2, 0);

    // �O�p�`�̒��_
    Triangle triangle(VGet(500, 500, 0), VGet(600,650, 0), VGet(700, 600, 0));

    // DX���C�u��������������
    if (DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    //##### ���C�����[�v�i�`�揈���j #####//
    while (ProcessMessage() == 0) {
        ClearDrawScreen(); // ��ʂ̍X�V

        printfDx("Hello World!");
        if (CheckHitKey(KEY_INPUT_A) == 1) floatRotateOrientation = -0.1; // A�L�[�������ꂽ�獶��]
        if (CheckHitKey(KEY_INPUT_D) == 1) floatRotateOrientation = 0.1;  // D�L�[�������ꂽ��E��]

        // A�L�[�AD�L�[�̂����ꂩ��������Ă������Őݒ肳�ꂽ�l���g���ĉ�]
        if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_D) == 1) {
            circleMAN.Rotate (circleCentralPos, floatRotateOrientation);
        }

        }

        CenterPos = triangle.Hit(CenterPos, LinePosLeft, LinePosRight);

        DrawTriangle(triangle.pos[0].x, triangle.pos[0].y, triangle.pos[1].x, triangle.pos[1].y, triangle.pos[2].x, triangle.pos[2].y, white, true);
        DrawCircle(CenterPos.x, CenterPos.y, 5, white, true);
        DrawLine(LinePosLeft.x, LinePosLeft.y, LinePosRight.x, LinePosRight.y, white);

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}
