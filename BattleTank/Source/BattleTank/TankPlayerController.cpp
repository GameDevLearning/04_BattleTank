// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerContorller not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
	}

	UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *ControlledTank->GetName());
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Aim
	AimTowardsCrosshair();

	UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) 
	{
		return;
	}

	FVector HitLocation; // Out parameter
	if (GetSightRayHitLocation(HitLocation)) { //side effect, is going to ray trace
		//UE_LOG(LogTemp, Warning, TEXT("HitLocaiton: %s"), *HitLocation.ToString());

		//TODO tell controlled tank to aim at crosshair
	}
	
}

//Get world location fi linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLoation);
	FVector HitLocation;
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		if (GetLookVectorHitLocation(LookDirection, HitLocation)) {
			UE_LOG(LogTemp, Warning, TEXT("HitLocaiton: %s"), *HitLocation.ToString());
		}
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{


	return false;
}
