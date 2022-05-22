#include "stdafx.h"

PhysicsData_t milesPhysicsCopy;
Trampoline* ResetAngle_t = nullptr;

void __cdecl Miles_SuperPhysics_Delete(ObjectMaster* obj) {

	memcpy(&PhysicsArray[Characters_Tails], &milesPhysicsCopy, sizeof(PhysicsData_t));
}

void __cdecl Miles_SuperPhysics_Load(ObjectMaster* obj)
{

	ObjUnknownB* v1; // esi
	CharObj2* v2; // eax

	v1 = (ObjUnknownB*)obj->UnknownB_ptr;
	v2 = GetCharObj2(v1->Time);
	if (v2)
	{
		memcpy(&milesPhysicsCopy, &PhysicsArray[Characters_Tails], sizeof(PhysicsData_t));

		if (!customPhysics || isPerfectChasoLevel()) { //use vanilla broken super sonic physics
			v2->PhysicsData.RollDecel = -0.001f;
			v2->PhysicsData.AirDecel = -0.0020000001f;
			v2->PhysicsData.AirAccel = 0.050000001f;
		}
		else {
			v2->PhysicsData.GroundAccel = 0.065f;
			v2->PhysicsData.RollDecel = -0.006f;
			v2->PhysicsData.AirDecel = -0.01799999999f;
			v2->PhysicsData.AirAccel = 0.040f;
			v2->PhysicsData.MaxAccel = 3.0f;
		}

		obj->DeleteSub = Miles_SuperPhysics_Delete;
		obj->MainSub = Sonic_SuperPhysics_Main;
	}
	else
	{
		DeleteObjectMaster(obj);
	}
}


void Load_SuperPhysics(taskwk* data1) {

	task* v11 = (task*)LoadObject(LoadObj_UnknownB, 2, Miles_SuperPhysics_Load);
	if (v11)
	{
		v11->awp->work.ub[0] = data1->counter.b[0];
	}
}


//fix spring issue, only run if Super Sonic mod is disabled.
static void __cdecl ResetAngle_r(EntityData1* data, EntityData2* data2, CharObj2* co2)
{
	if (!isPerfectChasoLevel() && co2->Upgrades & Upgrades_SuperSonic)
	{
		float v4; // ecx
		float v5; // eax
		float v6; // ecx
		NJS_VECTOR a2a; // [esp+4h] [ebp-Ch] BYREF
		taskwk* twk = (taskwk*)data;

		a2a.x = co2->Speed.x;
		v4 = co2->Speed.z;
		a2a.y = co2->Speed.y;
		a2a.z = v4;
		if (co2->PhysicsData.Run2 * co2->PhysicsData.Run2 >= a2a.z * a2a.z + a2a.y * a2a.y + a2a.x * a2a.x)
		{
			PConvertVector_P2G(twk, &a2a);
			data->Rotation.x = BAMS_SubWrap(data->Rotation.x, GravityAngle_Z, 2048);
			data->Rotation.z = BAMS_SubWrap(data->Rotation.z, GravityAngle_X, 2048);
			PConvertVector_G2P(twk, &a2a);
			v5 = a2a.y;
			v6 = a2a.z;
			co2->Speed.x = a2a.x;
			co2->Speed.y = v5;
			co2->Speed.z = v6;
		}
	}
	else
	{
		TARGET_DYNAMIC(ResetAngle)(data, data2, co2);
	}
}
void init_PhysicsHack()
{

	bool bSS = GetModuleHandle(L"Better-Super-Sonic");

	if (!bSS) {
		ResetAngle_t = new Trampoline(0x443AD0, 0x443AD7, ResetAngle_r);
	}

}