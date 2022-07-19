// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Astroid.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "AstroidField.generated.h"

UCLASS()
class PROGTESTASTROIDS_API AAstroidField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstroidField();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* AstroidSpawnBounds;

	void SpawnAstroidWave(int numAstroids);

	void SpawnAstroid();

	void SpawnPickUp();

	void AstroidWaveUpdate();

	UPROPERTY(EditAnywhere, Category="AstoridWaveSettings")
	float IntervalBetweenWaves;
	UPROPERTY(EditAnywhere, Category="AstoridWaveSettings")
	int MinAstroids;
	UPROPERTY(EditAnywhere, Category="AstoridWaveSettings")
	int MaxAstroids;

	FTimerHandle WaveTimerHandle;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="AstoridWaveSettings")
	TSubclassOf<class AAstroid> AstroidClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="PickupSpawning")
	TArray<TSubclassOf<class APickUp>> PossiblePickUps;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
