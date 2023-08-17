// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "WSInputConfig.generated.h"

class UInputAction;

/**
 * FInputAction
 *
 *	Struct used to map a input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FWSInputAction
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};

/**
 * UInputConfig
 *
 *	Data asset that contains input configuration properties.
 */
UCLASS(BlueprintType, Const) // ToDo::Need find out why Const 
class WEAPONSYSTEM_API UWSInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Input actions are mapped to gameplay tags, that require manual binding.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWSInputAction> NativeInputActions;

	// Input actions are mapped to gameplay tags and automatically bound to matching abilities.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWSInputAction> AbilityInputActions;
	
public:
	// Find a native input action based on the provided gameplay tag.
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;

	// Find an ability input action based on the provided gameplay tag.
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;

protected:
	// Find and return the input action associated with the given gameplay tag.
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag, const TArray<FWSInputAction>& InputActions) const;
};
