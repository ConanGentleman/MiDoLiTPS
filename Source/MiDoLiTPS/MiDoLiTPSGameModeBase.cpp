// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiDoLiTPSGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AMiDoLiTPSGameModeBase::AMiDoLiTPSGameModeBase() {
	//�޸�Ĭ�ϵ�Pawn
	DefaultPawnClass = ASandboxPawn::StaticClass();
	//�޸�Ĭ�ϵ�playercontroller
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}