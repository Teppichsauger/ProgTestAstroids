// Fill out your copyright notice in the Description page of Project Settings.


#include "AstroidField.h"

#include "Astroid.h"
#include "PickUp.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAstroidField::AAstroidField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = Root;
	AstroidSpawnBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBounds"));
	AstroidSpawnBounds->SetupAttachment(RootComponent);

}

void AAstroidField::SpawnAstroidWave(int numAstroids)
{
	for(int i = 0; i < numAstroids; i++)
	{
		SpawnAstroid();
	}
}

void AAstroidField::SpawnAstroid()
{
	FVector BoxOrigin = AstroidSpawnBounds->GetComponentLocation();
	FVector BoxBounds = AstroidSpawnBounds->GetScaledBoxExtent();
	FVector RandLocationInBounds = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin,BoxBounds);

	FVector Location = FVector(RandLocationInBounds.X,RandLocationInBounds.Y,0);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AAstroid>(AstroidClass.GetDefaultObject()->GetClass(),Location, Rotation, SpawnInfo);

	int x = FMath::RandRange(0,100);
	if(x < 5)
	{
		SpawnPickUp();
	}
}

void AAstroidField::SpawnPickUp()
{
	if(PossiblePickUps.Num() > 0)
	{
		FVector BoxOrigin = AstroidSpawnBounds->GetComponentLocation();
		FVector BoxBounds = AstroidSpawnBounds->GetScaledBoxExtent();
		FVector RandLocationInBounds = UKismetMathLibrary::RandomPointInBoundingBox(BoxOrigin,BoxBounds);
		
		FVector Location = FVector(RandLocationInBounds.X,RandLocationInBounds.Y,0);
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		int RandPickup = FMath::RandRange(0,PossiblePickUps.Num() - 1);
		GetWorld()->SpawnActor<APickUp>(PossiblePickUps[RandPickup].GetDefaultObject()->GetClass(),Location, Rotation, SpawnInfo);
	}
}

void AAstroidField::AstroidWaveUpdate()
{
	SpawnAstroidWave(FMath::RandRange(MinAstroids,MaxAstroids));
}

// Called when the game starts or when spawned
void AAstroidField::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle,this,&AAstroidField::AstroidWaveUpdate,IntervalBetweenWaves,true);
}

// Called every frame
void AAstroidField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

