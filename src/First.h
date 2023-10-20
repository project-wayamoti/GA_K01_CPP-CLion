#pragma once
#include <math.h>

/// <summary>
/// x����y���݂̂ɂ����όv�Z.
/// </summary>
/// <param name="In1">�x�N�g��A</param>
/// <param name="In2">�x�N�g��B</param>
/// <returns>����</returns>
float VDotXY(const VECTOR& In1, const VECTOR& In2) {
    return In1.x * In2.x + In1.y * In2.y;
}
