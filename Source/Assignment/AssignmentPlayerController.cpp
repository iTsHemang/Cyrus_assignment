// Copyright Epic Games, Inc. All Rights Reserved.


#include "AssignmentPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "AssignmentCameraManager.h"

AAssignmentPlayerController::AAssignmentPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AAssignmentCameraManager::StaticClass();
}

void AAssignmentPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}
