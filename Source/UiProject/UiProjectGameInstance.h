// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "MenuSystem/MainMenu.h"
#include "LogoutMenu.h"
#include "UiProjectGameInstance.generated.h"

/**
 *
 */
UCLASS()
class UIPROJECT_API UUiProjectGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
public:
	//constructor
	UUiProjectGameInstance(const FObjectInitializer& ObjectIn);
	virtual void Init();
	UFUNCTION(Exec)
		//void CheckValid(const FString& UserName, const FString& Password, const FString& EmailAddress, bool CheckBox);
		void CheckValid(const FString& UserName, const FString& Password, const FString& EmailAddress, bool CheckBox, const FString& Day, const FString& Month, const FString& Year);
	//check date
	UFUNCTION(Exec)
		bool CheckDate(const FString& Day, const FString& Month, const FString& Year);
	//Day Validation
	UFUNCTION(Exec)
		bool IsDayValid(const FString& Day);
	//Month Validation
	UFUNCTION(Exec)
		bool IsMonthValid(const FString& Month);
	//Year Validation
	UFUNCTION(Exec)
		bool IsYearValid(const FString& Year);
	//call load Menu
	UFUNCTION(BlueprintCallable)
		void LoadMenu();
	//if username and password correct login
	UFUNCTION(Exec)
		void Login(const FString& username, const FString& password);
	//check is email valid or not
	bool CheckEmail(const FString& EmailAddress);
	//check is UserName is valid or not
	bool ValidUserName(const FString& UserName);
	//check is password is valid or not
	bool ValidPassword(const FString& Password);
	//store username variable
	FString sessionusername;
	//store password variable
	FString sessionpassword;
	//store data from MainMenu 
	UFUNCTION(Exec)
		void  getdata(const FString& UserName, const FString& Password);
	//Load Logout pop menu
	UFUNCTION(Exec)
		void LoadLogoutMenu();
private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> LogoutMenuClass;
	class UMainMenu* Menu;
	class ULogoutMenu* LogoutMenu;
};
