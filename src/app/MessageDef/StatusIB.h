/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2016-2017 Nest Labs, Inc.
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
/**
 *    @file
 *      This file defines Status Information Block in Interaction Model
 *
 */

#pragma once

#include "StructBuilder.h"
#include "StructParser.h"

#include <app/AppBuildConfig.h>
#include <app/util/basic-types.h>
#include <lib/core/CHIPCore.h>
#include <lib/core/CHIPTLV.h>
#include <lib/core/Optional.h>
#include <lib/support/CodeUtils.h>
#include <lib/support/logging/CHIPLogging.h>
#include <protocols/interaction_model/Constants.h>
#include <protocols/secure_channel/Constants.h>

namespace chip {
namespace app {
struct StatusIB
{
    StatusIB() = default;
    StatusIB(Protocols::InteractionModel::Status imStatus) : mStatus(imStatus) {}
    StatusIB(Protocols::InteractionModel::Status imStatus, ClusterStatus clusterStatus) :
        mStatus(imStatus), mClusterStatus(clusterStatus)
    {}

    enum class Tag : uint8_t
    {
        kStatus        = 0,
        kClusterStatus = 1,
    };

    class Parser : public StructParser
    {
    public:
#if CHIP_CONFIG_IM_ENABLE_SCHEMA_CHECK
        /**
         *  @brief Roughly verify the message is correctly formed
         *   1) all mandatory tags are present
         *   2) all elements have expected data type
         *   3) any tag can only appear once
         *   4) At the top level of the structure, unknown tags are ignored for forward compatibility
         *  @note The main use of this function is to print out what we're
         *    receiving during protocol development and debugging.
         *    The encoding rule has changed in IM encoding spec so this
         *    check is only "roughly" conformant now.
         *
         *  @return #CHIP_NO_ERROR on success
         */
        CHIP_ERROR CheckSchemaValidity() const;
#endif

        /**
         * Decode the StatusIB
         *
         * @return       CHIP_ERROR codes returned by chip::TLV objects. CHIP_END_OF_TLV if either
         *               element is missing. CHIP_ERROR_WRONG_TLV_TYPE if the elements are of the wrong
         *               type.
         */
        CHIP_ERROR DecodeStatusIB(StatusIB & aStatusIB) const;
    };

    class Builder : public StructBuilder
    {
    public:
        /**
         * Write the StatusIB into TLV and close the container
         *
         * @return       CHIP_ERROR codes returned by chip::TLV objects. CHIP_END_OF_TLV if either
         *               element is missing. CHIP_ERROR_WRONG_TLV_TYPE if the elements are of the wrong
         *               type.
         */
        StatusIB::Builder & EncodeStatusIB(const StatusIB & aStatusIB);
    };

    /**
     * Encapsulate a StatusIB in a CHIP_ERROR.  This can be done for any
     * StatusIB, but will treat all success codes (including cluster-specific
     * ones) as CHIP_NO_ERROR.  The resulting CHIP_ERROR will either be
     * CHIP_NO_ERROR or test true for IsIMStatus().
     */
    CHIP_ERROR ToChipError() const;

    /**
     * Extract a CHIP_ERROR into this StatusIB.  If IsIMStatus is false for the
     * error, this might do a best-effort attempt to come up with a
     * corresponding StatusIB, defaulting to a generic Status::Failure.
     */
    void InitFromChipError(CHIP_ERROR aError);

    Protocols::InteractionModel::Status mStatus = Protocols::InteractionModel::Status::Success;
    Optional<ClusterStatus> mClusterStatus      = Optional<ClusterStatus>::Missing();

}; // struct StatusIB

}; // namespace app
}; // namespace chip
