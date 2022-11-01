// Fill out your copyright notice in the Description page of Project Settings.

#include "UiProjectGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

UUiProjectGameInstance::UUiProjectGameInstance(const FObjectInitializer& ObjectIn)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"));
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_Login2"));
	if (!ensure(MenuBPClass.Class != nullptr))
	{
		return;
	}
	MenuClass = MenuBPClass.Class;
	//searching the LogoutMenu Blueprint
	//WidgetBlueprint'WidgetBlueprint'/Game/MenuSystem/WBP_Logout.WBP_Logout''
	ConstructorHelpers::FClassFinder<UUserWidget> LogoutMenuBPClass(TEXT("/Game/MenuSystem/WBP_Logout"));
	//checking is the LogoutMenuBPClass property is null or not
	if (!ensure(LogoutMenuBPClass.Class != nullptr))
	{
		return;
	}
	LogoutMenuClass = LogoutMenuBPClass.Class;
}
void UUiProjectGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName());
	//if the blueprint is found prints it
	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *LogoutMenuClass->GetName());
}
void UUiProjectGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;

	Menu = CreateWidget<UMainMenu>(this, MenuClass);
	if (!ensure(Menu != nullptr)) return;
	/*
	* //this code is for making mouse clickable in the window
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(Menu->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
	*/
	Menu->Setup();
	//set the Menu to this
	Menu->SetMenuInterface(this);
}
void UUiProjectGameInstance::CheckValid(const FString& UserName, const FString& Password, const FString& EmailAddress, bool CheckBox, const FString& Day, const FString& Month, const FString& Year)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	if (ValidUserName(UserName))
	{
		if (ValidPassword(Password))
		{
			if (CheckBox)
			{
				if (CheckEmail(EmailAddress))
				{
					if (CheckDate(Day, Month, Year))
					{
						Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Creating Account,check your Email Address %s,%s"), *UserName, *EmailAddress));
					}
					else
					{
						Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Please enter valid Date of Birth %s,%s"), *UserName, *EmailAddress));
					}
				}
				else
				{
					Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Enter valid Email Address %s,%s"), *UserName, *EmailAddress));
				}
			}
			else
			{
				Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Please accept the terms %s,%s"), *UserName, *EmailAddress));
			}
		}
		else
		{
			Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Password must be greater than 8 and must contain Alphabet(Lower and Upper),Numbers,Special Chars")));
		}
	}
	else
	{
		Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Please enter valid username,example:firstname_lastname")));
	}
}
bool UUiProjectGameInstance::CheckEmail(const FString& EmailAddress)
{
	const FRegexPattern myPattern(TEXT("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+"));
	FRegexMatcher myMatcher(myPattern, EmailAddress);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::ValidUserName(const FString& UserName)
{
	const FRegexPattern myPattern(TEXT("^(?=.{8,20}$)(?![_.])(?!.*[_.]{2})[a-zA-Z0-9._]+(?<![_.])$"));
	FRegexMatcher myMatcher(myPattern, UserName);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::ValidPassword(const FString& Password)
{
	const FRegexPattern myPattern(TEXT("^(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[!@#&()–[{}]:;',?/*~$^+=<>]).{8,20}$"));
	FRegexMatcher myMatcher(myPattern, Password);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::IsDayValid(const FString& Day)
{
	const FRegexPattern myPattern(TEXT("^(3[01]|[12][0-9]|[1-9])$"));
	FRegexMatcher myMatcher(myPattern, Day);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		UE_LOG(LogTemp, Warning, TEXT("Matched"));
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::IsMonthValid(const FString& Month)
{
	const FRegexPattern myPattern(TEXT("^(1[0-2]|[1-9])$"));
	FRegexMatcher myMatcher(myPattern, Month);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		UE_LOG(LogTemp, Warning, TEXT("Matched"));
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::IsYearValid(const FString& Year)
{
	const FRegexPattern myPattern(TEXT("(19[56789]\\d|20[01]\\d)"));
	FRegexMatcher myMatcher(myPattern, Year);
	if (myMatcher.FindNext())
	{
		int32 b = myMatcher.GetMatchBeginning();
		int32 e = myMatcher.GetMatchEnding();
		UE_LOG(LogTemp, Warning, TEXT("REGEX %i %i"), b, e);
		UE_LOG(LogTemp, Warning, TEXT("Matched"));
		return true;
	}
	return false;
}
bool UUiProjectGameInstance::CheckDate(const FString& Day, const FString& Month, const FString& Year)
{
	if (IsDayValid(Day))
	{
		if (IsMonthValid(Month))
		{
			if (IsYearValid(Year))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return false;
}
void UUiProjectGameInstance::Login(const FString& username, const FString& password)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr))
	{
		return;
	}
	//FString username1 = FString(TEXT("Admin"));
	//FString password1 = FString(TEXT("Password@123"));
	if (username == sessionusername)
	{
		if (password == sessionpassword)
		{
			Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Logining in just wait a bit")));
			flag = true;
		}
		else
		{
			Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Incorrect password")));
			flag = false;
		}
	}
	else
	{
		Engine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Incorrect username")));
		flag = false;
	}
}
void UUiProjectGameInstance::getdata(const FString& UserName, const FString& Password)
{
	sessionusername = UserName;
	sessionpassword = Password;
}
void UUiProjectGameInstance::LoadLogoutMenu()
{
	//check first LogoutMenuClass is null or not
	if (!ensure(LogoutMenuClass != nullptr)) return;
	LogoutMenu = CreateWidget<ULogoutMenu>(this, LogoutMenuClass);
	if (!ensure(LogoutMenu != nullptr)) return;
	LogoutMenu->Setup();
	//set the Menu to this
	LogoutMenu->SetMenuInterface(this);
}