#include "downloader/toolbar_view.h"

#include "downloader/grit/downloader_images_resources.h"
#include "downloader/grit/downloader_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "downloader/toolbar_button.h"
#include "ui/events/event.h"
#include "ui/base/resource/resource_bundle.h"
#include "ui/views/border.h"

namespace downloader {

const struct ToolbarButtonList {
  const char* name;
  const int image_id;
  const int tooltip_text_id;
} kToolbarButtonList[] = {
  {"new", IDR_DOWNLOADER_IMAGE_NEW, IDS_DOWNLOADER_TOOLTIP_NEW},
  {"start", IDR_DOWNLOADER_IMAGE_START, IDS_DOWNLOADER_TOOLTIP_START},
  {"start_all", IDR_DOWNLOADER_IMAGE_START_ALL, IDS_DOWNLOADER_TOOLTIP_START_ALL},
  {"pause", IDR_DOWNLOADER_IMAGE_PAUSE, IDS_DOWNLOADER_TOOLTIP_PAUSE},
  {"pause_all", IDR_DOWNLOADER_IMAGE_PAUSE_ALL, IDS_DOWNLOADER_TOOLTIP_PAUSE_ALL},
  {"delete", IDR_DOWNLOADER_IMAGE_DELETE, IDS_DOWNLOADER_TOOLTIP_DELETE},
  {"delete_all", IDR_DOWNLOADER_IMAGE_DELETE_ALL, IDS_DOWNLOADER_TOOLTIP_DELETE_ALL},
  {"setting", IDR_DOWNLOADER_IMAGE_SETTING, IDS_DOWNLOADER_TOOLTIP_SETTING},
  {"help", IDR_DOWNLOADER_IMAGE_HELP, IDS_DOWNLOADER_TOOLTIP_HELP},
};

ToolbarView::ToolbarView() {
  Init();
}

ToolbarView::~ToolbarView() {

}

void ToolbarView::Init() {
  toolbar_button_list_.clear();

  SetBorder(views::Border::CreateSolidSidedBorder(0, 0, 1, 0, SK_ColorBLACK));

  ToolbarButton* toolbar_button = NULL;
  for (int i = 0; i < 9; ++i) {
    toolbar_button = new ToolbarButton(this);
    AddChildView(toolbar_button);
    toolbar_button_list_.push_back(toolbar_button);
  }
}

void ToolbarView::ButtonPressed(views::Button* sender, const ui::Event& event) {
  LOG(ERROR) << __func__;
}

void ToolbarView::Layout() {
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();

  for (size_t i = 0; i < arraysize(kToolbarButtonList); ++i) {
    toolbar_button_list_[i]->SetImage(
        views::Button::STATE_NORMAL,
        rb.GetImageSkiaNamed(kToolbarButtonList[i].image_id));
    toolbar_button_list_[i]->SetTooltipText(
        l10n_util::GetStringUTF16(kToolbarButtonList[i].tooltip_text_id));
    toolbar_button_list_[i]->SetBounds(60 * i + 20, 22, 36, 36);
  }
}

}  // namespace downloader
