#include "downloader/toolbar_view.h"

#include "ui/views/border.h"

namespace downloader {

ToolbarView::ToolbarView() {
  Init();
}

ToolbarView::~ToolbarView() {

}

void ToolbarView::Init() {
  SetBorder(views::Border::CreateSolidSidedBorder(0, 0, 1, 0, SK_ColorBLACK));
}

}  // namespace downloader
