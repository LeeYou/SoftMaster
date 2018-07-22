#include "stdafx.h"
#include "base_soft_strip.h"
//#include "base/thread_task_runner_handle.h"
#include "soft_data_controller.h"

BaseSoftStrip::BaseSoftStrip():view_(NULL),
soft_data_controller_(new SoftDataController){
	soft_list_.clear();
}
BaseSoftStrip::~BaseSoftStrip() {
}
void BaseSoftStrip::ChangeSoft(BaseSoft *soft) {
}
void BaseSoftStrip::DeleteSoft(BaseSoft * soft) {
}

bool BaseSoftStrip::DownloadSoft(BaseSoft *soft)
{
	return true;
}

void BaseSoftStrip::set_windows_view(WindowsView *view)
{
	view_ = view;
}

WindowsView * BaseSoftStrip::windowview()
{
	return view_;
}
void BaseSoftStrip::LoadStripView(){
	soft_data_controller_->RunGetSoftList();
}
