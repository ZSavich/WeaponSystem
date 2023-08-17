// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/WSInputConfig.h"


const UInputAction* UWSInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag) const
{
	return FindInputActionForTag(InputTag, NativeInputActions);
}

const UInputAction* UWSInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	return FindInputActionForTag(InputTag, AbilityInputActions);
}

const UInputAction* UWSInputConfig::FindInputActionForTag(const FGameplayTag& InputTag, const TArray<FWSInputAction>& InputActions) const
{
	for (const FWSInputAction& Action : InputActions)
	{
		if (Action. InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}
	return nullptr;
}
