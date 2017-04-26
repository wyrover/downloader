#include "downloader/downloader_window.h"

#include "base/strings/utf_string_conversions.h"
#include "downloader/grit/downloader_images_resources.h"
#include "downloader/grit/downloader_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/canvas.h"
#include "ui/gfx/geometry/size.h"
#include "ui/views/controls/button/image_button.h"
#include "ui/views/controls/label.h"
#include "ui/views/view.h"

DownloaderWindow::DownloaderWindow()
    : label_(NULL)
    , image_button_(NULL) {
  Init();
}

DownloaderWindow::~DownloaderWindow() {

}

void DownloaderWindow::Init() {
  label_ = new views::Label(base::ASCIIToUTF16("Hello, World!"));
  image_button_ = new views::ImageButton(this);

  AddChildView(label_);
  AddChildView(image_button_);
}

void DownloaderWindow::OnPaint(gfx::Canvas* canvas) {
  canvas->FillRect(GetLocalBounds(), SK_ColorWHITE);
}

void DownloaderWindow::Layout() {
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();

  gfx::Size ps = label_->GetPreferredSize();
  label_->SetBounds((width() - ps.width()) / 2, (height() - ps.height()) / 2, ps.width(), ps.height());

  image_button_->SetImage(
      views::Button::ButtonState::STATE_NORMAL,
      rb.GetNativeImageNamed(IDR_DOWNLOADER_IMAGE_LOGO).ToImageSkia());
  image_button_->SetBounds(0, 0, 100, 100);
}

gfx::Size DownloaderWindow::GetPreferredSize() const {
    // gfx::Size ps = label_->GetPreferredSize();
    // ps.set_width(ps.width() + 200);
    // ps.set_height(ps.height() + 200);
    // return ps;
  return gfx::Size(800, 600);
}

base::string16 DownloaderWindow::GetWindowTitle() const {
  // return base::ASCIIToUTF16("Hello World Window");
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

void DownloaderWindow::ButtonPressed(views::Button* sender, const ui::Event& event) {

}
