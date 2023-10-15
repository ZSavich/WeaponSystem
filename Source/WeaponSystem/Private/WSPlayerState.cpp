// Fill out your copyright notice in the Description page of Project Settings.

#include "WSPlayerState.h"
#include "AbilitySystem/WSAbilitySystemComponent.h"

AWSPlayerState::AWSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UWSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}
