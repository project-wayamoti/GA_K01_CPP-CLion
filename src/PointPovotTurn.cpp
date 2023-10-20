// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "First.h"

// ��ʃT�C�Y�萔
#define WIDTH 640
#define HEIGHT 480

// �F�萔
#define WHITE GetColor(255, 255, 255)       // ���F�擾
#define RED GetColor(255, 255, 255)       // �ԐF�擾

class Triangle {
public:
    int width = 0; // �}�`�p�����[�^
    int hitPosNumber = -1; // �ڐG���Ă��钸�_�̃i���o�[
	float turnD= 0.1; // ��]����
	VECTOR pos[3]; // ���_
    // �R���X�g���N�^
    Triangle(VECTOR vec1, VECTOR vec2, VECTOR vec3) :
        pos{ vec1, vec2, vec3 },width(10) {}

    void Turn(VECTOR center); // ��]����
    VECTOR LineHit(VECTOR center, VECTOR v1, VECTOR v2); // �����Ƃ̐ڐG����
};

/// <summary>
/// �}�`�̉�]����
/// </summary>
/// <param name="center">��]�̒��S</param>
void Triangle::Turn(VECTOR center) {
    for (int i = 0; i < 3; i++) {
        VECTOR tmpV = VSub(pos[i], center);
        pos[i] = VAdd(VGet(tmpV.x * cos(turnD) - tmpV.y * sin(turnD), tmpV.x * sin(turnD) + tmpV.y * cos(turnD), 0), center);
    }
}

/// <summary>
/// �����Ƃ̐ڐG����
/// </summary>
/// <param name="center">��]�̒��S</param>
/// <param name="v1">�����̍��[</param>
/// <param name="v2">�����̉E�[</param>
/// <returns></returns>
VECTOR Triangle::LineHit(VECTOR center, VECTOR v1, VECTOR v2) {
    float V1V2Dot = 0, V3V4Dot = 0;
    int i = 0;
    VECTOR relativeV1 = VSub(v2, v1); // ���΃x�N�g��,
    for (i = 0; i < 3; i++) {
        VECTOR relativeV2 = VSub(pos[i], v1); // ���΃x�N�g��

        VECTOR relativeV1Norm = VNorm(relativeV1); // ���K��

        VECTOR V1V2Cross = VCross(relativeV1Norm, relativeV2); // �O�όv�Z

        VECTOR relativeV3 = VSub(v1, v2); // ���΃x�N�g��
        VECTOR relativeV4 = VSub(pos[i], v2); // ���΃x�N�g��

        V1V2Dot = VDotXY(relativeV1, relativeV2); // �񎟌��ł̓��όv�Z
        V3V4Dot = VDotXY(relativeV3, relativeV4); // �񎟌��ł̓��όv�Z

        if (V1V2Cross.z >= 1 && V1V2Dot > 0 && V3V4Dot > 0) {
            // �O��ڐG�������_�ƁA���ݐڐG���Ă��钸�_��������
            if (hitPosNumber != i) {
                float  correction = pos[i].y - (HEIGHT / 2); // ���݂̐ڐG���_�Ɛ����̍���␳�l�Ƃ���
                for (int j = 0; j < 3; j++) {
                    pos[j].y -= correction; // y���W��␳
                }
                hitPosNumber = i; // ���̐ڐG���_
                return pos[i]; // �ڐG���_����]�̒��S�Ƃ���
            }
        }
    }

    return center; // �����ƒ��_�̐ڐG���Ȃ��ꍇ���S��Ԃ�
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ChangeWindowMode(true);                 // �E�B���h�E���[�h.
    SetWindowSize(WIDTH, HEIGHT);           // �E�B���h�E�T�C�Y�ݒ�

    if (DxLib_Init() == -1)                 // �c�w���C�u��������������
    {
        return -1;                          // �G���[���N������I��
    }

    char keyState[256];                             // �L�[���i�[�p�ϐ�
    GetHitKeyStateAll(keyState);                    // �L�[���͏��擾
	VECTOR centerPos = VGet(WIDTH / 2, HEIGHT / 2, 0); // ��]�̒��S���W
    VECTOR linePosLeft = VGet(0, HEIGHT / 2, 0); // �����̍��[
    VECTOR linePosRight = VGet(WIDTH, HEIGHT / 2, 0); // �����̉E�[

	Triangle triangle(VGet(100, 100, 0), VGet(150,200, 0), VGet(200, 100, 0)); // �O�p�`����

    while (!ProcessMessage() && !keyState[KEY_INPUT_ESCAPE]) {
        // ��ʂ̍X�V
        ClearDrawScreen();

        GetHitKeyStateAll(keyState);

        // �����
        if (keyState[KEY_INPUT_A]) {
            triangle.turnD = -0.1;
            triangle.Turn(centerPos);
        }

        // �E���
        if (keyState[KEY_INPUT_D]) {
            triangle.turnD = 0.1;
            triangle.Turn(centerPos);
        }

        centerPos = triangle.LineHit(centerPos, linePosLeft, linePosRight);

        // �`��
        DrawTriangle(triangle.pos[0].x, triangle.pos[0].y, triangle.pos[1].x, triangle.pos[1].y, triangle.pos[2].x, triangle.pos[2].y, WHITE, false);
        DrawCircle(centerPos.x, centerPos.y, 5, RED, true);
        DrawLine(linePosLeft.x, linePosLeft.y, linePosRight.x, linePosRight.y, WHITE);

        Sleep(10);                                      // �x��������
        ScreenFlip();                                   // ��ʂ̕\�Ɨ������ւ���
        clsDx();
    }

    DxLib_End();         // �c�w���C�u�����g�p�̏I������

    return 0;            // �\�t�g�̏I��
}