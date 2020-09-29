// Copyright Erik 2020

#include "TimeItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

UTimeItem::UTimeItem()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//RootComponent = CollisionComp;
	CollisionComp->InitSphereRadius(40.f);
	CollisionComp->SetCollisionProfileName(TEXT("TimeColl"));

	SM_Time = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Time"));
	//SM_Time->SetupAttachment(RootComponent);
}
void UTimeItem::Use(ACharacter_BuildingESC* Character)
{
}

void UTimeItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
