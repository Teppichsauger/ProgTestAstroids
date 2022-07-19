// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"

#include "SpaceShip.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup"));
	RootComponent = PickUpMesh;
	PickUpMesh->OnComponentBeginOverlap.AddDynamic(this, &APickUp::BeginOverlap);
}

void APickUp::MovePickup(float delta)
{
	FVector MoveDirection = FVector(1,0,0) * (Speed * delta);
	this->AddActorWorldOffset(MoveDirection);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePickup(DeltaTime);
}

void APickUp::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->IsA(ASpaceShip::StaticClass()))
	{
		OnPickUp();
		this->Destroy();
	}
}

