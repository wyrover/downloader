#ifndef DOWNLOADER_TOOLBAR_BUTTON_H_
#define DOWNLOADER_TOOLBAR_BUTTON_H_

#include "downloader/downloader_export.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/button/image_button.h"

namespace views {
}

namespace ui {
class MouseEvent;
class Event;
}

namespace downloader {

class DOWNLOADER_EXPORT ToolbarButton : public views::ImageButton {
public:
  ToolbarButton(views::ButtonListener* listener);
  ~ToolbarButton() override;

private:
  // Overridden from views::View:
  void Layout() override;
  void OnMouseEntered(const ui::MouseEvent& event) override;
  void OnMouseExited(const ui::MouseEvent& event) override;
  void OnMouseMoved(const ui::MouseEvent& event) override;
};

}  // namespace downloader

#endif  // DOWNLOADER_TOOLBAR_BUTTON_H_
