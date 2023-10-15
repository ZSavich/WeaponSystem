// Fill out your copyright notice in the Description page of Project Settings.

#include "WSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayEffectTypes.h"
#include "InputActionValue.h"
#include "AbilitySystem/WSAbilitySystemComponent.h"
#include "Input/WSInputComponent.h"

AWSCharacter::AWSCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWSCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponentWeak = UWSAbilitySystemComponent::GetWSAbilitySystemComponentFromController(GetController());
}

void AWSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	check(PC);

	const ULocalPlayer* LP = PC->GetLocalPlayer();
	check(LP);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);
	
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMapping, 0.f);

	UWSInputComponent* InputComp = Cast<UWSInputComponent>(PlayerInputComponent);
	check(InputComp);
	
	if (InputConfig)
	{
		// Ability Actions
		InputComp->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased);

		// Native Actions
		InputComp->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag(TEXT("InputTag.Move"), EGameplayTagEventType::NewOrRemoved), ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		InputComp->BindNativeAction(InputConfig, FGameplayTag::RequestGameplayTag(TEXT("InputTag.Look"), EGameplayTagEventType::NewOrRemoved), ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	}
}

void AWSCharacter::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (AbilitySystemComponentWeak.IsValid())
	{
		AbilitySystemComponentWeak->AbilityInputTagPressed(InputTag);
	}
}

void AWSCharacter::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (AbilitySystemComponentWeak.IsValid())
	{
		AbilitySystemComponentWeak->AbilityInputTagReleased(InputTag);
	}
}

void AWSCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();
		
	if (Value.X != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value.X);
	}
	if (Value.Y != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(),  Value.Y);
	}
}

void AWSCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D Value = InputActionValue.Get<FVector2D>();
		
	if (Value.X != 0.0f)
	{
		AddControllerYawInput(Value.X);
	}
	if (Value.Y != 0.0f)
	{
		AddControllerPitchInput(Value.Y);
	}
}
