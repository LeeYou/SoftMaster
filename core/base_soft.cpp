#include "stdafx.h"
#include "base_soft.h"
#include "soft_controller.h"

BaseSoft::BaseSoft(SoftController *controller):
	controller_(controller),
	downloading_(false){
}

BaseSoft::~BaseSoft(){
}
void BaseSoft::SetData(const SofterInfo &data){
	if (data_.Equals(data)){
		return;
	}
	data_ = data;
}
void BaseSoft::set_new_version(const std::wstring &ver) {
	new_version_ = ver;
}
bool BaseSoft::is_update() const {
	if (data_.file_version_ != new_version_) {
		return true;
	}
	return false;
}
