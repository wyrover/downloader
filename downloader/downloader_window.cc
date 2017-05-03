#include "downloader/downloader_window.h"

// #include "base/strings/utf_string_conversions.h"
#include "downloader/grit/downloader_strings.h"
#include "downloader/main_contents.h"
#include "downloader/menu_view.h"
#include "downloader/toolbar_view.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/view.h"

namespace downloader {

const int MenuViewWidth = 220;
const int ToolbarViewHeight = 80;

DownloaderWindow::DownloaderWindow()
    : main_contents_(NULL)
    , menu_view_(NULL)
    , toolbar_view_(NULL) {
  Init();
}

DownloaderWindow::~DownloaderWindow() {
}

void DownloaderWindow::Init() {
  main_contents_ = new MainContents;
  menu_view_ = new MenuView;
  toolbar_view_ = new ToolbarView;
  AddChildView(main_contents_);
  AddChildView(menu_view_);
  AddChildView(toolbar_view_);
}

void DownloaderWindow::OnPaint(gfx::Canvas* canvas) {
  canvas->FillRect(GetLocalBounds(), SK_ColorWHITE);
}

void DownloaderWindow::Layout() {
  int width = GetLocalBounds().width();
  int height = GetLocalBounds().height();
  main_contents_->SetBounds(
      MenuViewWidth, ToolbarViewHeight,
      width - MenuViewWidth, height - ToolbarViewHeight);
  menu_view_->SetBounds(0, 0, MenuViewWidth, height);
  toolbar_view_->SetBounds(
      MenuViewWidth, 0, width - MenuViewWidth, ToolbarViewHeight);
}

gfx::Size DownloaderWindow::GetPreferredSize() const {
  return gfx::Size(800, 600);
}

base::string16 DownloaderWindow::GetWindowTitle() const {
  return l10n_util::GetStringUTF16(IDS_DOWNLOADER_NAME);
}

bool DownloaderWindow::CanResize() const {
  return true;
}

bool DownloaderWindow::CanMaximize() const {
  return true;
}

views::View* DownloaderWindow::GetContentsView() {
  return this;
}

void DownloaderWindow::WindowClosing() {
  base::MessageLoop::current()->QuitWhenIdle();
}

void DownloaderWindow::ButtonPressed(
    views::Button* sender, const ui::Event& event) {
  LOG(ERROR) << __func__;
}

}  // namespace downloader
