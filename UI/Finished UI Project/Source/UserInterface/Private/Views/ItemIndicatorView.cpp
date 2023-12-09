#include "ItemIndicatorView.h"
#include "ViewHUD.h"
#include "GameFramework/PlayerController.h"
#include "ProjectShooterBlankCharacter.h"
#include "ProjectShooterBlankPlayerController.h"

void UItemIndicatorView::ItemPickedUp()
{
	AProjectShooterBlankCharacter* character = GetPlayerCharacter();
	if (IsValid(character))
	{
		OnItemChanged(character->bHasRifle);
	}
}

void UItemIndicatorView::RifleFired()
{
	OnRifleFired();
}

AProjectShooterBlankCharacter* UItemIndicatorView::GetPlayerCharacter()
{
	AViewHUD* viewHUD = GetViewHUD();
	if (!IsValid(viewHUD)) return nullptr;

	AProjectShooterBlankPlayerController* player = viewHUD->GetShooterPlayerController();
	if (!IsValid(player)) return nullptr;
	
	return Cast<AProjectShooterBlankCharacter>(player->GetCharacter());
}

void UItemIndicatorView::InitializeView()
{
	Super::InitializeView();

	AProjectShooterBlankCharacter* playerCharacter = GetPlayerCharacter();

	if (IsValid(playerCharacter))
	{
		ItemPickHandle = playerCharacter->OnItemPickedUp.AddUObject(this, &UItemIndicatorView::ItemPickedUp);
		RifleFiredHandle = playerCharacter->OnRifleFired.AddUObject(this, &UItemIndicatorView::RifleFired);
	}
}

void UItemIndicatorView::DeinitializeView()
{
	Super::DeinitializeView();

	AProjectShooterBlankCharacter* playerCharacter = GetPlayerCharacter();

	if (IsValid(playerCharacter))
	{
		playerCharacter->OnItemPickedUp.Remove(ItemPickHandle);
		playerCharacter->OnRifleFired.Remove(RifleFiredHandle);
	}
}

void UItemIndicatorView::Created()
{
	Super::Created();
	OpenThisView();
}
