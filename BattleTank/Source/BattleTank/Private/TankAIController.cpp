// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//just some testing
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController not finding a player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATankAIController Begin Play"));
	}

	UE_LOG(LogTemp, Warning, TEXT("ATankAIController found: %s"), *PlayerTank->GetName());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) {
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);

}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}