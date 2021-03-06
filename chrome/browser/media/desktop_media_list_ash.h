// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_DESKTOP_MEDIA_LIST_ASH_H_
#define CHROME_BROWSER_MEDIA_DESKTOP_MEDIA_LIST_ASH_H_

#include "base/memory/weak_ptr.h"
#include "chrome/browser/media/desktop_media_list_base.h"
#include "content/public/browser/desktop_media_id.h"

namespace aura {
class Window;
}

namespace gfx {
class Image;
}

// Implementation of DesktopMediaList that shows native screens and
// native windows.
class DesktopMediaListAsh : public DesktopMediaListBase {
 public:
  enum SourceTypes {
    SCREENS = 1,
    WINDOWS = 2,
  };

  explicit DesktopMediaListAsh(int source_types);
  ~DesktopMediaListAsh() override;

 private:
  // Override from DesktopMediaListBase.
  void Refresh() override;
  void EnumerateWindowsForRoot(
      std::vector<DesktopMediaListAsh::SourceDescription>* windows,
      aura::Window* root_window,
      int container_id);
  void EnumerateSources(
      std::vector<DesktopMediaListAsh::SourceDescription>* windows);
  void CaptureThumbnail(content::DesktopMediaID id, aura::Window* window);
  void OnThumbnailCaptured(content::DesktopMediaID id,
                           const gfx::Image& image);

  int source_types_;

  int pending_window_capture_requests_;

  base::WeakPtrFactory<DesktopMediaListAsh> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DesktopMediaListAsh);
};

#endif  // CHROME_BROWSER_MEDIA_DESKTOP_MEDIA_LIST_ASH_H_
