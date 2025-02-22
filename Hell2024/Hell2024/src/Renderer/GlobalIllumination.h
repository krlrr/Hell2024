#pragma once
#include "RendererCommon.h"
#include "Types/LightVolume.h"
#include <vector>

namespace GlobalIllumination {

    void CreatePointCloud();
    void CreateLightVolume(float width, float height, float depth, float offsetX, float offsetY, float offsetZ);
    std::vector<CloudPoint>& GetPointCloud();
    LightVolume* GetLightVolumeByIndex(int index);
    void RecalculateAll();
    void DestroyAllLightVolumes();
}