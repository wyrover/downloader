#include "downloader/toolbar_button.h"

#include "ui/events/event.h"
#include "ui/views/border.h"

namespace downloader {

ToolbarButton::ToolbarButton(views::ButtonListener* listener)
    : views::ImageButton(listener) {

}

ToolbarButton::~ToolbarButton() {

}

void ToolbarButton::Layout() {
  SetImageAlignment(views::ImageButton::ALIGN_CENTER,
                    views::ImageButton::ALIGN_MIDDLE);
}

void ToolbarButton::OnMouseEntered(const ui::MouseEvent& event) {
  SetBorder(views::Border::CreateSolidSidedBorder(
                1, 1, 1, 1, SkColorSetRGB(0x3F, 0x3F, 0x3F)));
  SchedulePaint();
}

void ToolbarButton::OnMouseExited(const ui::MouseEvent& event) {
  SetBorder(views::Border::CreateEmptyBorder(0, 0, 0, 0));
  SchedulePaint();
}

void ToolbarButton::OnMouseMoved(const ui::MouseEvent& event) {

}

}  // namespace downloader
