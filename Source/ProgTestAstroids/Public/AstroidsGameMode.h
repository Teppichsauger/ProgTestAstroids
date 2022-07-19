// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AstroidsGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROGTESTASTROIDS_API AAstroidsGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	int Points;
	
};
