// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class UIPROJECT_API IMenuInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//virtual void CheckValid(const FString& UserName, const FString& Password, const FString& EmailAddress,bool CheckBox) = 0;
	virtual void CheckValid(const FString& UserName, const FString& Password, const FString& EmailAddress, bool CheckBox, const FString& Day, const FString& Month, const FString& Year) = 0;
	virtual void Login(const FString& username, const FString& password) = 0;
	virtual void  getdata(const FString& UserName, const FString& Password) = 0;
	virtual void LoadMenu() = 0;
	virtual void LoadLogoutMenu() = 0;
	bool flag = false;
};
