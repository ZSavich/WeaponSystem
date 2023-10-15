// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WSPlayerController.generated.h"


class UWSAbilitySystemComponent;
class UWSInputComponent;

UCLASS()
class WEAPONSYSTEM_API AWSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWSPlayerController();

protected:
	TWeakObjectPtr<UWSAbilitySystemComponent> AbilitySystemComponentWeak;

public:
	virtual void BeginPlay() override;
	
protected:
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;
};
