// Copyright Erik 2020


#include "KeyItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

UKeyItem::UKeyItem()
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	//RootComponent = CollisionComp;
	CollisionComp->InitSphereRadius(40.f);
	CollisionComp->SetCollisionProfileName(TEXT("KeyColl"));

	SM_Key = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key"));
	//SM_Key->SetupAttachment(RootComponent);
}
void UKeyItem::Use(ACharacter_BuildingESC* Character)
{
}

void UKeyItem::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
