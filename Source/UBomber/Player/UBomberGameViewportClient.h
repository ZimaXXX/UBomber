// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "UBomberGameViewportClient.generated.h"

UCLASS()
class UBOMBER_API UUBomberGameViewportClient : public UGameViewportClient
{
	GENERATED_BODY()
protected:
	/**
	* Override for sending keyboard events to both Players
	*/
	virtual bool InputKey(FViewport* Viewport, int32 ControllerId, FKey Key, EInputEvent EventType, float AmountDepressed = 1.f, bool bGamepad = false) override;
	
	
};
