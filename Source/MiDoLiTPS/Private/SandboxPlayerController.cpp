// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

/// <summary>
/// ��������
/// </summary>
void ASandboxPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	if (InputComponent) {
		//BindAction������ɢ�͵������ �������󶨵����ƣ����뷢�����¼���ָ������ָ�룻�����ú���������
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
	}
}

void ASandboxPlayerController::BeginPlay() {
	Super::BeginPlay();

	//��ȡ�������ض����͵�����Actor �����������������У�Ҫ��ȡ���������ָ�룻ָ������ߵ�ָ������(����ֵ��
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ASandboxPawn::StaticClass(),Pawns);
}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;

	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	if (!CurrentPawn) return;

	UE_LOG(LogSandboxPlayerController, Error, TEXT("Chang player pawn"));
	//����Pawn�Ŀ���Ȩ
	Possess(CurrentPawn);
}
