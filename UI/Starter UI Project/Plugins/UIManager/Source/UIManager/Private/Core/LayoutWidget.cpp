#include "LayoutWidget.h"
#include "CommonUITypes.h"
#include "EnhancedInputSubsystems.h"
#include "MenuWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

UMenuWidget* ULayoutWidget::AddToLayer(TSubclassOf<UMenuWidget> WidgetClass, FGameplayTag LayerTag)
{
	UMenuWidget* AddedWidget = nullptr;
	if (LayerTag.IsValid() && LayerMap.Contains(LayerTag))
	{
		AddedWidget = LayerMap[LayerTag]->AddWidget<UMenuWidget>(WidgetClass);
	}
	
	return AddedWidget;
}

void ULayoutWidget::RemoveFromLayer(UMenuWidget* Menu, FGameplayTag LayerTag)
{
	if (!LayerTag.IsValid() || !LayerMap.Contains(LayerTag) || !IsValid(Menu))
	{
		return;
	}
	
	LayerMap[LayerTag]->RemoveWidget(*Menu);
}

void ULayoutWidget::ClearLayer(FGameplayTag LayerTag)
{
	if (!LayerTag.IsValid() || !LayerMap.Contains(LayerTag))
	{
		return;
	}
	
	LayerMap[LayerTag]->ClearWidgets();
}

void ULayoutWidget::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* ContainerWidget)
{
	if (IsValid(ContainerWidget))
	{
		LayerMap.Add(LayerTag, ContainerWidget);
	}
}

void ULayoutWidget::NativeConstruct()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && RootInputMapping)
	{
		if (const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->AddMappingContext(RootInputMapping, 1000);
			}
		}
	}
	Super::NativeConstruct();
}

void ULayoutWidget::NativeDestruct()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && RootInputMapping)
	{
		if (const ULocalPlayer* LocalPlayer = GetOwningLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				InputSystem->RemoveMappingContext(RootInputMapping);
			}
		}
	}
	Super::NativeDestruct();
}
