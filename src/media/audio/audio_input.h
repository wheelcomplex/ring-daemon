/*
 *  Copyright (C) 2018 Savoir-faire Linux Inc.
 *
 *  Author: Hugo Lefeuvre <hugo.lefeuvre@savoirfairelinux.com>
 * Author: Philippe Gorley <philippe.gorley@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.
 */

#pragma once

#include <future>
#include <mutex>

#include "audio/audiobuffer.h"
#include "media_device.h"
#include "media_buffer.h"
#include "threadloop.h"

namespace ring {

class MediaRecorder;
class Resampler;

class AudioInput
{
public:
    AudioInput(const std::string& id);
    ~AudioInput();

    std::shared_future<DeviceParams> switchInput(const std::string& resource);

    void setFormat(const AudioFormat& fmt);
    void setMuted(bool isMuted);
    void initRecorder(const std::shared_ptr<MediaRecorder>& rec);

private:
    std::string id_;
    AudioBuffer micData_;
    bool muteState_ = false;
    uint64_t sent_samples = 0;
    std::mutex fmtMutex_ {};
    AudioFormat format_;

    std::unique_ptr<Resampler> resampler_;
    std::weak_ptr<MediaRecorder> recorder_;

    ThreadLoop loop_;
    void process();
};

} // namespace ring