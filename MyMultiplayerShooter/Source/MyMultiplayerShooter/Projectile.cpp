// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "MyCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AProjectile::AProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SetRootComponent(SphereCollision);
	SphereCollision->InitSphereRadius(5.0f);
	SphereCollision->IgnoreActorWhenMoving(GetOwner(),true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereCollision->bReturnMaterialOnMove=true;

	MovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed=2000.0f;
	MovementComponent->ProjectileGravityScale=0.0f;

}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	MovementComponent->Velocity=ProjectileDirection*MovementComponent->InitialSpeed;
	SetLifeSpan(ProjectileLifeTime);
	SphereCollision->OnComponentHit.AddDynamic(this,&AProjectile::ComponentHit);
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld())return;
	MovementComponent->StopMovementImmediately();
	UGameplayStatics::ApplyRadialDamage(GetWorld(),BlowSphereDamage,GetActorLocation(),BlowSphereRadius,
	  UDamageType::StaticClass(),{GetOwner()},this,GetController(),bDoFullDamage);
	
	Destroy();
}

AController* AProjectile::GetController() const
{
	const auto Player=Cast<AMyCharacter>(GetOwner());

	return Player? Player->Controller:nullptr;
}

