#include "GameHUD.h"
#include "GameFramework/PlayerController.h"
#include "LayoutWidget.h"

UMenuWidget* AGameHUD::AddMenuToLayer(TSubclassOf<UMenuWidget> MenuClass, FGameplayTag LayerTag)
{
	if (!IsValid(LayoutWidget))
	{
		return nullptr;
	}
	
	return LayoutWidget->AddToLayer(MenuClass, LayerTag);
}

void AGameHUD::RemoveMenu(UMenuWidget* Menu, FGameplayTag LayerTag)
{
	if (!IsValid(LayoutWidget))
	{
		return;
	}
	
	LayoutWidget->RemoveFromLayer(Menu, LayerTag);
}

void AGameHUD::ClearLayer(FGameplayTag LayerTag)
{
	if (!IsValid(LayoutWidget))
	{
		return;
	}
	LayoutWidget->ClearLayer(LayerTag);
}

void AGameHUD::BeginPlay()
{
	// Player controller is the owner of widgets
	// So we need it for widget creation
	TObjectPtr<APlayerController> PlayerController = GetOwningPlayerController();

	// Create Layouting Widget
	// This creates our custom UI layers
	LayoutWidget = CreateWidget<ULayoutWidget>(PlayerController, LayoutClass);
	LayoutWidget->AddToViewport();
	
	// Recommended that you call the base function
	Super::BeginPlay();

	OnGameHUDReady.Broadcast();
}

void AGameHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// We remove our top Widget with layers from rendering
	// We also mark it for destruction (assigning nullptr)
	if (IsValid(LayoutWidget))
	{
		LayoutWidget->RemoveFromParent();
		LayoutWidget = nullptr;
	}

	// Recommended that you call the base function
	Super::EndPlay(EndPlayReason);
}

/*static*/ UMenuWidget* AGameHUD::PushMenuToLayer(const APlayerController* PlayerController, FGameplayTag LayerTag, TSubclassOf<UMenuWidget> MenuClass)
{
	if (!IsValid(PlayerController))
	{
		return nullptr;
	}

	AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());

	if(!IsValid(GameHUD))
	{
		return nullptr;
	}
	
	return GameHUD->AddMenuToLayer(MenuClass, LayerTag);
}


/*static*/ void AGameHUD::RemoveMenuFromLayer(const APlayerController* PlayerController, FGameplayTag LayerTag, UMenuWidget* Menu)
{
	if (!IsValid(PlayerController))
	{
		return;
	}

	AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());

	if(!IsValid(GameHUD))
	{
		return;
	}
	
	GameHUD->RemoveMenu(Menu, LayerTag);
}

/*static*/ void AGameHUD::ClearMenuLayer(const APlayerController* PlayerController, FGameplayTag LayerTag)
{
	if (!IsValid(PlayerController))
	{
		return;
	}

	AGameHUD* GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());

	if(!IsValid(GameHUD))
	{
		return;
	}
	
	GameHUD->ClearLayer(LayerTag);
}
