// Copyright Epic Games, Inc. All Rights Reserved.


#include "MiDoLiTPSGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AMiDoLiTPSGameModeBase::AMiDoLiTPSGameModeBase() {
	//修改默认的Pawn
	DefaultPawnClass = ASandboxPawn::StaticClass();
	//修改默认的playercontroller
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}