#include "ViewWidget.h"

#include "ViewHUD.h"

/*
bool UViewWidget::IsOpen()
{
	// By default, open state is defined by visibility, can be overriden for closing animation
	return GetVisibility() != ESlateVisibility::Collapsed
		&& GetVisibility() != ESlateVisibility::Hidden;
}
*/

void UViewWidget::InitializeView()
{
	// When we open UI, by default we set visibility and call BP event
	// If overriden, advisable to use Super
	// We gather and initialize data here
	SetVisibility(ESlateVisibility::Visible);
	//OnInitializeView();
}

void UViewWidget::DeinitializeView()
{
	// When we close UI, by default we set visibility and call BP event
	// If overriden, advisable to use Super
	// We clear out our data here
	SetVisibility(ESlateVisibility::Collapsed);
	//OnDeinitializeView();
}

void UViewWidget::Created()
{
	// Here we can sign up for delegates
	// We can listen to gameplay changes and decide when to open/close this View
	//OnCreated();
}

void UViewWidget::Removed()
{
	// Before we remove it, we call deinit to clean up if open
	//if (IsOpen())
	{
		DeinitializeView();
	}
	// We should clean up any remaining delegates here
	//OnRemoved();
}

void UViewWidget::Refocus()
{
	//OnRefocus();
}

/*
void UViewWidget::OpenThisView()
{
	if (HUDOwner.IsValid())
	{
		HUDOwner->ShowUI(ViewName);
	}
}

void UViewWidget::CloseThisView()
{
	if (HUDOwner.IsValid())
	{
		HUDOwner->HideUI(ViewName);
	}
}

AViewHUD* UViewWidget::GetViewHUD()
{
	return HUDOwner.Get();
}
*/
