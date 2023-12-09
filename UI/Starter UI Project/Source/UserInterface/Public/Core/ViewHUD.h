#pragma once

#include "UserInterfaceModule.h"
#include <GameFramework/HUD.h>

#include "ViewHUD.generated.h"

class UViewWidget;
class UViewHolderWidget;
class AProjectShooterBlankPlayerController;
class UInputMappingContext;

UCLASS(Blueprintable, NotBlueprintType)
class USERINTERFACE_API AViewHUD : public AHUD
{
	GENERATED_BODY()

public: // Blueprint Config

	// Our widget with layers for the rest of the UI
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<UViewHolderWidget> ViewHolderWidgetClass;

	// This stores types of UI View Widgets we want to instantiate
	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TArray<TSubclassOf<UViewWidget>> ViewClasses;
	
protected: // View Storage

	UViewWidget* GetViewByName(FName ViewName);

	// Our UI will be stored in a Map
	// So it can be pulled by it's unique identificator
	UPROPERTY(Transient)
	TMap<FName, UViewWidget*> ViewMap;

	// Access to Main Layer Widget
	UPROPERTY(Transient)
	UViewHolderWidget* ViewHolderWidget;

public:

	// Shows desired UI
	UFUNCTION(BlueprintCallable)
	bool ShowUI(FName ViewName);

	// Hides desired UI
	UFUNCTION(BlueprintCallable)
	bool HideUI(FName ViewName);

protected: // Actor overrides

	// We create our UI here
	virtual void BeginPlay() override;

	// We destroy our UI here
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:

	/*
	// Detects open Screen
	UFUNCTION(BlueprintCallable)
	bool IsScreenOpen();

	// Detects open Dialogs
	UFUNCTION(BlueprintCallable)
	bool IsDialogOpen();

	// We can check for open/close state of specific UI
	UFUNCTION(BlueprintCallable)
	bool IsViewOpen(FName ViewName);
	*/

	// Returns custom player controller class object
	UFUNCTION(BlueprintCallable)
	AProjectShooterBlankPlayerController* GetShooterPlayerController();

protected: // Internal State

	/*
	// Since there can be only one screen at a time
	// We hold current one
	UPROPERTY(BlueprintReadOnly)
	FName CurrentScreenName;

	// Currently open dialogs
	UPROPERTY(BlueprintReadOnly)
	TArray<FName> OpenDialogStack;
	*/

public: // Blueprint Events

	// Called when Views are instantiated and all creation events called
	UFUNCTION(BlueprintImplementableEvent)
	void OnViewsInitialized();

protected: // Input Mode

	/*
	// This context will be used for UI shortcuts during gameplay
	// E.g.: Pause Menu, Inventory, Journal, etc.
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* GameplayUIContext;

	// This context will be used for generic shortcuts during UI
	// E.g.: Close, Back, Reload, etc.
	UPROPERTY(EditDefaultsOnly)
	UInputMappingContext* GenericUIContext;

	void UpdateGameAndInputMode();
	*/

public: // View Management

	// Checks the top rendered UI and refocuses it
	void Refocus();

protected:

	bool bIsInitialized = false;
};