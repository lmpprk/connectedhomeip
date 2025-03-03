/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include "AudioOutputManager.h"

using namespace std;
using namespace chip::app::Clusters::AudioOutput;

uint8_t AudioOutputManager::HandleGetCurrentOutput()
{
    return 0;
}

std::list<Structs::OutputInfo::Type> AudioOutputManager::HandleGetOutputList()
{
    std::list<Structs::OutputInfo::Type> list;
    // TODO: Insert code here
    int maximumVectorSize = 3;

    for (int i = 0; i < maximumVectorSize; ++i)
    {
        chip::app::Clusters::AudioOutput::Structs::OutputInfo::Type outputInfo;
        outputInfo.outputType = chip::app::Clusters::AudioOutput::OutputTypeEnum::kHdmi;
        outputInfo.name       = chip::CharSpan("exampleName", strlen("exampleName"));
        outputInfo.index      = static_cast<uint8_t>(1 + i);
        list.push_back(outputInfo);
    }
    return list;
}

bool AudioOutputManager::HandleRenameOutput(const uint8_t & index, const chip::CharSpan & name)
{
    // TODO: Insert code here
    return true;
}

bool AudioOutputManager::HandleSelectOutput(const uint8_t & index)
{
    // TODO: Insert code here
    return true;
}
