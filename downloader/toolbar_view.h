#ifndef DOWNLOADER_TOOLBAR_VIEW_H_
#define DOWNLOADER_TOOLBAR_VIEW_H_

#include "downloader/downloader_export.h"
#include "ui/views/view.h"
#include "ui/views/controls/button/button.h"

namespace ui {
class Event;
}

namespace downloader {

class ToolbarButton;

class DOWNLOADER_EXPORT ToolbarView : public views::View
                                    , public views::ButtonListener {
public:
  ToolbarView();
  ~ToolbarView() override;

private:
  void Init();

  // Overridden from views::ButtonListener:
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  // Overriden from View:
  void Layout() override;

  // ToolbarButton* new_;
  // ToolbarButton* start_;
  // ToolbarButton* start_all_;
  // ToolbarButton* pause_;
  // ToolbarButton* pause_all_;
  // ToolbarButton* delete_;
  // ToolbarButton* delete_all_;
  // ToolbarButton* setting_;
  // ToolbarButton* help_;

  std::vector<ToolbarButton*> toolbar_button_list_;
};

}  // namespace downloader

#endif  // DOWNLOADER_TOOLBAR_VIEW_H_
