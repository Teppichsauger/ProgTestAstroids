// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PROGTESTASTROIDS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="WeaponProperties")
	int Ammunition;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="WeaponProperties")
	bool isInfinitAmmunition;

	UFUNCTION(BlueprintCallable)
	void FireWeapon(FVector MuzzleLocation,float ProjectileDamage,TSubclassOf<class AProjectile> Projectile);
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
