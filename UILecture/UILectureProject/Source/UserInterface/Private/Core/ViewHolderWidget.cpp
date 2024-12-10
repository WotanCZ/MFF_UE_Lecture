#include "ViewHolderWidget.h"
#include "ViewWidget.h"
#include "ViewHUD.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UViewWidget* UViewHolderWidget::AddToLayer(TSubclassOf<UViewWidget> WidgetClass, EViewLayer ViewType)
{
	UViewWidget* addedWidget = nullptr;

	switch (ViewType)
	{
		case EViewLayer::Screen:
			addedWidget = Screens->AddWidget<UViewWidget>(WidgetClass);
			break;
		case EViewLayer::Dialog:
			addedWidget = Dialogs->AddWidget<UViewWidget>(WidgetClass);
			break;
		default:
			break;
	}
	
	return addedWidget;
}

bool UViewHolderWidget::GetInputValidation()
{
	return (Dialogs->GetNumWidgets() || Screens->GetNumWidgets());
}

void UViewHolderWidget::ValidateInput(UCommonActivatableWidget* Widget)
{
	if (GetInputValidation())
	{
		GetOwningPlayer()->SetInputMode(FInputModeUIOnly());
		GetOwningPlayer()->SetShowMouseCursor(true);
	}
	else
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer()->SetShowMouseCursor(false);
	}
}

void UViewHolderWidget::NativeConstruct()
{
	if (IsValid(Screens) && IsValid(Dialogs))
	{
		ScreenChangeHandle = Screens->OnDisplayedWidgetChanged().AddUObject(this, &UViewHolderWidget::ValidateInput);
		DialogChangeHandle = Dialogs->OnDisplayedWidgetChanged().AddUObject(this, &UViewHolderWidget::ValidateInput);
	}
	ValidateInput(nullptr);
	Super::NativeConstruct();
}

void UViewHolderWidget::NativeDestruct()
{
	if (IsValid(Screens) && ScreenChangeHandle.IsValid())
	{
		Screens->OnDisplayedWidgetChanged().Remove(ScreenChangeHandle);
	}
	if (IsValid(Dialogs) && DialogChangeHandle.IsValid())
	{
		Dialogs->OnDisplayedWidgetChanged().Remove(DialogChangeHandle);
	}
	GetOwningPlayer()->SetShowMouseCursor(true);
	Super::NativeDestruct();
}
