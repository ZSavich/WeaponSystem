// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/WSAbilitySystemComponent.h"

void UWSAbilitySystemComponent::HandleAbilityInputTag(const FGameplayTag& InputTag, TArray<FGameplayAbilitySpecHandle>& SpecHandles)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				SpecHandles.AddUnique(AbilitySpec.Handle);
				InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
			}
		}
	}
}

void UWSAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	HandleAbilityInputTag(InputTag, InputPressedSpecHandles);
}

void UWSAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	HandleAbilityInputTag(InputTag, InputReleasedSpecHandles);
}
