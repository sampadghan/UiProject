// Fill out your copyright notice in the Description page of Project Settings.


#include "LogoutMenu.h"

bool ULogoutMenu::Initialize()
{
	bool success = Super::Initialize();
	if (!success)
	{
		return false;
	}
	if (!ensure(YesButton != nullptr))
	{
		return false;
	}
	YesButton->OnClicked.AddDynamic(this, &ULogoutMenu::YesPressed);
	NoButton->OnClicked.AddDynamic(this, &ULogoutMenu::NoPressed);
	return true;
}
void ULogoutMenu::Setup()
{
	this->AddToViewport();
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}
void ULogoutMenu::Teardown()
{
	this->RemoveFromViewport();
	UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}
void ULogoutMenu::SetMenuInterface(IMenuInterface* MenuInterfaceParameter)
{
	this->MenuInterface = MenuInterfaceParameter;
}
void ULogoutMenu::NoPressed()
{
	this->RemoveFromViewport();
	//UWidgetLayoutLibrary::RemoveAllWidgets(this);
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}
void ULogoutMenu::YesPressed()
{
	if (MenuInterface != nullptr)
	{
		Teardown();
		MenuInterface->LoadMenu();
	}
}