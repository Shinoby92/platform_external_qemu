/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <vector>

#include "android/hw-sensors.h"
#include "android/physics/Physics.h"

namespace android {
namespace physics {

class FoldableModel {
public:
    FoldableModel();

    void setHingeAngle(uint32_t hingeIndex,
                       float degrees,
                       PhysicalInterpolation mode);

    void setPosture(float posture, PhysicalInterpolation mode);

    float getHingeAngle(uint32_t hingeIndex,
                        ParameterValueType parameterValueType =
                                PARAMETER_VALUE_TYPE_CURRENT) const;

    float getPosture(ParameterValueType parameterValueType =
                           PARAMETER_VALUE_TYPE_CURRENT) const;

    FoldableState getFoldableState() { return mState; }     // structure copy

    bool isFolded();

private:
    enum FoldablePostures calculatePosture();
    void sendPostureToSystem();
    void setToolBarFold(enum FoldablePostures oldPosture);

    FoldableState mState;
    std::vector<struct AnglesToPosture> mAnglesToPostures;
};

}  // namespace physics
}  // namespace android
