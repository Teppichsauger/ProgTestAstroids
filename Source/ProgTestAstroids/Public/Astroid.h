// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Astroid.generated.h"

UCLASS()
class PROGTESTASTROIDS_API AAstroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAstroid();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UStaticMeshComponent* AstroidMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere,Category="AstroidProperties")
	float AstroidSize = 1;
	UPROPERTY(EditAnywhere,Category="AstroidProperties")
	float MinSize = 1;
	UPROPERTY(EditAnywhere,Category="AstroidProperties")
	float MaxSize = 2;
	UPROPERTY(VisibleAnywhere,Category="AstroidProperties")
	float AstroidResistance = 50;
	float CurrentAstroidResistance;
	UPROPERTY(EditAnywhere,Category="AstroidProperties")
	float MinVelocity = 0.5f;
	UPROPERTY(EditAnywhere,Category="AstroidProperties")
	float MaxVelocity = 1;
	
	void TakeAstroidDamage(float Damage);
	UFUNCTION(BlueprintCallable)
	void OnHit(AActor* OtherActor);

	UPROPERTY(EditAnywhere,Category="AstroidProperties")
	UParticleSystem* Explosion;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetAstroidProperties();
	void MoveAstroid(float delta);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
