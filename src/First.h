#pragma once
#include <math.h>

/// <summary>
/// x軸とy軸のみによる内積計算.
/// </summary>
/// <param name="In1">ベクトルA</param>
/// <param name="In2">ベクトルB</param>
/// <returns>内積</returns>
float VDotXY(const VECTOR& In1, const VECTOR& In2) {
    return In1.x * In2.x + In1.y * In2.y;
}
