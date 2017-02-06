/*
 * Copyright (C) 2017 The Android Open Source Project
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

#ifndef ANDROID_VINTF_KERNEL_INFO_H
#define ANDROID_VINTF_KERNEL_INFO_H

#include <map>
#include <string>

#include <utils/Errors.h>

namespace android {
namespace vintf {

// Kernel Info sent to OTA server
struct KernelInfo {

    // Get the object that contains all kernel information. If any error,
    // nullptr is returned.
    // Note: this is not thread-safe.
    static const KernelInfo *Get();

    // /proc/version
    // utsname.sysname
    const std::string &osName() const;
    // utsname.nodename
    const std::string &nodeName() const;
    // utsname.release
    const std::string &osRelease() const;
    // utsname.version
    const std::string &osVersion() const;
    // utsname.machine
    const std::string &hardwareId() const;

    // /sys/fs/selinux/policyvers
    size_t kernelSepolicyVersion() const;

private:

    friend struct KernelInfoFetcher;
    friend std::string dump(const KernelInfo &ki);

    void clear();

    // /proc/config.gz
    // Key: CONFIG_xxx; Value: the value after = sign.
    std::map<std::string, std::string> kernelConfigs;
    std::string mOsName;
    std::string mNodeName;
    std::string mOsRelease;
    std::string mOsVersion;
    std::string mHardwareId;

    size_t mKernelSepolicyVersion;

};

} // namespace vintf
} // namespace android

#endif // ANDROID_VINTF_KERNEL_INFO_H
