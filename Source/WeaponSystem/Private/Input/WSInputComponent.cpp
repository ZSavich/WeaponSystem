// Fill out your copyright notice in the Description page of Project Settings.

#include "EnhancedInputSubsystems.h"
#include "Input/WSInputComponent.h"
#include "AbilitySystemComponent.h"
#include "NativeGameplayTags.h"
#include "AbilitySystem/WSAbilitySystemComponent.h"

namespace WSGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(InputTag_Move, "InputTag.Move", "Move input.");
}

UWSInputComponent::UWSInputComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

template <class UserClass, typename FuncType>
void UWSInputComponent::BindNativeAction(const UWSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* InputAction = InputConfig->FindNativeInputActionForTag(InputTag))
	{
		BindAction(InputAction, TriggerEvent, Object, MoveTemp(Func));
	}
}

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void UWSInputComponent::BindAbilityActions(const UWSInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc)
{
	check(InputConfig);

	for (const FWSInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag).GetHandle();
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle();
			}
		}
	}
}

void UWSInputComponent::InitializePlayerInputs(UEnhancedInputLocalPlayerSubsystem* Subsystem)
{
	check(Subsystem);

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMapping, 0.f);

	if (InputConfig)
	{
		// Ability Actions
		BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased);

		// Native Actions
		BindNativeAction(InputConfig, WSGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	}
}

void UWSInputComponent::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (OwnerASC.IsValid())
	{
		OwnerASC->AbilityInputTagPressed(InputTag);
	}
}

void UWSInputComponent::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (OwnerASC.IsValid())
	{
		OwnerASC->AbilityInputTagReleased(InputTag);
	}
}

void UWSInputComponent::Input_Move(const FInputActionValue& InputActionValue)
{
	
}
