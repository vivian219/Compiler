#pragma once
#include "MiddleCode.h"
#include "mipsinstr.h"
#include "globalSignary.h"
#include <vector>

class MipsCode {
public:
	MiddleCode middle_code;
	globalSignary glo_sig;
	Signary* cur_sig;
	MipsCode(MiddleCode& _code, globalSignary& _glo) :middle_code(_code), glo_sig(_glo) {
		//Start with main function.
		cur_sig = glo_sig.funcList["main"];
	}

	vector<MipsInstr> mipsInstrs;
	vector<PreDefine> mipsDefines;
	void add(MIPSType _mips_type) {
		mipsInstrs.push_back(MipsInstr(_mips_type));
	}
	void addInstr(MIPSType _mips_type, string _des) {
		mipsInstrs.push_back(MipsInstr(_mips_type," "+_des));
	}
	void addInstr(MIPSType _mips_type, string _des, string _src1) {
		mipsInstrs.push_back(MipsInstr(_mips_type," "+_des, ","+_src1));
	}
	void addInstr(MIPSType _mips_type, string _des, string _src1, string _src2) {
		if ((_mips_type == MIPSType::lw )| (_mips_type == MIPSType::sw)) {
			mipsInstrs.push_back(MipsInstr(_mips_type, " " + _des, "," + _src1, "(" + _src2 + ")"));
		}
		else {
			mipsInstrs.push_back(MipsInstr(_mips_type, " " + _des, "," + _src1, "," + _src2));
		}
	}
	void addDefine(string _label, string _conString) {
		mipsDefines.push_back(PreDefine(_label, _conString));
	}

	// Helper function


	void ToMips(MiddleInstr* middle);

	void CalcToMips(MiddleInstr* middle);

	void AssignToMips(MiddleInstr* middle);
	void ArrAssToMips(MiddleInstr* middle);
	void ArrGetToMips(MiddleInstr* middle);

	void BranchToMips(MiddleInstr* middle);

	void SetLabelToMips(MiddleInstr* middle);
	
	void JumpToMips(MiddleInstr* middle);

	void CallToMips(MiddleInstr* middle);
	void RetToMips(MiddleInstr* middle);
	void PushToMips(MiddleInstr* middle);

	void SaveContext();
	void RestoreContext();
	void BeginToMips(MiddleInstr* middle);
	void EndToMips(MiddleInstr* middle);
	
	void PrintToMips(MiddleInstr* middle);
	void ScanToMips(MiddleInstr* middle);
};