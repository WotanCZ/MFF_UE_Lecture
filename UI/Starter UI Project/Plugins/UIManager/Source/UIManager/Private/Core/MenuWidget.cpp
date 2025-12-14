#include "MenuWidget.h"
#include "CommonInputSubsystem.h"

void UMenuWidget::HandleInputMethodChanged(const ECommonInputType CommonInputType)
{
	InputType = CommonInputType;
	OnInputMethodChanged(CommonInputType);
}

bool UMenuWidget::IsGamepadMode()
{
	return InputType == ECommonInputType::Gamepad;
}

bool UMenuWidget::HandleNestedBackNavigation()
{
	if (!bIsBackHandler)
	{
		return BP_OnHandleBackAction();
	}
	return false;
}

void UMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (bStopAllNavigation)
	{
		SetAllNavigationRules(EUINavigationRule::Stop, GetDesiredFocusWidgetName());
	}
}

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (UCommonInputSubsystem* InputSubsystem = GetInputSubsystem())
	{
		InputChangedHandle = InputSubsystem->OnInputMethodChangedNative.AddUObject(this, &UMenuWidget::HandleInputMethodChanged);
		InputType = InputSubsystem->GetCurrentInputType();
	}
}

void UMenuWidget::NativeDestruct()
{
	if (UCommonInputSubsystem* InputSubsystem = GetInputSubsystem())
	{
		if (InputChangedHandle.IsValid())
		{
			InputSubsystem->OnInputMethodChangedNative.Remove(InputChangedHandle);
		}
	}
	Super::NativeDestruct();
}

void UMenuWidget::SynchronizeProperties()
{
	InputMappingPriority = FMath::Max(InputMappingPriority, 1001);
	Super::SynchronizeProperties();
}

void UMenuWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
	BindActions();
}

void UMenuWidget::NativeOnDeactivated()
{
	UnbindActions();
	Super::NativeOnDeactivated();
}

TOptional<FUIInputConfig> UMenuWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
		case EWidgetInputMode::GameAndMenu:
			return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
		case EWidgetInputMode::Game:
			return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
		case EWidgetInputMode::Menu:
			return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
		case EWidgetInputMode::Default:
		default:
			return TOptional<FUIInputConfig>();
	}
}
