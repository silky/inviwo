/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2019-2022 Inviwo Foundation
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

#include <modules/basegl/processors/raycasting/volumeraycasterbase.h>

#include <modules/basegl/processors/shadercomponentprocessorbase.h>  // for ShaderComponentProce...
#include <modules/opengl/shader/shadertype.h>                        // for ShaderType, ShaderTy...
#include <modules/opengl/shader/shaderutils.h>                       // for findShaderResource
#include <modules/opengl/shader/standardshaders.h>                   // for imgIdentityVert

#include <memory>   // for shared_ptr
#include <utility>  // for pair

namespace inviwo {

VolumeRaycasterBase::VolumeRaycasterBase(std::string_view identifier, std::string_view displayName)
    : ShaderComponentProcessorBase(
          {utilgl::imgIdentityVert(),
           {ShaderType::Fragment,
            utilgl::findShaderResource("raycasting/raycaster-template.frag")}},
          identifier, displayName) {}

VolumeRaycasterBase::~VolumeRaycasterBase() = default;

}  // namespace inviwo