#pragma once

#include "UserInterfaceModule.h"
#include "Blueprint/UserWidget.h"
#include "ViewWidget.generated.h"

class AViewHUD;
class UInputMappingContext;

// We define different UI types
// We can use different management rules based on the type
UENUM(BlueprintType)
enum class EViewType : uint8
{
	HudElement			UMETA(DisplayName = "HUD"),
	Screen				UMETA(DisplayName = "Screen"),
	Dialog				UMETA(DisplayName = "Dialog")
};

UCLASS(Abstract, Blueprintable)
class USERINTERFACE_API UViewWidget : public UUserWidget
{
	GENERATED_BODY()

	// This ensures that ViewHUD actor (UI Manager) can manipulate even private properties
	// Inherited classes will be more restricted by design
	friend class AViewHUD;

public: // View Properties

	// Defines UI Type
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View Setup")
	EViewType ViewType;

	// Defines a unique UI identificator
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View Setup")
	FName ViewName;

public: // Layout Properties
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View Layout")
	TEnumAsByte<EHorizontalAlignment> SlotHorizontal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View Layout")
	TEnumAsByte<EVerticalAlignment> SlotVertical;

public: // Input Context

	// Input context that will be active while this UI is in focus
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="View Input")
	TObjectPtr<UInputMappingContext> ViewInputContext;
	
protected: // Blueprint Events

	// Creates a Blueprint event on open
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitializeView();

	// Creates a Blueprint event on close
	UFUNCTION(BlueprintImplementableEvent)
	void OnDeinitializeView();

	// Creates a Blueprint event on creation
	UFUNCTION(BlueprintImplementableEvent)
	void OnCreated();

	// Creates a Blueprint event on destruction
	UFUNCTION(BlueprintImplementableEvent)
	void OnRemoved();

	// Creates a Blueprint event on refocus
	UFUNCTION(BlueprintImplementableEvent)
	void OnRefocus();

protected: // Internal overridable events

	// Is called on open
	virtual void InitializeView();

	// Is called on close
	virtual void DeinitializeView();

	// Is called on creation
	virtual void Created();

	// Is called on destruction
	virtual void Removed();

	// Is called on refocus
	virtual void Refocus();
	
protected:

	// Calls for opening of this UI
	UFUNCTION(BlueprintCallable)
	void OpenThisView();

	// Calls for closing of this UI
	UFUNCTION(BlueprintCallable)
	void CloseThisView();

	UFUNCTION(BlueprintCallable)
	virtual bool IsOpen();

	UFUNCTION(BlueprintCallable)
	AViewHUD* GetViewHUD();

private:

	// This is a weak link to the HUD actor (UI Manager)
	// It is private so it can't be manipulated, getter is protected
	TWeakObjectPtr<AViewHUD> HUDOwner;
};