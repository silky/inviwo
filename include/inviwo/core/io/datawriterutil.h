/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2022 Inviwo Foundation
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

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwoapplication.h>
#include <inviwo/core/io/datawriterfactory.h>
#include <inviwo/core/util/fileextension.h>
#include <inviwo/core/io/datawriter.h>
#include <inviwo/core/io/datawriterexception.h>

#include <string_view>
#include <vector>

namespace inviwo {

namespace util {

template <typename T>
void saveData(const T& data, std::string_view path, const FileExtension& extension,
              Overwrite overwrite) {
    auto factory = InviwoApplication::getPtr()->getDataWriterFactory();
    if (auto writer = factory->getWriterForTypeAndExtension<T>(extension, path)) {
        writer->setOverwrite(overwrite);
        writer->writeData(&data, path);
    } else {
        throw DataWriterException(
            fmt::format("Could not find a writer for {} of the specified extension {}", path,
                        extension.toString()),
            IVW_CONTEXT_CUSTOM("datawriterutil"));
    }
}

template <typename T>
std::optional<std::string> saveData(const T& data, std::string_view path, std::string_view name,
                                    const std::vector<FileExtension>& extensions,
                                    Overwrite overwrite) {
    auto factory = InviwoApplication::getPtr()->getDataWriterFactory();

    for (const auto& extension : extensions) {
        if (auto writer = factory->getWriterForTypeAndExtension<T>(extension.extension_)) {
            writer->setOverwrite(overwrite);
            const auto file = fmt::format("{}/{}.{}", path, name, extension.extension_);
            writer->writeData(&data, file);
            return file;
        }
    }
    return std::nullopt;
}

}  // namespace util

}  // namespace inviwo
