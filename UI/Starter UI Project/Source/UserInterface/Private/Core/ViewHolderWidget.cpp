#include "ViewHolderWidget.h"
#include "ViewWidget.h"
#include <Components/Overlay.h>
#include <Components/OverlaySlot.h>

void UViewHolderWidget::AddToLayer(UViewWidget* Widget)
{
	/*
	if (!IsValid(Widget)) return;

	UOverlaySlot* addedSlot = nullptr;

	switch (Widget->ViewType)
	{
		case EViewType::HudElement:
			addedSlot = HUDElements->AddChildToOverlay(Widget);
			break;
		case EViewType::Screen:
			addedSlot = Screens->AddChildToOverlay(Widget);
			break;
		case EViewType::Dialog:
			addedSlot = Dialogs->AddChildToOverlay(Widget);
			break;
		default:
			break;
	}

	// We adjust slot layout based on UI configuration
	if (IsValid(addedSlot))
	{
		addedSlot->SetHorizontalAlignment(Widget->SlotHorizontal);
		addedSlot->SetVerticalAlignment(Widget->SlotVertical);
	}
	*/
}
