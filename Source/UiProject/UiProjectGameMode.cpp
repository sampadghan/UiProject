// Copyright Epic Games, Inc. All Rights Reserved.

#include "UiProjectGameMode.h"
#include "UiProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUiProjectGameMode::AUiProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
