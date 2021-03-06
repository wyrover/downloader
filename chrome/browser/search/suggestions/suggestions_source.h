// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_SUGGESTIONS_SUGGESTIONS_SOURCE_H_
#define CHROME_BROWSER_SEARCH_SUGGESTIONS_SUGGESTIONS_SOURCE_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "content/public/browser/url_data_source.h"
#include "url/gurl.h"

class Profile;
class SkBitmap;

namespace suggestions {

// SuggestionsSource renders a webpage to list SuggestionsService data.
class SuggestionsSource : public content::URLDataSource {
 public:
  explicit SuggestionsSource(Profile* profile);

  // content::URLDataSource implementation.
  std::string GetSource() const override;
  void StartDataRequest(
      const std::string& path,
      int render_process_id,
      int render_frame_id,
      const content::URLDataSource::GotDataCallback& callback) override;
  std::string GetMimeType(const std::string& path) const override;
  base::MessageLoop* MessageLoopForRequestPath(
      const std::string& path) const override;

 private:
  ~SuggestionsSource() override;

  // Container for the state of a request.
  struct RequestContext {
    RequestContext(
        bool is_refresh_in,
        const suggestions::SuggestionsProfile& suggestions_profile_in,
        const content::URLDataSource::GotDataCallback& callback_in);
    ~RequestContext();

    const bool is_refresh;
    const suggestions::SuggestionsProfile suggestions_profile;
    const content::URLDataSource::GotDataCallback callback;
    std::map<GURL, std::string> base64_encoded_pngs;
  };

  // Callback for responses from each Thumbnail request.
  void OnThumbnailAvailable(RequestContext* context, base::Closure barrier,
                            const GURL& url, const SkBitmap* bitmap);

  // Callback for when all requests are complete. Renders the output webpage and
  // passes the result to the original caller.
  void OnThumbnailsFetched(RequestContext* context);

  // Only used when servicing requests on the UI thread.
  Profile* const profile_;

  // For callbacks may be run after destruction.
  base::WeakPtrFactory<SuggestionsSource> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SuggestionsSource);
};

}  // namespace suggestions

#endif  // CHROME_BROWSER_SEARCH_SUGGESTIONS_SUGGESTIONS_SOURCE_H_
