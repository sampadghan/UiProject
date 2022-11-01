// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MenuInterface.h"
#include "Components/Button.h"
#include "MenuSystem/MainMenu.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "LogoutMenu.generated.h"

/**
 * 
 */
UCLASS()
class UIPROJECT_API ULogoutMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetMenuInterface(IMenuInterface* MenuInterfaceParameter);
	void Setup();
	void Teardown();

protected:
	IMenuInterface* MenuInterface;
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* YesButton;

	UPROPERTY(meta = (BindWidget))
		class UButton* NoButton;

	UFUNCTION()
		void NoPressed();

	UFUNCTION()
		void YesPressed();
};
