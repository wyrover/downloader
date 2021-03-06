// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/media/android/browser_surface_view_manager.h"

#include "content/browser/android/child_process_launcher_android.h"
#include "content/browser/android/content_view_core_impl.h"
#include "content/browser/gpu/gpu_surface_tracker.h"
#include "content/browser/web_contents/web_contents_impl.h"
#include "content/common/media/surface_view_manager_messages_android.h"
#include "content/public/browser/render_frame_host.h"
#include "media/base/surface_manager.h"
#include "ui/gfx/geometry/size.h"

namespace content {

BrowserSurfaceViewManager::BrowserSurfaceViewManager(
    RenderFrameHost* render_frame_host)
    : render_frame_host_(render_frame_host),
      surface_id_(media::SurfaceManager::kNoSurfaceID) {}

BrowserSurfaceViewManager::~BrowserSurfaceViewManager() {}

void BrowserSurfaceViewManager::SetVideoSurface(
    gfx::ScopedJavaSurface surface) {
  if (surface.IsEmpty()) {
    DCHECK_NE(surface_id_, media::SurfaceManager::kNoSurfaceID);
    GpuSurfaceTracker::Get()->RemoveSurface(surface_id_);
    UnregisterViewSurface(surface_id_);
    surface_id_ = media::SurfaceManager::kNoSurfaceID;
  } else {
    // We mainly use the surface tracker to allocate a surface id for us. The
    // lookup will go through the Android specific path and get the java
    // surface directly, so there's no need to add a valid native widget here.
    surface_id_ = GpuSurfaceTracker::Get()->AddSurfaceForNativeWidget(
        gfx::kNullAcceleratedWidget);
    RegisterViewSurface(surface_id_, surface.j_surface().obj());
    SendSurfaceID(surface_id_);
  }
}

void BrowserSurfaceViewManager::DidExitFullscreen(bool release_media_player) {
  DVLOG(3) << __FUNCTION__;
  content_video_view_.reset();
}

void BrowserSurfaceViewManager::OnCreateFullscreenSurface(
    const gfx::Size& video_natural_size) {
  // It's valid to get this call if we already own the fullscreen view. We just
  // return the existing surface id.
  if (content_video_view_) {
    // Send the surface now if we have it. Otherwise it will be returned by
    // |SetVideoSurface|.
    if (surface_id_ != media::SurfaceManager::kNoSurfaceID) {
      SendSurfaceID(surface_id_);
      OnNaturalSizeChanged(video_natural_size);
      return;
    }
  }

  // If we don't own the fullscreen view, but one exists, it means another
  // WebContents has it. Ignore this request and return a null surface id.
  if (ContentVideoView::GetInstance()) {
    SendSurfaceID(media::SurfaceManager::kNoSurfaceID);
    return;
  }

  ContentViewCore* cvc = ContentViewCore::FromWebContents(
      WebContents::FromRenderFrameHost(render_frame_host_));
  content_video_view_.reset(new ContentVideoView(this, cvc));
  OnNaturalSizeChanged(video_natural_size);
}

void BrowserSurfaceViewManager::OnNaturalSizeChanged(const gfx::Size& size) {
  if (content_video_view_)
    content_video_view_->OnVideoSizeChanged(size.width(), size.height());
}

bool BrowserSurfaceViewManager::SendSurfaceID(int surface_id) {
  return render_frame_host_->Send(
      new SurfaceViewManagerMsg_FullscreenSurfaceCreated(
          render_frame_host_->GetRoutingID(), surface_id));
}

}  // namespace content
