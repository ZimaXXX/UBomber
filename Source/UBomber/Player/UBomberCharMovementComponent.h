// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UBomberCharMovementComponent.generated.h"

/**
 * Movement component for alterating Player movement speed
 */
UCLASS()
class UBOMBER_API UUBomberCharMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	/**
	* Override for modifying Player speed based on Speed property of UBomberCharacter
	*/
	float GetMaxSpeed() const override;
	
	
};
