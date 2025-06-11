// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Mesh/Doors/Door01.h"

ADoor01::ADoor01()
{
	LeftDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftDoor"));
	RightDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightDoor"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorMeshAsset(TEXT("/Game/JapaneseSchool/Meshes/WindowDoor/SM_Corridor_Door_01.SM_Corridor_Door_01"));

	if (DoorMeshAsset.Succeeded())
	{
		LeftDoorMesh->SetStaticMesh(DoorMeshAsset.Object);
		LeftDoorMesh->SetRelativeLocationAndRotation(FVector(-100.0f, 0, -10.0f), FRotator(0, 0, 0));
		LeftDoorMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
		LeftDoorMesh->SetupAttachment(RootComponent);
		
		RightDoorMesh->SetStaticMesh(DoorMeshAsset.Object);
		RightDoorMesh->SetRelativeLocationAndRotation(FVector(100.0f, 0, -10.0f), FRotator(0, 0, 0));
		RightDoorMesh->SetRelativeScale3D(FVector(-1.0f, 1.0f, 1.0f));
		RightDoorMesh->SetupAttachment(RootComponent);
	}

	Super::SetBoxCollisionLocation(FVector(0.0f, -10.0f, 90.0f));
	Super::SetBoxCollisionRotation(FRotator(0.0f, 0.0f, 0.0f));
	Super::SetBoxCollisionScale(FVector(2.87262f, 3.832295f, 2.358312f));
}

void ADoor01::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor01::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	
}

void ADoor01::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	
}
