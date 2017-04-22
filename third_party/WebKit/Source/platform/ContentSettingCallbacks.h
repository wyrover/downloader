// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ContentSettingCallbacks_h
#define ContentSettingCallbacks_h

#include "platform/PlatformExport.h"
#include "wtf/Allocator.h"
#include "wtf/Functional.h"
#include "wtf/Noncopyable.h"
#include "wtf/OwnPtr.h"
#include "wtf/PassOwnPtr.h"

namespace blink {

class PLATFORM_EXPORT ContentSettingCallbacks {
    USING_FAST_MALLOC(ContentSettingCallbacks);
    WTF_MAKE_NONCOPYABLE(ContentSettingCallbacks);
public:
    static PassOwnPtr<ContentSettingCallbacks> create(PassOwnPtr<SameThreadClosure> allowed, PassOwnPtr<SameThreadClosure> denied);
    virtual ~ContentSettingCallbacks() { }

    void onAllowed() { (*m_allowed)(); }
    void onDenied() { (*m_denied)(); }

private:
    ContentSettingCallbacks(PassOwnPtr<SameThreadClosure> allowed, PassOwnPtr<SameThreadClosure> denied);

    OwnPtr<SameThreadClosure> m_allowed;
    OwnPtr<SameThreadClosure> m_denied;
};

} // namespace blink

#endif // ContentSettingCallbacks_h