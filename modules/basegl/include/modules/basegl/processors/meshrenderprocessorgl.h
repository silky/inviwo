/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2022 Inviwo Foundation
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

#pragma once

#include <modules/basegl/baseglmoduledefine.h>  // for IVW_MODULE_BASEGL_API

#include <inviwo/core/interaction/cameratrackball.h>        // for CameraTrackball
#include <inviwo/core/ports/imageport.h>                    // for ImageInport, ImageOutport
#include <inviwo/core/ports/meshport.h>                     // for MeshFlatMultiInport
#include <inviwo/core/processors/processor.h>               // for Processor
#include <inviwo/core/processors/processorinfo.h>           // for ProcessorInfo
#include <inviwo/core/properties/boolproperty.h>            // for BoolProperty
#include <inviwo/core/properties/cameraproperty.h>          // for CameraProperty
#include <inviwo/core/properties/compositeproperty.h>       // for CompositeProperty
#include <inviwo/core/properties/optionproperty.h>          // for OptionPropertyInt
#include <inviwo/core/properties/ordinalproperty.h>         // for FloatVec4Property
#include <inviwo/core/properties/simplelightingproperty.h>  // for SimpleLightingProperty
#include <modules/opengl/shader/shader.h>                   // for Shader

namespace inviwo {

class IVW_MODULE_BASEGL_API MeshRenderProcessorGL : public Processor {
public:
    MeshRenderProcessorGL();

    MeshRenderProcessorGL(const MeshRenderProcessorGL&) = delete;
    MeshRenderProcessorGL& operator=(const MeshRenderProcessorGL&) = delete;

    virtual ~MeshRenderProcessorGL();

    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

    virtual void initializeResources() override;
    virtual void process() override;

protected:
    MeshFlatMultiInport inport_;
    ImageInport imageInport_;
    ImageOutport outport_;

    CameraProperty camera_;

    CompositeProperty meshProperties_;
    OptionPropertyInt cullFace_;
    BoolProperty enableDepthTest_;
    BoolProperty overrideColorBuffer_;
    FloatVec4Property overrideColor_;

    SimpleLightingProperty lightingProperty_;
    CameraTrackball trackball_;

    CompositeProperty layers_;
    BoolProperty colorLayer_;
    BoolProperty texCoordLayer_;
    BoolProperty normalsLayer_;
    BoolProperty viewNormalsLayer_;

    Shader shader_;
};

}  // namespace inviwo
