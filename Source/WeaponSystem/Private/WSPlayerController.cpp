// Fill out your copyright notice in the Description page of Project Settings.

#include "WSPlayerController.h"

#include "AbilitySystem/WSAbilitySystemComponent.h"

AWSPlayerController::AWSPlayerController()
{
	
}

void AWSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponentWeak = UWSAbilitySystemComponent::GetWSAbilitySystemComponentFromController(this);
}

void AWSPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	if (AbilitySystemComponentWeak.IsValid())
	{
		AbilitySystemComponentWeak->ProcessAbilityInput(DeltaTime, bGamePaused);
	}
	
	Super::PostProcessInput(DeltaTime, bGamePaused);
}
