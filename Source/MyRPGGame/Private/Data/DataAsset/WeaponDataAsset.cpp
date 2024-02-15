// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DataAsset/WeaponDataAsset.h"


// void UWeaponDataAsset::WeaponEffect(float rate)
// {
// 	return;
// }

FWeaponMsg UWeaponDataAsset::GetWeaponMsg()
{
	FWeaponMsg WeaponMsg;
	WeaponMsg.Attack = Attack;
	WeaponMsg.Defence = Defence;
	WeaponMsg.CurrentBullet = CurrentBullet;
	WeaponMsg.GroupBullet = GroupBullet;
	WeaponMsg.MaxBullet = MaxBullet;
	WeaponMsg.bEquip = bEquip;
	return WeaponMsg;
}
