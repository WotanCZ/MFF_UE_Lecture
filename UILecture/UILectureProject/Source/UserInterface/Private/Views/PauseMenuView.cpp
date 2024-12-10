#include "PauseMenuView.h"
#include "InputAction.h"
#include "Input/CommonUIInputTypes.h"

void UPauseMenuView::BindActions()
{
	if (IsValid(RestartInputAction))
	{
		RestartActionHandle = RegisterUIActionBinding(
			FBindUIActionArgs(
			RestartInputAction,
			true,
			FSimpleDelegate::CreateUObject(this, &UPauseMenuView::OnRestartAction))
			);

		AddActionBinding(RestartActionHandle);
	}
}

void UPauseMenuView::UnbindActions()
{
	RemoveActionBinding(RestartActionHandle);
	RestartActionHandle.Unregister();
}
