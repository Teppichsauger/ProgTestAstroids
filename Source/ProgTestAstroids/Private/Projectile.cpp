// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Astroid.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));
	RootComponent = ProjectileMesh;
}

float AProjectile::GetProjectileDamage()
{
	return ProjectileDamage;
}

void AProjectile::UpdateProjectile(float delta)
{
	FVector MoveDirection = FVector(-1,0,0) * (ProjectileSpeed * delta);
    this->AddActorWorldOffset(MoveDirection);
}

void AProjectile::ProjectileDestroyAfterTime()
{
	this->Destroy();
}

void AProjectile::OnHit(AActor* OtherActor)
{
	if(OtherActor->IsA(AAstroid::StaticClass()))
	{
		Cast<AAstroid>(OtherActor)->TakeAstroidDamage(ProjectileDamage);
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ProjectileDestroyTimer,this,&AProjectile::ProjectileDestroyAfterTime,DestroyTime,false);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateProjectile(DeltaTime);
}
