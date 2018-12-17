// Fill out your copyright notice in the Description page of Project Settings.

#include "FPS_LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
AFPS_LaunchPad::AFPS_LaunchPad()
{
	LaunchPadComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PadComp"));
	RootComponent = LaunchPadComp;

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->SetupAttachment(RootComponent);

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxCollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	BoxCollisionComp->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AFPS_LaunchPad::BeginPlay()
{
	Super::BeginPlay();

	// Bind overlap
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFPS_LaunchPad::Launch);
}

void AFPS_LaunchPad::Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Successful"))

	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);

	FRotator LaunchPadRotation = RootComponent->GetComponentRotation();
	FVector LaunchVelocity = LaunchPadRotation.RotateVector(FVector(-1000.0f, 0.0f, 1000.0f));
	if (OtherCharacter)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlap with pawn"))
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);
	}
	else if (OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
	}
}

