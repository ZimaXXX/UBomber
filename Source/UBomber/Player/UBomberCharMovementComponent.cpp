// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberCharMovementComponent.h"
#include "Core/UBomberCharacter.h"

float UUBomberCharMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();

	AUBomberCharacter* const UB_C = Cast<AUBomberCharacter>(PawnOwner);
	if (IsValid(UB_C))
	{
		MaxSpeed *= UB_C->GetSpeedModifier();
	}

	return MaxSpeed;
}


