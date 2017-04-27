#ifndef DOWNLOADER_DOWNLOADER_WINDOW_H_
#define DOWNLOADER_DOWNLOADER_WINDOW_H_

#include "base/strings/string16.h"
#include "downloader/downloader_export.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/widget/widget_delegate.h"

namespace gfx {
class Canvas;
class Size;
}

namespace ui {
class Event;
}

namespace views {
class ImageButton;
class Label;
class View;
}

namespace downloader {

class MainContents;
class MenuView;
class ToolbarView;

class DOWNLOADER_EXPORT DownloaderWindow : public views::WidgetDelegateView
                                         , public views::ButtonListener {
public:
  DownloaderWindow();
  ~DownloaderWindow() override;

private:
  void Init();

  // Overridden from views::View:
  void OnPaint(gfx::Canvas* canvas) override;
  void Layout() override;
  gfx::Size GetPreferredSize() const override;

  // Overridden from views::WidgetDelegate:
  base::string16 GetWindowTitle() const override;
  bool CanResize() const override;
  bool CanMaximize() const override;
  views::View* GetContentsView() override;
  void WindowClosing() override;

  // Overridden from views::ButtonListener:
  void ButtonPressed(views::Button* sender, const ui::Event& event) override;

  MainContents* main_contents_;
  MenuView* menu_view_;
  ToolbarView* toolbar_view_;

  DISALLOW_COPY_AND_ASSIGN(DownloaderWindow);
};

}  // namespace downloader

#endif  // DOWNLOADER_DOWNLOADER_WINDOW_H_
