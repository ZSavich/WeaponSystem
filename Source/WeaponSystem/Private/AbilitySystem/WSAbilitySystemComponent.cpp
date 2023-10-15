// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/WSAbilitySystemComponent.h"

#include "WSPlayerState.h"
#include "AbilitySystem/WSAbilitySet.h"
#include "AbilitySystem/Abilities/WSGameplayAbility.h"

void UWSAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(AbilitySet))
	{
		AbilitySet->GiveToAbilitySystem(this);
	}
}

UWSAbilitySystemComponent* UWSAbilitySystemComponent::GetWSAbilitySystemComponentFromController(const AController* Controller)
{
	if (Controller)
	{
		if (const AWSPlayerState* PlayerState = Controller->GetPlayerState<AWSPlayerState>())
		{
			return PlayerState->GetAbilitySystemComponent();
		}
	}
	return nullptr;
}

void UWSAbilitySystemComponent::HandleAbilityInputTag(const FGameplayTag& InputTag, TArray<FGameplayAbilitySpecHandle>& SpecHandles, const bool bIsReleased)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
		{
			if (AbilitySpec.Ability && AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				SpecHandles.AddUnique(AbilitySpec.Handle);
				if (bIsReleased)
				{
					InputHeldSpecHandles.Remove(AbilitySpec.Handle);
				}
				else
				{
					InputHeldSpecHandles.AddUnique(AbilitySpec.Handle);
				}
			}
		}
	}
}

void UWSAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	HandleAbilityInputTag(InputTag, InputPressedSpecHandles, false);
}

void UWSAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	HandleAbilityInputTag(InputTag, InputReleasedSpecHandles, true);
}

void UWSAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();
	
	// Process all Abilities that Activate when the Input is Held
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (const FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability && !AbilitySpec->IsActive())
			{
				const UWSGameplayAbility* AbilityCDO = CastChecked<UWSGameplayAbility>(AbilitySpec->Ability);
				if (AbilityCDO && AbilityCDO->GetActivationPolicy() == EWSAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
				}
			}
		}
	}

	// Process all abilities that had their input pressed this frame
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = true;

				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputPressed(*AbilitySpec);
				}
				else
				{
					const UWSGameplayAbility* AbilityCDO = CastChecked<UWSGameplayAbility>(AbilitySpec->Ability);
					if (AbilityCDO && AbilityCDO->GetActivationPolicy() == EWSAbilityActivationPolicy::OnInputTriggered)
					{
						AbilitiesToActivate.AddUnique(AbilitySpec->Handle);
					}
				}
			}
		}
	}
	
	for (const FGameplayAbilitySpecHandle& SpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(SpecHandle);
	}

	// Process all abilities that had their input released this frame
	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (AbilitySpec->Ability)
			{
				AbilitySpec->InputPressed = false;

				if (AbilitySpec->IsActive())
				{
					AbilitySpecInputReleased(*AbilitySpec);
				}
			}
		}
	}

	// Clear the cached ability handles
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
}

void UWSAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();
}

void UWSAbilitySystemComponent::CancelInputActivatedAbilities()
{
	// Implement CancelAbilitiesByFunc
	// We can't use While Input Active abilities because they can't finished
}
