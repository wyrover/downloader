#include "downloader/menu_view.h"

#include "downloader/grit/downloader_images_resources.h"
#include "downloader/grit/downloader_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/border.h"
#include "ui/views/controls/image_view.h"
#include "ui/views/controls/label.h"

namespace downloader {

MenuView::MenuView()
    : logo_(NULL)
    , name_(NULL) {
  Init();
}

MenuView::~MenuView() {

}

void MenuView::Layout() {
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();

  logo_->SetImage(rb.GetImageSkiaNamed(IDR_DOWNLOADER_IMAGE_LOGO));
  logo_->SetBounds(10, 10, 48, 48);

  gfx::Size ps = name_->GetPreferredSize();
  name_->SetBounds(60, 10, ps.width(), 48);
  name_->SetHorizontalAlignment(gfx::ALIGN_CENTER);
  name_->SetFontList(gfx::FontList("Arial,Sans serif,Bold 25px"));
}

void MenuView::Init() {
  SetBorder(views::Border::CreateSolidSidedBorder(0, 0, 0, 1, SK_ColorBLACK));

  logo_ = new views::ImageView;
  AddChildView(logo_);

  name_ = new views::Label(l10n_util::GetStringUTF16(IDS_DOWNLOADER_NAME));
  AddChildView(name_);
  // name_->
}

}  // namespace downloader
