// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DOWNLOADER_DOWNLOADER__EXPORT_H_
#define DOWNLOADER_DOWNLOADER__EXPORT_H_

// Defines VIEWS_EXAMPLES_EXPORT so that functionality implemented by the
// views_examples_with_content_lib module can be exported to consumers.

#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(AURA_IMPLEMENTATION)
#define DOWNLOADER_EXPORT __declspec(dllexport)
#else
#define DOWNLOADER_EXPORT __declspec(dllimport)
#endif  // defined(AURA_IMPLEMENTATION)

#else  // defined(WIN32)
#if defined(AURA_IMPLEMENTATION)
#define DOWNLOADER_EXPORT __attribute__((visibility("default")))
#else
#define DOWNLOADER_EXPORT
#endif
#endif

#else  // defined(COMPONENT_BUILD)
#define DOWNLOADER_EXPORT
#endif

#endif  // DOWNLOADER_DOWNLOADER__EXPORT_H_
