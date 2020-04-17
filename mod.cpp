#include "pch.h"
#include "SADXModLoader.h"

extern "C"
{
#pragma pack(push, 8)
	struct __declspec(align(4)) AL_NormalCameraExecutor_Data1
	{
		EntityData1 EntityData1;
		int type;
		NJS_POINT3 velo;
		NJS_POINT3 AimPos;
		Rotation3 AngSpd;
		NJS_POINT3 target;
		NJS_POINT3 AimTarget;
		float dist;
		int ViewAngle;
		float TargetNormalOffsetY;
		float TargetTreeOffsetY;
		float PosOffsetY;
		float PosItpRatio;
		int StopFlag;
	};
#pragma pack(pop)


	DataPointer(float, flt_33D0D44, 0x33D0D44);
	DataPointer(float, flt_33D0D48, 0x33D0D48);
	DataPointer(float, flt_33D0D4C, 0x33D0D4C);
	DataPointer(float, flt_33D0D50, 0x33D0D50);
	DataPointer(float, flt_33D0D54, 0x33D0D54);

	DataPointer(int, dword_3CDC194, 0x3CDC194);
	DataPointer(int, dword_3CDC188, 0x3CDC188);
	DataPointer(int, dword_3CDC19C, 0x3CDC19C);

	DataPointer(ObjectMaster*, ALO_OdekakeMachine_Ptr, 0x03CDC190);

	ObjectFunc(AL_DetectCollisionStandard, 0x0073FE10);
	FunctionPointer(bool, ShakingTree, (), 0x00729FA0);
	
	DataArray(int, ChaoObjectCount, 0x03CC6F48, 12);

	int IsChaoCameraActive;
	int ToggleDisplay = 0;
	int ChaoPauseEnabled = 0;

	void __cdecl AL_NormalCameraExecutor(ObjectMaster* arg0)
	{
		AL_NormalCameraExecutor_Data1* AL_NormalCameraData; // esi
		NJS_VECTOR* camPos_; // ebp
		NJS_VECTOR* field_40; // edi
		NJS_VECTOR* playerPos; // ebx
		double v5; // st7
		ObjectMaster* v6; // eax
		NJS_VECTOR* v7; // eax
		double v8; // st7
		Angle v9; // ecx
		ChaoData2* v10; // ST20_4
		double v11; // st7
		ChaoData2* v12; // ST20_4
		double v13; // st7
		ChaoData2* v14; // ecx
		double v15; // st7
		double v16; // st7
		double v17; // st7
		double v18; // st7
		double v19; // st7
		double v20; // st7
		float v21; // ST24_4
		double v22; // st7
		EntityData1* v23; // [esp+10h] [ebp-2Ch]
		float v24; // [esp+10h] [ebp-2Ch]
		float v25; // [esp+14h] [ebp-28h]
		float v26; // [esp+18h] [ebp-24h]
		ChaoData2* n; // [esp+1Ch] [ebp-20h]
		NJS_VECTOR a1; // [esp+24h] [ebp-18h]
		NJS_VECTOR v; // [esp+30h] [ebp-Ch]

		AL_NormalCameraData = (AL_NormalCameraExecutor_Data1*)arg0->Data1;
		camPos_ = &AL_NormalCameraData->EntityData1.Position;
		field_40 = &AL_NormalCameraData->AimPos;
		playerPos = &EntityData1Ptrs[0]->Position;


		if ((PressedButtons[0] & Buttons_L) && (PressedButtons[0] & Buttons_R))
			IsChaoCameraActive = !IsChaoCameraActive;

		if (PressedButtons[0] & Buttons_X) ToggleDisplay = !ToggleDisplay;
		if (PressedButtons[0] & Buttons_Y) ChaoPauseEnabled = !ChaoPauseEnabled;

		if (!IsChaoCameraActive || ChaoObjectCount[0] <= 0)
		{
			ControlEnabled = 1;
			ChaoEnabled = 1; //chaoenabled
			playerPos = &EntityData1Ptrs[0]->Position;
			AL_NormalCameraData->dist = 25.0f;
		}
		else
		{
			ControlEnabled = 0;
			ChaoEnabled = ChaoPauseEnabled; //chaoenabled
			((ChaoData1*)GetChaoObject(0, arg0->Data1->Index)->Data1)->NestFlag = 1; //NestFlag
			playerPos = &GetChaoObject(0, arg0->Data1->Index)->Data1->Position;
			if (HeldButtons[0] & Buttons_Down)
			{
				if (AL_NormalCameraData->dist > 7.5f) AL_NormalCameraData->dist -= 0.25f;
			}
			if (HeldButtons[0] & Buttons_Up)
			{
				if (AL_NormalCameraData->dist < 50.0f) AL_NormalCameraData->dist += 0.25f;
			}
		}


		if (!AL_NormalCameraData->EntityData1.Action)
		{
			camPos_->x = playerPos->x - njSin(0x4000 - EntityData1Ptrs[0]->Rotation.y) * 10.0;
			AL_NormalCameraData->EntityData1.Position.y = AL_NormalCameraData->PosOffsetY + playerPos->y;
			AL_NormalCameraData->EntityData1.Position.z = playerPos->z - njCos(0x4000 - EntityData1Ptrs[0]->Rotation.y) * 10.0;
			field_40->x = camPos_->x;
			AL_NormalCameraData->AimPos.y = AL_NormalCameraData->EntityData1.Position.y;
			AL_NormalCameraData->AimPos.z = AL_NormalCameraData->EntityData1.Position.z;
			++AL_NormalCameraData->EntityData1.Action;
		}
		v5 = field_40->x - playerPos->x;
		a1.y = 0.0;
		a1.x = v5;
		a1.z = AL_NormalCameraData->AimPos.z - playerPos->z;
		njUnitVector(&a1);
		flt_33D0D44 = AL_NormalCameraData->dist;
		a1.x = flt_33D0D44 * a1.x;
		a1.z = flt_33D0D44 * a1.z;

		if (PressedButtons[0] & Buttons_A)
		{
			arg0->Data1->Index++;
			if (arg0->Data1->Index >= ChaoObjectCount[0])
				arg0->Data1->Index = 0;
		}
		if (PressedButtons[0] & Buttons_B)
		{
			arg0->Data1->Index--;
			if (arg0->Data1->Index < 0)
				arg0->Data1->Index = ChaoObjectCount[0] - 1;
		}
		if (HeldButtons[0] & Buttons_L)
		{
			njPushMatrix(_nj_unit_matrix_);
			njRotateY(0, 65024);
			njCalcVector(0, &a1, &a1);
			njPopMatrixEx();
		}
		if (HeldButtons[0] & Buttons_R)
		{
			njPushMatrix(_nj_unit_matrix_);
			njRotateY(0, 512);
			njCalcVector(0, &a1, &a1);
			njPopMatrixEx();
		}
		if (ShakingTree())
		{
			v6 = GetCharObj2(0)->ObjectHeld;
			if (v6)
			{
				v7 = &v6->Data1->Position;
			}
			else
			{
				v7 = playerPos;
			}
			AL_NormalCameraData->target.x = (v7->x - AL_NormalCameraData->target.x) * 0.039999999
				+ AL_NormalCameraData->target.x;
			AL_NormalCameraData->target.y = (v7->y + AL_NormalCameraData->TargetTreeOffsetY - AL_NormalCameraData->target.y)
				* 0.039999999
				+ AL_NormalCameraData->target.y;
			v8 = v7->z;
			goto LABEL_14;
		}
		if (dword_3CDC19C)
		{
			AL_NormalCameraData->target.x = (70.0 - AL_NormalCameraData->target.x) * 0.039999999 + AL_NormalCameraData->target.x;
			AL_NormalCameraData->target.y = (95.0 - AL_NormalCameraData->target.y) * 0.039999999 + AL_NormalCameraData->target.y;
			v8 = -150.0;
		LABEL_14:
			AL_NormalCameraData->target.z = (v8 - AL_NormalCameraData->target.z) * 0.039999999 + AL_NormalCameraData->target.z;
		}
		AL_NormalCameraData->target.x = (playerPos->x - AL_NormalCameraData->target.x) * 0.40000001
			+ AL_NormalCameraData->target.x;
		AL_NormalCameraData->target.y = (AL_NormalCameraData->TargetNormalOffsetY
			+ playerPos->y
			- AL_NormalCameraData->target.y)
			* 0.2
			+ AL_NormalCameraData->target.y;
		AL_NormalCameraData->target.z = (playerPos->z - AL_NormalCameraData->target.z) * 0.40000001
			+ AL_NormalCameraData->target.z;
		if (dword_3CDC194 && ALO_OdekakeMachine_Ptr)
		{
			v9 = ALO_OdekakeMachine_Ptr->Data1->Rotation.y;
			v23 = ALO_OdekakeMachine_Ptr->Data1;
			if (dword_3CDC188)
			{
				v10 = (ChaoData2*)(v9 + 0x5800);
				field_40->x = njSin(v9 + 0x5800) * 45.0 + v23->Position.x;
				AL_NormalCameraData->AimPos.y = v23->Position.y + 16.0;
				v11 = njCos((Angle)v10) * 45.0 + v23->Position.z;
			}
			else
			{
				v12 = (ChaoData2*)(v9 + 0x5800);
				field_40->x = njSin(v9 + 0x5800) * 37.0 + v23->Position.x;
				AL_NormalCameraData->AimPos.y = v23->Position.y + 12.0;
				v11 = njCos((Angle)v12) * 37.0 + v23->Position.z;
			}
		}
		else
		{
			field_40->x = a1.x + playerPos->x;
			AL_NormalCameraData->AimPos.y = AL_NormalCameraData->PosOffsetY + playerPos->y;
			v11 = a1.z + playerPos->z;
		}
		v14 = (ChaoData2*)arg0->Data2;
		AL_NormalCameraData->AimPos.z = v11;
		v13 = flt_33D0D54 + v14->MoveWork.WaterY;
		if (v13 > AL_NormalCameraData->AimPos.y)
		{
			AL_NormalCameraData->AimPos.y = v13;
		}
		
		n = v14;
		if (v14->MoveWork.Flag & 0x800)
		{
			AL_NormalCameraData->PosItpRatio = 0.02;
		}
		else if (dword_3CDC194)
		{
			AL_NormalCameraData->PosItpRatio = 0.050000001;
		}
		else
		{
			v15 = AL_NormalCameraData->PosItpRatio + 0.0099999998;
			AL_NormalCameraData->PosItpRatio = v15;
			if (v15 > flt_33D0D48)
			{
				AL_NormalCameraData->PosItpRatio = flt_33D0D48;
			}
		}
		v.x = (field_40->x - camPos_->x) * AL_NormalCameraData->PosItpRatio;
		if (v14->MoveWork.Flag & 0x400
			&& (v16 = AL_NormalCameraData->AimPos.y - AL_NormalCameraData->EntityData1.Position.y, v16 < 30.0))
		{
			v17 = v16 * flt_33D0D4C * 0.1;
		}
		else
		{
			v17 = (AL_NormalCameraData->AimPos.y - AL_NormalCameraData->EntityData1.Position.y) * flt_33D0D4C;
		}
		v.y = v17;
		v.z = (AL_NormalCameraData->AimPos.z - AL_NormalCameraData->EntityData1.Position.z) * AL_NormalCameraData->PosItpRatio;
		v18 = njScalor(&v);
		v24 = v18;
		if (v18 > 0.0 && v24 > (double)flt_33D0D50)
		{
			v24 = flt_33D0D50;
			njUnitVector(&v);
			v.x = flt_33D0D50 * v.x;
			v.y = flt_33D0D50 * v.y;
			v.z = v.z * flt_33D0D50;
		}
		njAddVector(&AL_NormalCameraData->EntityData1.Position, &v);
		v25 = camPos_->x - playerPos->x;
		v19 = AL_NormalCameraData->EntityData1.Position.z - playerPos->z;
		v26 = v19;
		v20 = v19 * v26 + v25 * v25;
		if (v20 < 15.0 * 15.0)
		{
			v21 = v20;
			v22 = 15.0 / squareroot(v21);
			camPos_->x = v25 * v22 + playerPos->x;
			AL_NormalCameraData->EntityData1.Position.z = v22 * v26 + playerPos->z;
		}
		if (AL_NormalCameraData->StopFlag)
		{
			if (v24 > 0.0099999998 || n->MoveWork.Flag & 0x800)
			{
				AL_NormalCameraData->StopFlag = 0;
			}
		}
		else
		{
			if (!(n->MoveWork.Flag & 0x800) && v24 < 0.0049999999)
			{
				AL_NormalCameraData->StopFlag = 1;
			}
			AL_DetectCollisionStandard(arg0);
		}
		Chao_AddToCollisionList(arg0);
	}

	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		WriteJump((void*)0x0072A040, AL_NormalCameraExecutor);
	}
	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer };
}