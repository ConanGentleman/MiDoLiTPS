// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

/// <summary>
/// 接收输入
/// </summary>
void ASandboxPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	if (InputComponent) {
		//BindAction负责离散型的输入绑定 参数：绑定的名称；输入发生的事件；指向对象的指针；被调用函数的引用
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
	}
}

void ASandboxPlayerController::BeginPlay() {
	Super::BeginPlay();

	//获取场景中特定类型的所有Actor 参数：从整个世界中；要获取其对象的类的指针；指向参与者的指针数组(返回值）
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASandboxPawn::StaticClass(),Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;

	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (!CurrentPawn) return;

	UE_LOG(LogSandboxPlayerController, Error, TEXT("Chang player pawn"));
	//更改Pawn的控制权
	Possess(CurrentPawn);
}
