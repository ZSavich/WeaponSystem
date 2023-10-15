// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WSPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class WEAPONSYSTEM_API AWSPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWSPlayerState();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UWSAbilitySystemComponent> AbilitySystemComponent;

public:
	UFUNCTION(BlueprintPure, Category = "WeaponSystem")
	UWSAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; };
};
