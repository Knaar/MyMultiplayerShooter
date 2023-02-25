// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MYMULTIPLAYERSHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	USphereComponent *SphereCollision;

	UPROPERTY(VisibleAnywhere, Category="Weapon")
	UProjectileMovementComponent* MovementComponent;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float ProjectileLifeTime=5.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float BlowSphereRadius=200.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	float BlowSphereDamage=100.0f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category="Weapon")
	bool bDoFullDamage=false;
protected:

	FVector ProjectileDirection;
	
	void SetShootDirection(const FVector &Direction){ ProjectileDirection = Direction; }

	UFUNCTION()
	void ComponentHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController *GetController() const;
	
	
};
