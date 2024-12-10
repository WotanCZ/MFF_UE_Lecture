#include "ViewHUD.h"

#include "ProjectShooterBlankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "ViewHolderWidget.h"

bool AViewHUD::PushView(FName ViewName, EViewLayer Layer)
{
	if (ViewClassMap.Contains(ViewName))
	{
		ViewHolderWidget->AddToLayer(ViewClassMap[ViewName], Layer);
		return true;
	}
	
	return false;
}

AProjectShooterBlankPlayerController* AViewHUD::GetShooterPlayerController()
{
	return Cast<AProjectShooterBlankPlayerController>(GetOwningPlayerController());
}

void AViewHUD::BeginPlay()
{
	// Recommended that you call the base function
	Super::BeginPlay();

	// Player controller is the owner of widgets
	// So we need it for widget creation
	TObjectPtr<APlayerController> playerController = GetOwningPlayerController();

	// Create View Holder Widget
	// This creates our custom UI layers
	ViewHolderWidget = CreateWidget<UViewHolderWidget>(playerController, ViewHolderWidgetClass);
	ViewHolderWidget->AddToViewport();
}

void AViewHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// We remove our top Widget with layers from rendering
	// We also mark it for destruction (assigning nullptr)
	if (IsValid(ViewHolderWidget))
	{
		ViewHolderWidget->RemoveFromParent();
		ViewHolderWidget = nullptr;
	}

	// Recommended that you call the base function
	Super::EndPlay(EndPlayReason);
}
