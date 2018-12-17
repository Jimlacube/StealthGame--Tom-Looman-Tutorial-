// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_LaunchPad.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API AFPS_LaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS_LaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* LaunchPadComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxCollisionComp;

	UFUNCTION()
	void Launch(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
