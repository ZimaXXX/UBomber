// Fill out your copyright notice in the Description page of Project Settings.

#include "UBomberHUD.h"

void AUBomberHUD::ShowEndScreen(FString Text)
{
	ShowEndScreenBPEvent(Text);
}


void AUBomberHUD::CloseEndScreen()
{
	CloseEndScreenBPEvent();
}


