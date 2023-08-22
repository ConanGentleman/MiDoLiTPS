// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MIDOLITPS_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
private:

	UPROPERTY()
	TArray<AActor*> Pawns; //场景中的Pawns数组

	int32 CurrentPawnIndex = 0; //当前是第几个Pawn

	void ChangePawn();
};
