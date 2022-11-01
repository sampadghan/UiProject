// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/CheckBox.h"
#include "Components/EditableTextBox.h"
bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}
	if (!ensure(ButtonCreateMyAccount != nullptr))
	{
		return false;
	}
	//check the host button null or not
	ButtonCreateMyAccount->OnClicked.AddDynamic(this, &UMainMenu::CreateMyAccount);
	ButtonAccountExistLogIn->OnClicked.AddDynamic(this, &UMainMenu::OpenLoginMenu);
	SignUpButton->OnClicked.AddDynamic(this, &UMainMenu::OpenSignUpMenu);
	LoginButton->OnClicked.AddDynamic(this, &UMainMenu::OpenHomeMenu);
	LogOutButton->OnClicked.AddDynamic(this, &UMainMenu::OpenLoginoutPopup);
	return true;
}

void UMainMenu::CreateMyAccount()
{
	UE_LOG(LogTemp, Warning, TEXT("Account button pressed"));
	if (MenuInterface != nullptr)
	{
		if (!ensure(UserNameField != nullptr)) return;
		if (!ensure(PasswordField != nullptr)) return;
		if (!ensure(EmailAddressField != nullptr)) return;
		if (!ensure(CheckBoxAgree != nullptr)) return;
		if (!ensure(DayField != nullptr)) return;
		if (!ensure(MonthField != nullptr)) return;
		if (!ensure(YearField != nullptr)) return;
		const FString& UserName = UserNameField->GetText().ToString();
		const FString& Password = PasswordField->GetText().ToString();
		const FString& EmailAddress = EmailAddressField->GetText().ToString();
		const FString& Day = DayField->GetText().ToString();
		const FString& Month = MonthField->GetText().ToString();
		const FString& Year = YearField->GetText().ToString();
		bool CheckBox = CheckBoxAgree->IsChecked();
		//session username and password of the sign up menu
		MenuInterface->getdata(UserName, Password);
		MenuInterface->CheckValid(UserName, Password, EmailAddress, CheckBox, Day, Month, Year);
	}
}
void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterfacePara)
{
	this->MenuInterface = MenuInterfacePara;
}
void UMainMenu::OpenSignUpMenu()
{
	if(!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(SignUpMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(SignUpMenu);
}
void UMainMenu::OpenLoginMenu()
{
	//MenuInterface->LoadLogoutMenu();
	if (!ensure(MenuSwitcher != nullptr))
	{
		return;
	}
	if (!ensure(LoginMenu != nullptr))
	{
		return;
	}
	MenuSwitcher->SetActiveWidget(LoginMenu);
}
void UMainMenu::MainMenuLogin()
{
	UE_LOG(LogTemp, Warning, TEXT("Account button pressed"));
	if (MenuInterface != nullptr)
	{
		if (MenuInterface->flag)
		{
			if (!ensure(MenuSwitcher != nullptr))
			{
				return;
			}
			if (!ensure(HomeMenu != nullptr))
			{
				return;
			}
			MenuSwitcher->SetActiveWidget(HomeMenu);
		}
	}
}
void UMainMenu::OpenHomeMenu()
{
	if (!ensure(LogInUserNameField != nullptr)) return;
	if (!ensure(LogInPasswordField != nullptr)) return;
	const FString& UserName = LogInUserNameField->GetText().ToString();
	const FString& Password = LogInPasswordField->GetText().ToString();
	MenuInterface->Login(UserName,Password);
	if (MenuInterface->flag)
	{
		if (!ensure(MenuSwitcher != nullptr))
		{
			return;
		}
		if (!ensure(HomeMenu != nullptr))
		{
			return;
		}
		if (!ensure(HomeUserName != nullptr))
		{
			return;
		}
		HomeUserName->SetText(LogInUserNameField->GetText());
		MenuSwitcher->SetActiveWidget(HomeMenu);
	}
}
void UMainMenu::OpenLoginoutPopup()
{
	MenuInterface->LoadLogoutMenu();
}
void UMainMenu::Teardown()
{
	this->RemoveFromViewport();

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	PlayerController->bShowMouseCursor = true;
}
void UMainMenu::Setup()
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