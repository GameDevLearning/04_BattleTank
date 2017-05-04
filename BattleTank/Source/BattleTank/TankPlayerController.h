// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	
private:
	//moves the barrel so the shot would hit the world at that location
	void AimTowardsCrosshair();

	//true if hit landscape
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};
