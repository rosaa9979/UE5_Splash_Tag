// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Mesh/BaseDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseDoor::ABaseDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_T"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	BoxCollision->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ABaseDoor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseDoor::OnOverlapBegin);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseDoor::OnOverlapEnd);
}

// Called every frame
void ABaseDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseDoor::HandleProgress(float Value)
{
}

void ABaseDoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void ABaseDoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABaseDoor::SetBoxCollisionLocation(const FVector& Loc)
{
	BoxCollision->SetWorldLocation(Loc);
}

void ABaseDoor::SetBoxCollisionRotation(const FRotator& Rot)
{
	BoxCollision->SetWorldRotation(Rot);
}

void ABaseDoor::SetBoxCollisionScale(const FVector& Sca)
{
	BoxCollision->SetWorldScale3D(Sca);
}

