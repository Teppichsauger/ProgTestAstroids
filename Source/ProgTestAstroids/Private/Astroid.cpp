// Fill out your copyright notice in the Description page of Project Settings.


#include "Astroid.h"

#include "AstroidsGameMode.h"
#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAstroid::AAstroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AstroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Astroid"));
	RootComponent = AstroidMesh;
	AstroidMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AAstroid::BeginPlay()
{
	Super::BeginPlay();
	SetAstroidProperties();
	//AstroidMesh->OnComponentHit.AddDynamic(this, &AAstroid::OnCompHit);
}

void AAstroid::SetAstroidProperties()
{
	AstroidSize = FMath::RandRange(MinSize,MaxSize);
	AstroidResistance = FMath::Floor(FMath::GetMappedRangeValueClamped(FVector2D(MinSize,MaxSize),FVector2D(50,100),AstroidSize));
	FRotator AstroidRotation = FRotator(FMath::RandRange(0,360));
	CurrentAstroidResistance = AstroidResistance;
	
	AstroidMesh->SetWorldScale3D(FVector(AstroidSize));
	AstroidMesh->SetWorldRotation(FRotator(AstroidRotation));
}

void AAstroid::MoveAstroid(float delta)
{
	float Speed = FMath::GetMappedRangeValueClamped(FVector2D(MaxSize,MinSize),FVector2D(MinVelocity,MaxVelocity),AstroidSize);
	FVector MoveDirection = FVector(1,0,0) * (Speed * delta);
	this->AddActorWorldOffset(MoveDirection);

	// Destroy if out of bounds
	if(this->GetActorLocation().X > 1300)
	{
		this->Destroy();
	}
}

void AAstroid::TakeAstroidDamage(float Damage)
{
	CurrentAstroidResistance -= Damage;
	if(CurrentAstroidResistance <= 0)
	{
		AAstroidsGameMode* GameMode = (AAstroidsGameMode*)GetWorld()->GetAuthGameMode();
		int NewPoints = GameMode->Points + (int)AstroidResistance;
		GameMode->Points = NewPoints;
		this->Destroy();
		FTransform SpawnTransform = FTransform(FRotator(0),AstroidMesh->GetComponentLocation(),FVector(1,1,1));
		if(Explosion)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Explosion,SpawnTransform,true,EPSCPoolMethod::None,true);
		}
	}
}

// Called every frame
void AAstroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveAstroid(DeltaTime);
}

void AAstroid::OnHit(AActor* OtherActor)
{
	if(OtherActor == UGameplayStatics::GetPlayerPawn(GetWorld(),0))
	{
		Cast<ASpaceShip>(OtherActor)->TakeShipDamage(CurrentAstroidResistance);
		this->Destroy();
	}
}

