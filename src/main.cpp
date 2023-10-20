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

    // DX���C�u��������������
    if (DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    //##### ���C�����[�v�i�`�揈���j #####//
    while (ProcessMessage() == 0) {
        ClearDrawScreen(); // ��ʂ̍X�V

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
