// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WSGameplayAbility.generated.h"

/**
 * EWSAbilityActivationPolicy
 *
 *	Defines how an ability is meant to activate.
 */
UENUM()
enum class EWSAbilityActivationPolicy : uint8
{
	OnInputTriggered	UMETA(DisplayName = "On Input Triggered"),
	WhileInputActive	UMETA(DisplayName = "While Input Active"),
	OnSpawn				UMETA(DisplayName = "On Spawn")
};

UCLASS(Abstract)
class WEAPONSYSTEM_API UWSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponSystem|AbilityActivation")
	EWSAbilityActivationPolicy ActivationPolicy;

public:
	EWSAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
};
