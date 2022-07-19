// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AWeapon::FireWeapon(FVector MuzzleLocation, float ProjectileDamage, TSubclassOf<AProjectile> Projectile)
{
	if(Ammunition > 0 || isInfinitAmmunition)
	{
		FRotator Rotation = FRotator(0);
		FActorSpawnParameters SpawnInfo;
		AProjectile* CachedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile.GetDefaultObject()->GetClass(),MuzzleLocation, Rotation, SpawnInfo);
		CachedProjectile->ProjectileDamage = ProjectileDamage;
		if(!isInfinitAmmunition)
		{
			Ammunition --;
		}
	}
	else
	{
		//if out of ammo switch to Primary Weapon
		ASpaceShip* SpaceShip = Cast<ASpaceShip>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		SpaceShip->CurrentWeapon->Destroy();
		SpaceShip->AttachWeapon(SpaceShip->PrimaryWeaponClass);
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Ammunition = FMath::RandRange(50,100);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

