#ifndef DOWNLOADER_TOOLBAR_VIEW_H_
#define DOWNLOADER_TOOLBAR_VIEW_H_

#include "downloader/downloader_export.h"
#include "ui/views/view.h"

namespace downloader {

class DOWNLOADER_EXPORT ToolbarView : public views::View {
public:
  ToolbarView();
  ~ToolbarView() override;

private:
  void Init();
};

}  // namespace downloader

#endif  // DOWNLOADER_TOOLBAR_VIEW_H_
