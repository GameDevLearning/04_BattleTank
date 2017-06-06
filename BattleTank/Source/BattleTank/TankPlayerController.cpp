// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if(AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at begin play"))
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Aim
	AimTowardsCrosshair();
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
		GetControlledTank()->AimAt(HitLocation);
	}
	
}

//Get world location fi linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation, ViewPortSizeY * CrossHairYLoation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection)) {
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
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
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility
	)) {
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
