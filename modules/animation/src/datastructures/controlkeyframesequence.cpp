/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2016-2020 Inviwo Foundation
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

#include <modules/animation/datastructures/controlkeyframesequence.h>
#include <modules/animation/algorithm/animationrange.h>

namespace inviwo {

namespace animation {

ControlKeyframeSequence::ControlKeyframeSequence() = default;

ControlKeyframeSequence::ControlKeyframeSequence(
    std::vector<std::unique_ptr<ControlKeyframe>> keyframes)
    : BaseKeyframeSequence<ControlKeyframe>(std::move(keyframes)) {}

ControlKeyframeSequence::ControlKeyframeSequence(const ControlKeyframeSequence& rhs) = default;

ControlKeyframeSequence& ControlKeyframeSequence::operator=(const ControlKeyframeSequence& that) =
    default;

ControlKeyframeSequence::~ControlKeyframeSequence() = default;

ControlKeyframeSequence* ControlKeyframeSequence::clone() const {
    return new ControlKeyframeSequence(*this);
}

AnimationTimeState ControlKeyframeSequence::operator()(Seconds from, Seconds to,
                                                       AnimationState state) const {
    auto animate = [](auto begin, auto end, Seconds from, Seconds to,
                      AnimationState state) -> AnimationTimeState {
        auto direction = from <= to ? PlaybackDirection::Forward : PlaybackDirection::Backward;
        AnimationTimeState res{to, state};
        while (begin != end && res.state != AnimationState::Paused) {
            res = (**begin)(from, to, state);
            if ((direction == PlaybackDirection::Forward && res.time <= (**begin)) ||
                (direction == PlaybackDirection::Backward && res.time >= (**begin))) {
                // We jumped in the opposite direction
                break;
            }
            // Use jump-to-time if set, previous keyframe time otherwise
            from = res.time != to ? res.time : (*begin)->getTime();

            ++begin;
        }
        return res;
    };
    auto [fromIt, toIt] = getRange(keyframes_.begin(), keyframes_.end(), from, to);
    if (from <= to) {
        return animate(fromIt, toIt, from, to, state);
    } else {
        return animate(std::make_reverse_iterator(toIt), std::make_reverse_iterator(fromIt), from,
                       to, state);
    }
}

}  // namespace animation

}  // namespace inviwo
