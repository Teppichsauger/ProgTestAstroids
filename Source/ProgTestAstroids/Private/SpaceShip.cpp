// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpaceShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpaceShip"));
	RootComponent = SpaceShipMesh;
	ForceField = CreateDefaultSubobject<UForceFieldComponent>(TEXT("ForceFieldComp"));
	WeaponSocket = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponSocket"));
	WeaponSocket->SetupAttachment(RootComponent);
	
	ShipFire = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire"));
	ShipFire->SetupAttachment(RootComponent);
	ShipFire->bAutoActivate = false;
}

bool ASpaceShip::IsPlayerInBounds(float min, float max)
{
	float currentLocation = this->GetActorLocation().Y;
	if(currentLocation > min && currentLocation < max)
	{
		return true;
	}
		return false;
}

void ASpaceShip::TakeShipDamage(float Damage)
{
	float NewStrenght = ForceField->GetCurrentForceFieldStrength() - Damage;
	ForceField->SetForceFieldStrength(FMath::Clamp(NewStrenght,0.0f,100.0f));
	
	float StrengthInPrec = FMath::GetMappedRangeValueClamped(FVector2D(ForceField->GetForceFieldStrength(),0),FVector2D(0,100),ForceField->GetCurrentForceFieldStrength());

	if(StrengthInPrec < 75)
	{
		// Start Burning
		ShipFire->SetActive(true);
	}
	else
	{
		ShipFire->SetActive(false);
	}
	if(ForceField->GetCurrentForceFieldStrength() <= 0)
	{
		GameOverEvent();
	}
}

void ASpaceShip::AttachWeapon(TSubclassOf<AWeapon> WeaponTypeToAttache)
{
	if(CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}
	
	FVector Location = WeaponSocket->GetComponentLocation();
	FRotator Rotation = WeaponSocket->GetRelativeRotation();
	FActorSpawnParameters SpawnInfo;
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponTypeToAttache.GetDefaultObject()->GetClass(),Location, Rotation, SpawnInfo);
	CurrentWeapon->AttachToComponent(WeaponSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

}

void ASpaceShip::Fire()
{
	CurrentWeapon->StartFire();
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	AttachWeapon(PrimaryWeaponClass);
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this,&ASpaceShip::MoveX);
	PlayerInputComponent->BindAction(TEXT("Fire"),IE_Pressed,this,&ASpaceShip::Fire);
}

void ASpaceShip::MoveX(float AxisValue)
{
	AddMovementInput(this->GetActorRightVector(),AxisValue);
}

