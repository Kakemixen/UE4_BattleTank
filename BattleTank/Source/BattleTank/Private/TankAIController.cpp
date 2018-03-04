// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* TempTank = GetControlledTank();
	if (TempTank == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Ai %s Has No Tank!"), *GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI %s Has Tank %s"), *GetName(), *TempTank->GetName());
	}

	ATank* TempPlayer = GetPlayerTank();
	if (TempPlayer == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Ai %s Found No Player Tank!"), *GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI %s Found Player controlled Tank %s"), *GetName(), *TempPlayer->GetName());
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}



