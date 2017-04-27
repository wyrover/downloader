#include "downloader/main_contents.h"

#include "ui/views/border.h"

namespace downloader {

MainContents::MainContents() {
  Init();
}

MainContents::~MainContents() {

}

void MainContents::Init() {
  // SetBorder(views::Border::CreateSolidSidedBorder(0, 0, 0, 1, SK_ColorBLACK));
}

}  // namespace downloader
