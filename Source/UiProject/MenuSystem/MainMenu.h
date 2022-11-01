// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "MenuInterface.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class UIPROJECT_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* MenuInterfacePara);
	void Teardown();
	void Setup();

protected:
	virtual bool Initialize() override;
	IMenuInterface* MenuInterface;
private:
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* UserNameField;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* PasswordField;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* EmailAddressField;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* DayField;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* MonthField;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* YearField;
	//Login username
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* LogInUserNameField;
	//Login password
	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* LogInPasswordField;
	//ButtonCreateMyAccount
	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonCreateMyAccount;
	//ButtonAccountExistLogIn
	UPROPERTY(meta = (BindWidget))
		class UButton* ButtonAccountExistLogIn;
	//checkbox
	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBoxAgree;

	UPROPERTY(meta = (BindWidget))
		class UCheckBox* CheckBoxSignUp;
	UFUNCTION()
		void CreateMyAccount();
	//MenuSwitcher
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;
	//LoginMenu
	UPROPERTY(meta = (BindWidget))
		class UWidget* LoginMenu;
	//SignUpMenu
	UPROPERTY(meta = (BindWidget))
		class UWidget* SignUpMenu;
	//SignUpButton
	UPROPERTY(meta = (BindWidget))
		class UButton* SignUpButton;
	//LoginButton
	UPROPERTY(meta = (BindWidget))
		class UButton* LoginButton;
	//Open SignUpMenu
	UFUNCTION()
		void OpenSignUpMenu();
	//Open LoginMenu
	UFUNCTION()
		void OpenLoginMenu();
	//open logout popup
	UFUNCTION()
		void OpenLoginoutPopup();
	//Open HomeMenu
	UFUNCTION()
		void OpenHomeMenu();
	//Login Function
	UFUNCTION()
		void MainMenuLogin();
	//HomeMenu
	UPROPERTY(meta = (BindWidget))
		class UWidget* HomeMenu;
	//LogoutButton
	UPROPERTY(meta = (BindWidget))
		class UButton* LogOutButton;
	//HomeUserName
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* HomeUserName;
};
