#ifndef DOWNLOADER_MAIN_CONTENTS_H_
#define DOWNLOADER_MAIN_CONTENTS_H_

#include "downloader/downloader_export.h"
#include "ui/views/view.h"

namespace downloader {

class DOWNLOADER_EXPORT MainContents : public views::View {
public:
  MainContents();
  ~MainContents() override;

private:
  void Init();
};

}  // namespace downloader

#endif  // DOWNLOADER_MAIN_CONTENTS_H_
