// Copyright Erik 2020


#include "PickUps.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUps::APickUps()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = MeshComp;
}

// Called when the game starts or when spawned
void APickUps::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickUps::UseItem(ACharacter_BuildingESC* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("AddingTime"));
	if (Player)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerHere"));
		class UInventoryComponent* InvenComp = Player->PlayerInventoryComp;
		if (InvenComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("ARE YOU REALLY?!"));
			InvenComp->AddTime(150.0f);
		}
	}
}



