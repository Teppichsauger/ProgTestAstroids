// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ForceFieldComponent.h"
#include "Weapon.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"

#include "SpaceShip.generated.h"

UCLASS()
class PROGTESTASTROIDS_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* SpaceShipMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
	UForceFieldComponent* ForceField;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Weapons")
	USphereComponent* WeaponSocket;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Weapons")
	AWeapon* CurrentWeapon;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Weapons")
	TSubclassOf<class AWeapon> PrimaryWeaponClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UParticleSystemComponent* ShipFire;

	
	bool IsPlayerInBounds(float min, float max);

	void TakeShipDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void AttachWeapon(TSubclassOf<class AWeapon> WeaponTypeToAttache);

	void Fire();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOverEvent();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveX(float AxisValue);

};
