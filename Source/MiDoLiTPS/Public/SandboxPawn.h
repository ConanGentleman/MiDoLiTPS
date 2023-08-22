// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

//���Ҫ��һ����A���������õ���һ����B��ָ������ã���Ҫ������B��ͷ�ļ�������������������ʹ����ǰ�������˴���Ϊ��ǰ����
class UCameraComponent;

UCLASS()
class MIDOLITPS_API ASandboxPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandboxPawn();

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	//������
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	
	//�����
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	float Velocity = 300.0f;

	//����ȡPawn�Ŀ���Ȩʱ���� ���������Ƹ����ɶ���Ŀ�����ָ��
	virtual void PossessedBy(AController* NewController) override;
	//����ʧPawn�Ŀ���Ȩʱ���� 
	virtual void UnPossessed() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input ��������
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector VelocityVector = FVector::ZeroVector;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
};
