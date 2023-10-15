// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameplayAbilitySpec.h"
#include "WSAbilitySet.generated.h"

class UAbilitySystemComponent;
class UWSGameplayAbility;

/**
 *  FWSAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FWSAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:
	// Gameplay Ability to Grant
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UWSGameplayAbility> Ability;

	// Level of Ability to Grant
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	int32 AbilityLevel = 1;

	// Tag used to Process Input for the Ability
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FWSAbilitySet_GrantedHandles
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void TakeFromAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent);
};

/**
 * UWSAbilitySet
 *
 *	Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS()
class WEAPONSYSTEM_API UWSAbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAbilitySystemComponent* AbilitySystemComponent,
	                         FWSAbilitySet_GrantedHandles* OutGrantedHandles = nullptr,
	                         UObject* SourceObject = nullptr) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", Meta = (TitleProperty = "Ability"))
	TArray<FWSAbilitySet_GameplayAbility> GrantedGameplayAbilities;
};
