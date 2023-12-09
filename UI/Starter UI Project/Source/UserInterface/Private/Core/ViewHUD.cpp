#include "ViewHUD.h"

#include "EnhancedInputSubsystems.h"
#include "ProjectShooterBlankPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "ViewWidget.h"
#include "ViewHolderWidget.h"
#include "Components/Overlay.h"
#include "InputMappingContext.h"

bool AViewHUD::ShowUI(FName ViewName)
{
	/*
	// Get View by identificator
	UViewWidget* view = GetViewByName(ViewName);

	// Check for validity
	if (!IsValid(view)) return false;

	// Save the current internal status of UI
	const bool bHadInput = IsScreenOpen() || IsDialogOpen();

	// Get the UI type and change the internal status accordingly
	EViewType viewType = view->ViewType;

	switch (viewType)
	{
	case EViewType::Screen:
		CurrentScreenName = ViewName;
		break;
	case EViewType::Dialog:
		OpenDialogStack.AddUnique(ViewName);
		break;
	default:
		break;
	}

	// Save new internal status of UI
	const bool bHasInput = IsScreenOpen() || IsDialogOpen();

	// If the status has changed, update input mode
	if (bHadInput != bHasInput)
	{
		UpdateGameAndInputMode();
	}

	// Open the UI
	view->InitializeView();

	// Refocus if needed
	if (viewType != EViewType::HudElement)
	{
		Refocus();
	}
	*/
	// Success
	return true;
}

bool AViewHUD::HideUI(FName ViewName)
{
	/*
	// Get View by identificator
	UViewWidget* view = GetViewByName(ViewName);

	// Check for validity
	if (!IsValid(view)) return false;

	// Save the current internal status of UI
	bool bHadInput = IsScreenOpen() || IsDialogOpen();
	
	// Get the UI type and change the internal status accordingly
	EViewType viewType = view->ViewType;

	switch (viewType)
	{
	case EViewType::Screen:
		CurrentScreenName = FName();
		break;
	case EViewType::Dialog:
		OpenDialogStack.Remove(ViewName);
		break;
	default:
		break;
	}

	// Save new internal status of UI
	bool bHasInput = IsScreenOpen() || IsDialogOpen();

	// If the status has changed, update input mode
	if (bHadInput != bHasInput)
	{
		UpdateGameAndInputMode();
	}

	// Close the UI
	view->DeinitializeView();

	// Refocus if needed
	if (viewType != EViewType::HudElement)
	{
		Refocus();
	}
	*/
	// Success
	return true;
}

/*
bool AViewHUD::IsScreenOpen()
{
	return !CurrentScreenName.IsNone();
}

bool AViewHUD::IsDialogOpen()
{
	return !OpenDialogStack.IsEmpty();
}

bool AViewHUD::IsViewOpen(FName ViewName)
{
	// Get View by identificator
	UViewWidget* view = GetViewByName(ViewName);

	if (!IsValid(view)) return false;
	
	return view->IsOpen();
}
*/

AProjectShooterBlankPlayerController* AViewHUD::GetShooterPlayerController()
{
	return Cast<AProjectShooterBlankPlayerController>(GetOwningPlayerController());
}

/*
void AViewHUD::Refocus()
{
	// While refocusing, we need to change input context
	// So we prepare access to the controller and input context
	APlayerController* controller = GetOwningPlayerController();
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer());

	// We remove current UI input contexts
	// In our game, only one UI at a time can process input and navigation
	for (auto ViewPair: ViewMap)
	{
		UViewWidget* viewValue = ViewPair.Value;
		if (IsValid(viewValue) && IsValid(viewValue->ViewInputContext))
		{
			subsystem->RemoveMappingContext(viewValue->ViewInputContext);
		}
	}

	FName viewToFocus = FName();

	// We check for the last open dialog
	if (IsDialogOpen())
	{
		viewToFocus = OpenDialogStack.Last();
	}
	// If no dialog, let's check screen
	else if (IsScreenOpen())
	{
		viewToFocus = CurrentScreenName;
	}

	// Get top View from internal state and refocus it
	const UViewWidget* view = GetViewByName(viewToFocus);
	
	if (!IsValid(view))
	{
		return;
	}
	
	view->Refocus();

	// Top View gets the honor of activating it's input context
	if (IsValid(view->ViewInputContext))
	{
		subsystem->AddMappingContext(view->ViewInputContext, 20);
	}
}
*/

void AViewHUD::BeginPlay()
{
	// Recommended that you call the base function
	Super::BeginPlay();

	/*
	// Player controller is the owner of widgets
	// So we need it for widget creation
	APlayerController* playerController = GetOwningPlayerController();

	// Create View Holder Widget
	// This creates our custom UI layers
	ViewHolderWidget = CreateWidget<UViewHolderWidget>(playerController, ViewHolderWidgetClass);
	ViewHolderWidget->AddToViewport();
    
	ViewMap.Empty();
	
	// Create View Widgets
	// Initialize link to this actor
	// Map the Widget
	// Add to layer
	for (TSubclassOf<UViewWidget>& viewClass : ViewClasses)
	{
		UViewWidget* view = CreateWidget<UViewWidget>(playerController, viewClass);

		view->HUDOwner = this;

		ViewMap.Add(view->ViewName, view);
		
		ViewHolderWidget->AddToLayer(view);

		view->SetVisibility(ESlateVisibility::Collapsed);
	}

	TArray<UViewWidget*> widgets;
	ViewMap.GenerateValueArray(widgets);
	
	bIsInitialized = true;

	// We call creation events for each widget
	// So we can hook them up to gameplay events
	for (UViewWidget*& view : widgets)
	{
		if (IsValid(view)) 
		{
			view->Created();
		}
	}
	
	UpdateGameAndInputMode();

	// At this point we can assume that UI can be safely interacted with
	OnViewsInitialized();
	*/
}

void AViewHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	/*
	TArray<UViewWidget*> widgets;
	ViewMap.GenerateValueArray(widgets);

	// We call destroy events on every Widget
	for (UViewWidget*& view : widgets)
	{
		if (IsValid(view))
		{
			view->Removed();
		}
	}
	
	ViewMap.Empty();

	// We remove our top Widget with layers from rendering
	// We also mark it for destruction (assigning nullptr)
	if (IsValid(ViewHolderWidget))
	{
		ViewHolderWidget->RemoveFromParent();
		ViewHolderWidget = nullptr;
	}
	*/

	// Recommended that you call the base function
	Super::EndPlay(EndPlayReason); 
}

/*
void AViewHUD::UpdateGameAndInputMode()
{
	// While changing UI state, we need to change input context
	// So we prepare access to the controller and input context
	APlayerController* controller = GetOwningPlayerController();
	UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer());
	
	if (IsScreenOpen() || IsDialogOpen())
	{
		// We adjust the context
		subsystem->AddMappingContext(GenericUIContext, 10);
		subsystem->RemoveMappingContext(GameplayUIContext);

		// We set new input mode
		// This will give us access to pointer device (like mouse)
		controller->SetInputMode(FInputModeGameAndUI());

		// We pause the game and hide HUD layer
		controller->SetPause(true);
		// This will hide HUD layer independently of visibility of HUD elements
		ViewHolderWidget->HUDElements->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		// We adjust the context
		subsystem->AddMappingContext(GameplayUIContext, 10);
		subsystem->RemoveMappingContext(GenericUIContext);
		
		// We set new input mode
		// Back to gameplay (this will hide the mouse)
		controller->SetInputMode(FInputModeGameOnly());

		// We unpause the game are show HUD layer
		controller->SetPause(false);
		// This will show back our HUD layer, but it ignores raycast hits for click events
		// Our game doesn't need pointer interactions with HUD layer (saves performance)
		ViewHolderWidget->HUDElements->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}
*/

UViewWidget* AViewHUD::GetViewByName(FName ViewName)
{
	// We will allow manipulation only after all views are initialized
	// If the identificator is not registered, we return nullptr
	if (!bIsInitialized || !ViewMap.Contains(ViewName)) return nullptr;

	// We return proper Widget object
	return ViewMap[ViewName];
}

