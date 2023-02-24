// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FRotator AMyCharacter::GetAimOffsets() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void AMyCharacter::RotateToPoint(UStaticMeshComponent* MeshToRotate, FVector TargetPoint) 
{
	
	//Получаем текущую позицию меша
	FVector CurrentPos = MeshToRotate->GetComponentLocation();

	//Вычисляем расстояние между текущей позицией и целевой точкой
	FVector DistanceVector = TargetPoint - CurrentPos;

	//Вычисляем длину вектора расстояния
	float Distance = DistanceVector.Size();

	//Вычисляем направление вектора расстояния
	FVector DirectionVector = DistanceVector / Distance;

	//Вычисление угла между вектором направления и осью Z
	float Angle = FMath::Acos(FVector::DotProduct(DirectionVector, FVector::ForwardVector));

	//Вычисляем крутильное направление с помощью вектора произведения
	FVector CrossVector = FVector::CrossProduct(DirectionVector, FVector::ForwardVector);

	//Если крутильное направление положительное, поворачиваем в минус, иначе плюс.
	Angle *= CrossVector.Z > 0 ? -1 : 1;

	//Выставляем поворот меша
	MeshToRotate->SetWorldRotation(FRotator(0, Angle * (180 / PI), 0));
}
