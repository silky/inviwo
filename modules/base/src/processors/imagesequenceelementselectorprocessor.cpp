/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2015-2022 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#include <modules/base/processors/imagesequenceelementselectorprocessor.h>

#include <inviwo/core/datastructures/image/image.h>                  // for Image
#include <inviwo/core/ports/imageport.h>                             // for ImageOutport
#include <inviwo/core/ports/outportiterable.h>                       // for OutportIterable
#include <inviwo/core/processors/processorinfo.h>                    // for ProcessorInfo
#include <inviwo/core/processors/processorstate.h>                   // for CodeState, CodeState...
#include <inviwo/core/processors/processortags.h>                    // for Tags, Tags::CPU
#include <inviwo/core/properties/ordinalproperty.h>                  // for IntSizeTProperty
#include <inviwo/core/util/glmvec.h>                                 // for uvec3
#include <modules/base/processors/vectorelementselectorprocessor.h>  // for VectorElementSelecto...
#include <modules/base/properties/sequencetimerproperty.h>           // for SequenceTimerProperty

#include <functional>  // for __base

#include <fmt/core.h>  // for basic_string_view

namespace inviwo {

const ProcessorInfo ImageSequenceElementSelectorProcessor::processorInfo_{
    "org.inviwo.ImageTimeStepSelector",  // Class identifier
    "Image Sequence Element Selector",   // Display name
    "Data Selector",                     // Category
    CodeState::Stable,                   // Code state
    Tags::CPU,                           // Tags
    R"(Select a specific image out of a sequence of images)"_unindentHelp};
const ProcessorInfo ImageSequenceElementSelectorProcessor::getProcessorInfo() const {
    return processorInfo_;
}
ImageSequenceElementSelectorProcessor::ImageSequenceElementSelectorProcessor()
    : VectorElementSelectorProcessor<Image, ImageOutport>() {
    timeStep_.index_.autoLinkToProperty<ImageSequenceElementSelectorProcessor>(
        "timeStep.selectedSequenceIndex");
    outport_.setHandleResizeEvents(false);
}

}  // namespace inviwo
