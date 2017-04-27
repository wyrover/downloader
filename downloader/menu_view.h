#ifndef DOWNLOADER_MENU_VIEW_H_
#define DOWNLOADER_MENU_VIEW_H_

#include "downloader/downloader_export.h"
#include "ui/views/view.h"

namespace views {
class ImageView;
class Label;
}

namespace downloader {

class DOWNLOADER_EXPORT MenuView : public views::View {
public:
  MenuView();
  ~MenuView() override;

private:
  void Init();

  // Overriden from View:
  void Layout() override;

  views::ImageView* logo_;
  views::Label* name_;
};

}  // namespace downloader

#endif  // DOWNLOADER_MENU_VIEW_H_
